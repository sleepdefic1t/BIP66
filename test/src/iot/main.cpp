/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#if (defined PLATFORMIO && defined UNIT_TEST)

#include <AUnit.h>

void setup() {
  Serial.begin(115200);

  while (!Serial) { delay(100); };
  // ^for the Arduino Leonardo/Micro only

  aunit::TestRunner::setTimeout(0);

  delay(1000);
}

void loop() {
  aunit::TestRunner::run();
}

#endif
