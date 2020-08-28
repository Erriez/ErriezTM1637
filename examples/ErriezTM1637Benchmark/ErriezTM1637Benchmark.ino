/*
 * MIT License
 *
 * Copyright (c) 2018-2020 Erriez
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
 * \brief TM1637 benchmark example
 * \details
 *    Required libraries:
 *       https://github.com/Erriez/ErriezTM1637
 *       https://github.com/Erriez/ErriezTimestamp
 */

#include <ErriezTM1637.h>
#include <ErriezTimestamp.h>

// Connect display pins to the Arduino DIGITAL pins
#if defined(ARDUINO_ARCH_AVR)
#define TM1637_CLK_PIN      2
#define TM1637_DIO_PIN      3
#define TEST_PIN            5
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI) || defined(ESP8266_WEMOS_D1MINI) || defined(ARDUINO_ESP8266_NODEMCU)
#define TM1637_CLK_PIN      D2
#define TM1637_DIO_PIN      D3
#define TEST_PIN            D5
#elif defined(ARDUINO_LOLIN32)
#define TM1637_CLK_PIN      0
#define TM1637_DIO_PIN      4
#define TEST_PIN            16
#else
#error "May work, but not tested on this target"
#endif

// Create objects
TM1637 tm1637(TM1637_CLK_PIN, TM1637_DIO_PIN);
TimestampMicros timestamp;


void setup()
{
    pinMode(TEST_PIN, OUTPUT);

    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("TM1637 benchmark example"));

    // Initialize TM1637
    tm1637.begin();
    tm1637.clear();

    uint8_t buf[TM1637_NUM_GRIDS];
    for (uint8_t i = 0; i < TM1637_NUM_GRIDS; i++) {
        buf[i] = 0x3f;
    }

    delay(2000);

    digitalWrite(TEST_PIN, HIGH);

    Serial.print(F("getKeys(): "));
    timestamp.start();
    uint32_t keys = tm1637.getKeys();
    timestamp.print();

    delay(1);

    Serial.print(F("writeData(0, 0x7f): "));
    timestamp.start();
    tm1637.writeData(0x00, 0x7f);
    timestamp.print();

    delay(1);

    Serial.print(F("writeData(buf, 16): "));
    timestamp.start();
    tm1637.writeData(0x00, buf, sizeof(buf));
    timestamp.print();

    delay(1);

    Serial.print(F("Clear(): "));
    timestamp.start();
    tm1637.clear();
    timestamp.print();

    digitalWrite(TEST_PIN, LOW);
}

void loop()
{
}
