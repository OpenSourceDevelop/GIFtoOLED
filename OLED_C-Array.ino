/*! 
 *  \brief     OLED_C-Array Test 
 *  \details   Shows the C-Array on a OLED Display with an Animation
 *  \author    OpenDev 📧 https://github.com/OpenSourceDevelop
 *  \version   see #define SWVERSION
 *  \date      05.05.2024
 *  \bug       
 *  \warning   
 *  \copyright Free 
 * 
 *  CONTROLLER: Adafruit_SSD1306   https://github.com/adafruit/Adafruit_SSD1306
 *
 *  IO:
 *       I2C  
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "frames_array.h"

#define SWVERSION "1.0"

#define SCREEN_I2C_ADDR 0x3C // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

void setup() {
  Wire.begin(5,4);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
}

int frame = 0;
void loop() {
  display.clearDisplay();
  display.drawBitmap(48, 16, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  
  delay(1000/FPS); 
}
