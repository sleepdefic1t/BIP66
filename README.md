# BIP66

> A simple Bitcoin BIP66 Implementation in C++ for the ARK Ecosystem.

ANS.1 DER Encoder/Decoder based on [Bitcoin BIP66](https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki).

[![GitHub Actions](https://github.com/sleepdefic1t/BIP66/workflows/GitHub%20Actions/badge.svg)](https://github.com/sleepdefic1t/BIP66)
[![CodeFactor](https://www.codefactor.io/repository/github/sleepdefic1t/bip66/badge)](https://www.codefactor.io/repository/github/sleepdefic1t/bip66)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/3828f000e03d45ba86997addd00834c0)](https://www.codacy.com/manual/sleepdefic1t/BIP66)
[![Latest Version](https://badgen.now.sh/github/release/sleepdefic1t/BIP66)](https://github.com/sleepdefic1t/BIP66/releases)
[![License: MIT](https://badgen.now.sh/badge/license/MIT/green)](https://opensource.org/licenses/MIT)

## Supported Platforms

| IoT:        | supported: |
| :---------- | :--------: |
| Arduino IDE | [x]        |
| PlatformIO  | [x]        |

| OS Platform: | supported: |
| :----------- | :--------: |
| Linux        | [x]        |
| macOS        | [x]        |
| Windows      | [x]        |

| Boards: | supported: |
| :------ | :--------: |
| ESP8266 | [x] |
| ESP32   | [x] |

## Installation

### Dependencies

- IoT:
  - **Arduino IDE**: N/A
  - **PlatformIO**: AUnit
- OS:
  - **Linux**: CMake,
  - **macOS**: CMake
  - **Windows**: CMake
  > _Unit Testing: Git is required for the GoogleTest submodule_

---

### Arduino IDE

1) Open the `BIP66.ino` sketch in the `examples/BIP66` folder.  
2) Select your board from the Arduino IDE
3) Upload the sketch.

---

### PlatformIO

#### Building the Library

- `pio run`

#### Building the Library with Tests

- `pio run -t test/`

#### Uploading and Running Tests

- `pio run -t test/ -e esp32 -t upload`

---

### OS Builds

Operating System builds like Linux, macOS, and Windows use CMake to build this BIP66 library.  
This build should be done out of source.

#### Building the Library

1) `mkdir build && cd build`
2) `cmake ..`
3) `cmake --build .`

#### Building the running Tests

1) `mkdir build && cd build`
2) `cmake -DBUILD_BIP66_TESTS=ON ..`
3) `cmake --build .`
4) `./test/bip66_tests`

---

## Usage

### Encode a Signature

From the raw R & S elements:

```cpp
uint8_t r[32] = {
    33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20
};

uint8_t s[32] = {
    14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

uint8_t signature[72];

const bool success = bip66::encode(r, 32, s, 32, signature);
```

---

### Decode a Signature

From a DER-encoded signature to raw R & S elements:

```cpp
uint8_t derEncodedSignature[70] = {
    48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

uint8_t r[32];
uint8_t s[32];

const bool success = bip66::decode(derEncodedSignature, 70, r, s);
```

---

### Check/Validate an Encoded Signature

From a DER-encoded signature:

```cpp
const uint8_t derEncodedSignature[70] = {
    48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147
};

const bool success = bip66::check(derEncodedSignature, 70);
```

---

## License

[MIT](LICENSE) © [Simon Downey](https://github.com/sleepdefic1t)
