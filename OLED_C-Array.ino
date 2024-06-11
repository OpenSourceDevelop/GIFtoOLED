/*! 
 *  \brief     OLED_C-Array Test 
 *  \details   Shows the C-Array on a OLED Display with an Animation
 *  \author    OpenDev 📧 https://github.com/OpenSourceDevelop
 *  \version   see #define SWVERSION
 *  \date      10.06.2024
 *  \bug       
 *  \warning   
 *  \copyright Free 
 * 
 *  CONTROLLER: ESP32 / WEMOS D1 MINI ESP32
 *
 *  IO:
 *                        IRin   ==>  15
 *                        IRout  <==  4
 *                        Button ==>  32
 *                        LEDw   <==  0
 * 
 *    https://github.com/mdminhazulhaque/esp32-mqtt-ir-remote/tree/master
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
