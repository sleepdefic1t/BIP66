# BIP66

> A simple Bitcoin BIP66 Implementation in C++ for the ARK Blockchain.

ANS.1 DER Encoder/Decoder based on [Bitcoin BIP66](https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki).

[![Build Status](https://badgen.now.sh/circleci/github/sleepdefic1t/BIP66)](https://circleci.com/gh/sleepdefic1t/BIP66)
[![Latest Version](https://badgen.now.sh/github/release/sleepdefic1t/BIP66)](https://github.com/sleepdefic1t/BIP66/releases)
[![License: MIT](https://badgen.now.sh/badge/license/MIT/green)](https://opensource.org/licenses/MIT)

## Supported Platforms

| IoT:        | supported: |
| :---------- | :--------: |
| Arduino IDE | [x]        |
| PlatformIO  | [x]        |

| Boards: | supported: |
| :------ | :--------: |
| ESP8266 | [x]        |
| ESP32   | [x]        |

| OS Platform: | supported: |
| :----------- | :--------: |
| Linux        | [x]        |
| macOS        | [x]        |
| Windows      | [x]        |

## Installation

### Dependencies

IoT:
-   **Arduino IDE**: N/A
-   **PlatformIO**: AUnit

OS:
-   **Linux**: CMake
-   **macOS**: CMake
-   **Windows**: CMake

---

### Arduino IDE

1) Open the `BIP66.ino` sketch in the `examples/BIP66` folder.  
2) Select your board from the Arduino IDE
3) Upload the sketch.

---

### PlatformIO

1) `cd test`
2) `cmake --build .`
3) `pio run -e esp32 -t upload`<br>_or_ `pio run -e esp8266 -t upload`

---

### OS Builds

Operating System builds like Linux, macOS, and Windows use CMake to build this BIP66 library.

1) `cmake .`
2) `cmake --build .`
3) `./test/BIP66_tests`

---

## Usage

### Check/Validate an Encoded Signature

From a DER encoded signature:

```cpp
std::vector<uint8_t> derEncodedSignature = {
    48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

const bool checked = BIP66::check(derEncodedSignature);
```

---

### Decode a Signature

From a DER encoded signature to raw r-value & s-value:

```cpp
std::vector<uint8_t> derEncodedSignature = {
    48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

std::vector<uint8_t> r(32);
std::vector<uint8_t> s(32);

const bool decoded = BIP66::decode(derEncodedSignature, r, s);
```

---

### Encode a Signature

From the raw r-value & s-value:

```cpp
std::vector<uint8_t> r = {
    33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20
};

std::vector<uint8_t> s = {
    14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

std::vector<uint8_t> rawSignatureBuffer(64);

const bool encoded = BIP66::encode(r, s, rawSignatureBuffer);
```

From a raw unencoded signature:

```cpp
std::vector<uint8_t> rawUnencodedSignature = {
    33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

std::vector<uint8_t> encodedSignatureBuffer(72);

const bool encoded = BIP66::encode(&rawUnencodedSignature[0], encodedSignatureBuffer);
```

---

## Security

If you discover a security vulnerability within this package, please send an e-mail to simon@ark.io. All security vulnerabilities will be promptly addressed.

## Credits

-   [Simon Downey](https://github.com/sleepdeficit)
-   [Chris Johnson](https://github.com/ciband)
-   [All Contributors](../../../../contributors)

## License

[MIT](LICENSE)