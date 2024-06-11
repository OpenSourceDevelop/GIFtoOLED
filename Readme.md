# OLED_C-Array

## Details
A Gif converter to write the frames into a C array for monochrome OLED displays with grayscale.

## File
`OLED_C-Array.ino`

## Author
OpenDev 📧 [GitHub Profile](https://github.com/OpenSourceDevelop)

## Version
See `#define SWVERSION`

## Date
05.05.2024

## Bug
*None reported*

## License
Free

## Note
Adafruit_SSD1306 Library: [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

## IO
| Signal | MCU |
|--------|-----|
|  I2C   | I2C |

## Usage

1. Clone or download the repository to your local machine.
2. Install the required libraries using the command above.
3. Run the script `GIFtoOLED.py`.
4. Click on the "Browse" button to select a GIF file.
5. The converted C array will be saved as `frames_array.h` in the same directory as the script.

## Example

The Gif converter performs the following steps:

1. Extracts the frames from the selected GIF file.
2. Converts the individual images to grayscale.
3. Converts the grayscale images into a C array.
4. Determines the frame rate (FPS) of the GIF.
5. Writes the result to a header file.

An example for Arduino is included.
