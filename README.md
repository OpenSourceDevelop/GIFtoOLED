# OLED_C-Array

[![Build Status](https://github.com/OpenSourceDevelop/GIFtoOLED?branch=main)](https://github.com/OpenSourceDevelop)

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

## Code

```cpp
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SWVERSION "1.0"

// Frame data
const uint8_t frames[][SCREEN_WIDTH * SCREEN_HEIGHT / 8] PROGMEM = {
    // Include the frame data from frames_array.h here
};

void setup() {
  Serial.begin(115200);

  // Initialize the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // Display each frame
  for(int i = 0; i < sizeof(frames)/sizeof(frames[0]); i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, frames[i], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();
    delay(100); // Adjust this delay to change the frame rate
  }
}
