import tkinter as tk
from tkinter import filedialog
from PIL import Image
import numpy as np
import av

__version__ = "1.0"

def open_file_dialog():
    file_path = filedialog.askopenfilename(filetypes=[("GIF files", "*.gif")])
    return file_path

def gif_to_frames(gif_path):
    frames = []
    with Image.open(gif_path) as img:
        while True:
            try:
                frames.append(img.copy())
                img.seek(img.tell() + 1)
            except EOFError:
                break
    return frames

def convert_to_grayscale(frames):
    grayscale_frames = []
    for frame in frames:
        grayscale_frame = frame.convert("L")
        grayscale_frames.append(grayscale_frame)
    return grayscale_frames

def frames_to_array(frames):
    array = np.array([np.array(frame) for frame in frames])
    return array

def frames_to_c_array(frames, gif_path):
    array_string = ""
    frame_count = len(frames)
    frame_width = frames[0].width
    frame_height = frames[0].height

    array_string += f"#define FRAME_WIDTH {frame_width}\n"
    array_string += f"#define FRAME_HEIGHT {frame_height}\n"
    array_string += f"#define FRAME_COUNT {frame_count}\n"
    fps = get_gif_fps(gif_path)
    array_string += f"#define FPS {fps}\n\n"
    
    array_string += f"const byte PROGMEM frames[][{frame_height * ((frame_width + 7) // 8)}] = {{\n"
    
    for frame_idx, frame in enumerate(frames):
        pixels = list(frame.convert("1").getdata())  
        byte_width = (frame_width + 7) // 8
        byte_array = [0] * (frame_height * byte_width)
        
        for i in range(len(pixels)):
            row = i // frame_width
            col = i % frame_width
            byte_index = row * byte_width + col // 8
            bit_index = 7 - (col % 8)
            byte_array[byte_index] |= (pixels[i] & 1) << bit_index  

        array_string += "{ "
        for byte in byte_array:
            array_string += f"0x{byte:02X}, "
        array_string += "},\n"
    
    array_string += "};\n"
    return array_string

def get_gif_fps(file_path):
    container = av.open(file_path)
    video_stream = next(s for s in container.streams if s.type == 'video')
    return video_stream.average_rate

def process_gif():
    gif_path = open_file_dialog()
    if not gif_path:
        print("No GIF file selected.")
        return
    
    array_name = "frames_array" 
    frames = gif_to_frames(gif_path)
    grayscale_frames = convert_to_grayscale(frames)
    c_array = frames_to_c_array(grayscale_frames, gif_path)
    
    with open(f"{array_name}.h", "w") as f:
        f.write(c_array)

    print(f"Number of frames: {len(frames)}")
    print(f"FPS: {get_gif_fps(gif_path)}")
    print(f"Converted frames to grayscale and saved as {array_name}.h")

def create_gui():
    root = tk.Tk()
    root.title("GIF to C Array Converter")

    label = tk.Label(root, text="Select a GIF file:")
    label.pack(pady=10)

    button = tk.Button(root, text="Browse", command=process_gif)
    button.pack(pady=5)

    root.mainloop()

if __name__ == "__main__":
    create_gui()
