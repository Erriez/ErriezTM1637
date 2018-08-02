/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file TM1637.ino
 * \brief TM1637 example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezTM1637
 *      Documentation:  https://erriez.github.io/ErriezTM1637
 */

#include <Arduino.h>
#include <TM1637.h>

// Connect display pins to the Arduino DIGITAL pins
#if defined(ARDUINO_ARCH_AVR)
#define TM1637_CLK_PIN      2
#define TM1637_DIO_PIN      3
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI) || defined(ESP8266_WEMOS_D1MINI) || defined(ARDUINO_ESP8266_NODEMCU)
#define TM1637_CLK_PIN      D2
#define TM1637_DIO_PIN      D3
#elif defined(ARDUINO_LOLIN32)
#define TM1637_CLK_PIN      0
#define TM1637_DIO_PIN      4
#else
#error "May work, but not tested on this target"
#endif

TM1637 tm1637(TM1637_CLK_PIN, TM1637_DIO_PIN);

static uint8_t keysLast = 0;


void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("TM1637 example"));

    // Initialize TM1637
    tm1637.begin();

    // Turn display off (All LED's off)
    tm1637.displayOff();

    // Clear display
    tm1637.clear();

    // Set brightness 0..7
    tm1637.setBrightness(3);

    // Turn display on
    tm1637.displayOn();

    // Write segment LED's to the first display registers 0x00..0x0F with value 0x00..0xff to
    // display numbers and characters. Just an example which depends on the hardware:
    tm1637.writeData(0x01, 0x01);
}

void loop()
{
    uint8_t keys;

    // Read 8-bit keys
    keys = tm1637.getKeys();

    // Check key down
    if (keysLast != keys) {
        keysLast = keys;

        Serial.print(F("Keys: 0x"));
        Serial.println(keys, HEX);

        if (keys == 0xFF) {
            // Write segment LED's to first display register
            tm1637.writeData(0, 0b00111111);
        } else {
            // Write segment LED's to first display register
            tm1637.writeData(0, 0b00000110);
        }
    }
}
