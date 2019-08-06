/**
 * This file is part of Ark Cpp Client.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include <Arduino.h>

#include <bip66.h>

#include <vector>

namespace testCases {  // NOLINT

const std::vector<std::vector<uint8_t>> decoded { 
  //  21704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d61140edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93
  { 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 },
  // //  38044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab584c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da
  { 56, 4, 77, 233, 118, 113, 45, 50, 251, 243, 116, 81, 194, 102, 225, 134, 126, 110, 49, 180, 230, 154, 218, 135, 146, 169, 77, 179, 32, 120, 171, 88, 76, 20, 104, 4, 204, 98, 242, 35, 29, 57, 217, 227, 175, 199, 4, 181, 30, 73, 28, 238, 12, 124, 250, 106, 195, 84, 143, 61, 180, 197, 17, 218 },
  // //  3e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff12e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9
  { 62, 66, 43, 141, 78, 75, 82, 50, 174, 110, 97, 46, 95, 67, 219, 18, 24, 91, 112, 108, 219, 187, 76, 20, 47, 173, 145, 1, 183, 48, 191, 241, 46, 76, 75, 54, 116, 28, 243, 154, 200, 197, 60, 69, 175, 119, 153, 188, 208, 1, 71, 88, 69, 165, 13, 132, 225, 228, 205, 229, 36, 39, 111, 233 },
  // //  35ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db13a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795
  { 53, 255, 27, 242, 120, 173, 161, 78, 150, 68, 67, 232, 71, 120, 253, 221, 82, 246, 188, 143, 87, 205, 134, 189, 34, 234, 184, 145, 165, 158, 93, 177, 58, 108, 221, 2, 70, 157, 59, 51, 179, 85, 13, 234, 91, 229, 184, 170, 104, 243, 210, 3, 149, 225, 133, 228, 28, 163, 116, 250, 59, 38, 215, 149 },
  // //  0094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f5422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50
  { 0, 148, 233, 61, 184, 240, 196, 17, 127, 179, 45, 44, 83, 75, 39, 112, 207, 61, 108, 205, 198, 76, 124, 218, 52, 32, 129, 175, 166, 148, 125, 63, 84, 34, 23, 111, 170, 225, 35, 3, 56, 159, 243, 81, 231, 6, 65, 23, 122, 27, 67, 134, 250, 231, 97, 63, 47, 74, 53, 55, 221, 96, 26, 80 }
};

const std::vector<std::vector<uint8_t>> encoded {
  //  3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93
  { 48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 },
  //  3044022038044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab5802204c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da
  { 48, 68, 2, 32, 56, 4, 77, 233, 118, 113, 45, 50, 251, 243, 116, 81, 194, 102, 225, 134, 126, 110, 49, 180, 230, 154, 218, 135, 146, 169, 77, 179, 32, 120, 171, 88, 2, 32, 76, 20, 104, 4, 204, 98, 242, 35, 29, 57, 217, 227, 175, 199, 4, 181, 30, 73, 28, 238, 12, 124, 250, 106, 195, 84, 143, 61, 180, 197, 17, 218 },
  //  304402203e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff102202e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9
  { 48, 68, 2, 32, 62, 66, 43, 141, 78, 75, 82, 50, 174, 110, 97, 46, 95, 67, 219, 18, 24, 91, 112, 108, 219, 187, 76, 20, 47, 173, 145, 1, 183, 48, 191, 241, 2, 32, 46, 76, 75, 54, 116, 28, 243, 154, 200, 197, 60, 69, 175, 119, 153, 188, 208, 1, 71, 88, 69, 165, 13, 132, 225, 228, 205, 229, 36, 39, 111, 233 },
  //  3044022035ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db102203a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795
  { 48, 68, 2, 32, 53, 255, 27, 242, 120, 173, 161, 78, 150, 68, 67, 232, 71, 120, 253, 221, 82, 246, 188, 143, 87, 205, 134, 189, 34, 234, 184, 145, 165, 158, 93, 177, 2, 32, 58, 108, 221, 2, 70, 157, 59, 51, 179, 85, 13, 234, 91, 229, 184, 170, 104, 243, 210, 3, 149, 225, 133, 228, 28, 163, 116, 250, 59, 38, 215, 149 },
  //  304402200094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f02205422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50
  { 48, 68, 2, 32, 0, 148, 233, 61, 184, 240, 196, 17, 127, 179, 45, 44, 83, 75, 39, 112, 207, 61, 108, 205, 198, 76, 124, 218, 52, 32, 129, 175, 166, 148, 125, 63, 2, 32, 84, 34, 23, 111, 170, 225, 35, 3, 56, 159, 243, 81, 231, 6, 65, 23, 122, 27, 67, 134, 250, 231, 97, 63, 47, 74, 53, 55, 221, 96, 26, 80 }
};

// additional test cases adapted from: https://github.com/bitcoinjs/bip66/blob/master/test/fixtures.json
namespace valid {
const std::vector<std::vector<uint8_t>> der {
  //  3044022029db2d5f4e1dcc04e19266cce3cb135865784c62ab653b307f0e0bb744f5c2aa022000a97f5826912cac8b44d9f577a26f169a2f8db781f2ddb7de2bc886e93b6844
  { 48, 68, 2, 32, 41, 219, 45, 95, 78, 29, 204, 4, 225, 146, 102, 204, 227, 203, 19, 88, 101, 120, 76, 98, 171, 101, 59, 48, 127, 14, 11, 183, 68, 245, 194, 170, 2, 32, 0, 169, 127, 88, 38, 145, 44, 172, 139, 68, 217, 245, 119, 162, 111, 22, 154, 47, 141, 183, 129, 242, 221, 183, 222, 43, 200, 134, 233, 59, 104, 68 },
  //  304302201ea1fdff81b3a271659df4aad19bc4ef83def389131a36358fe64b245632e777021f29e164658be9ce810921bf81d6b86694785a79ea1e52dbfa5105148d1f0bc1
  { 48, 67, 2, 32, 30, 161, 253, 255, 129, 179, 162, 113, 101, 157, 244, 170, 209, 155, 196, 239, 131, 222, 243, 137, 19, 26, 54, 53, 143, 230, 75, 36, 86, 50, 231, 119, 2, 31, 41, 225, 100, 101, 139, 233, 206, 129, 9, 33, 191, 129, 214, 184, 102, 148, 120, 90, 121, 234, 30, 82, 219, 250, 81, 5, 20, 141, 31, 11, 193 },
  //  304402201b19519b38ca1e6813cd25649ad36be8bc6a6f2ad9758089c429acd9ce0b572f02203bf32193c8a3a3de1f847cd6e6eebf43c96df1ffa4d7fe920f8f71708920c65f
  { 48, 68, 2, 32, 27, 25, 81, 155, 56, 202, 30, 104, 19, 205, 37, 100, 154, 211, 107, 232, 188, 106, 111, 42, 217, 117, 128, 137, 196, 41, 172, 217, 206, 11, 87, 47, 2, 32, 59, 243, 33, 147, 200, 163, 163, 222, 31, 132, 124, 214, 230, 238, 191, 67, 201, 109, 241, 255, 164, 215, 254, 146, 15, 143, 113, 112, 137, 32, 198, 95 },
  //  3044022000c8da1836747d05a6a3d2c395825edce827147d15909e66939a5037d5916e6f022017823c2da62f539d7f8e1e186eaea7a401ab3c077dcfc44aeaf3e13fac99bdbc
  { 48, 68, 2, 32, 0, 200, 218, 24, 54, 116, 125, 5, 166, 163, 210, 195, 149, 130, 94, 220, 232, 39, 20, 125, 21, 144, 158, 102, 147, 154, 80, 55, 213, 145, 110, 111, 2, 32, 23, 130, 60, 45, 166, 47, 83, 157, 127, 142, 30, 24, 110, 174, 167, 164, 1, 171, 60, 7, 125, 207, 196, 74, 234, 243, 225, 63, 172, 153, 189, 188 },
  //  3042021e2ff2609c8dc0392d3731a2c6312841e09c76f10b83e2b52604dc84886dd502200090ac80e787c063618192bc04758e6666d0179c377fb2f3d6105d58000f33ac
  { 48, 66, 2, 30, 47, 242, 96, 156, 141, 192, 57, 45, 55, 49, 162, 198, 49, 40, 65, 224, 156, 118, 241, 11, 131, 226, 181, 38, 4, 220, 132, 136, 109, 213, 2, 32, 0, 144, 172, 128, 231, 135, 192, 99, 97, 129, 146, 188, 4, 117, 142, 102, 102, 208, 23, 156, 55, 127, 178, 243, 214, 16, 93, 88, 0, 15, 51, 172 },
  //  3041021d00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb02202e7aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e9
  { 48, 65, 2, 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187, 2, 32, 46, 122, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233 },
  //  3042021d00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb0221008aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e925
  { 48, 66, 2, 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187, 2, 33, 0, 138, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233, 37 },
  //  303e021d00c1d545da2e4edfbc65e9267d3c0a6fdda41793d0fd945f15acbcf0dd021d009acffda3ca5e7c349c35ba606f0a8f1ec7815b653b51695ca9ee69a6
  { 48, 62, 2, 29, 0, 193, 213, 69, 218, 46, 78, 223, 188, 101, 233, 38, 125, 60, 10, 111, 221, 164, 23, 147, 208, 253, 148, 95, 21, 172, 188, 240, 221, 2, 29, 0, 154, 207, 253, 163, 202, 94, 124, 52, 156, 53, 186, 96, 111, 10, 143, 30, 199, 129, 91, 101, 59, 81, 105, 92, 169, 238, 105, 166 },
  //  3006020100020100
  { 48, 6, 2, 1, 0, 2, 1, 0 }
};

const std::vector<std::vector<uint8_t>> r {
  //  29db2d5f4e1dcc04e19266cce3cb135865784c62ab653b307f0e0bb744f5c2aa
  { 41, 219, 45, 95, 78, 29, 204, 4, 225, 146, 102, 204, 227, 203, 19, 88, 101, 120, 76, 98, 171, 101, 59, 48, 127, 14, 11, 183, 68, 245, 194, 170 },
  //  1ea1fdff81b3a271659df4aad19bc4ef83def389131a36358fe64b245632e777
  { 30, 161, 253, 255, 129, 179, 162, 113, 101, 157, 244, 170, 209, 155, 196, 239, 131, 222, 243, 137, 19, 26, 54, 53, 143, 230, 75, 36, 86, 50, 231, 119 },
  //  1b19519b38ca1e6813cd25649ad36be8bc6a6f2ad9758089c429acd9ce0b572f
  { 27, 25, 81, 155, 56, 202, 30, 104, 19, 205, 37, 100, 154, 211, 107, 232, 188, 106, 111, 42, 217, 117, 128, 137, 196, 41, 172, 217, 206, 11, 87, 47 },
  //  00c8da1836747d05a6a3d2c395825edce827147d15909e66939a5037d5916e6f
  { 0, 200, 218, 24, 54, 116, 125, 5, 166, 163, 210, 195, 149, 130, 94, 220, 232, 39, 20, 125, 21, 144, 158, 102, 147, 154, 80, 55, 213, 145, 110, 111 },
  //  2ff2609c8dc0392d3731a2c6312841e09c76f10b83e2b52604dc84886dd5
  { 47, 242, 96, 156, 141, 192, 57, 45, 55, 49, 162, 198, 49, 40, 65, 224, 156, 118, 241, 11, 131, 226, 181, 38, 4, 220, 132, 136, 109, 213 },
  //  00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb
  { 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187 },
  //  00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb
  { 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187 },
  //  00c1d545da2e4edfbc65e9267d3c0a6fdda41793d0fd945f15acbcf0dd
  { 0, 193, 213, 69, 218, 46, 78, 223, 188, 101, 233, 38, 125, 60, 10, 111, 221, 164, 23, 147, 208, 253, 148, 95, 21, 172, 188, 240, 221 },
  //  00
  { 0 }
};

const std::vector<std::vector<uint8_t>> s {
  //  00a97f5826912cac8b44d9f577a26f169a2f8db781f2ddb7de2bc886e93b6844
  { 0, 169, 127, 88, 38, 145, 44, 172, 139, 68, 217, 245, 119, 162, 111, 22, 154, 47, 141, 183, 129, 242, 221, 183, 222, 43, 200, 134, 233, 59, 104, 68 },
  //  29e164658be9ce810921bf81d6b86694785a79ea1e52dbfa5105148d1f0bc1
  { 41, 225, 100, 101, 139, 233, 206, 129, 9, 33, 191, 129, 214, 184, 102, 148, 120, 90, 121, 234, 30, 82, 219, 250, 81, 5, 20, 141, 31, 11, 193 },
  //  3bf32193c8a3a3de1f847cd6e6eebf43c96df1ffa4d7fe920f8f71708920c65f
  { 59, 243, 33, 147, 200, 163, 163, 222, 31, 132, 124, 214, 230, 238, 191, 67, 201, 109, 241, 255, 164, 215, 254, 146, 15, 143, 113, 112, 137, 32, 198, 95 },
  //  17823c2da62f539d7f8e1e186eaea7a401ab3c077dcfc44aeaf3e13fac99bdbc
  { 23, 130, 60, 45, 166, 47, 83, 157, 127, 142, 30, 24, 110, 174, 167, 164, 1, 171, 60, 7, 125, 207, 196, 74, 234, 243, 225, 63, 172, 153, 189, 188 },
  //  0090ac80e787c063618192bc04758e6666d0179c377fb2f3d6105d58000f33ac
  { 0, 144, 172, 128, 231, 135, 192, 99, 97, 129, 146, 188, 4, 117, 142, 102, 102, 208, 23, 156, 55, 127, 178, 243, 214, 16, 93, 88, 0, 15, 51, 172 },
  //  2e7aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e9
  { 46, 122, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233 },
  //  008aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e925
  { 0, 138, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233, 37 },
  //  009acffda3ca5e7c349c35ba606f0a8f1ec7815b653b51695ca9ee69a6
  { 0, 154, 207, 253, 163, 202, 94, 124, 52, 156, 53, 186, 96, 111, 10, 143, 30, 199, 129, 91, 101, 59, 81, 105, 92, 169, 238, 105, 166 },
  //  00
  { 0 }
};

}  //  namespace valid

namespace invalid {
namespace encoded {

const std::vector<std::vector<uint8_t>> r {
  //  R length is zero
  //  r: ""
  //  s: 0080000000000000000000000000000000000000000000000000000000000000
  {},
  //  s length is zero
  //  r: 0080000000000000000000000000000000000000000000000000000000000000
  //  s: ""
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  R value is negative
  //  r: 80
  //  s: 7f
  { 128 },
  //  S value is negative
  //  r: 7f
  //  s: 80
  { 127 },
  //  R value excessively padded
  //  r: 0010000000000000000000000000000000000000000000000000000000000000
  //  s: 0080000000000000000000000000000000000000000000000000000000000000
  { 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  S value excessively padded
  //  r: 0080000000000000000000000000000000000000000000000000000000000000
  //  s: 0010000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  R length is too long
  //  r: 00800000000000000000000000000000000000000000000000000000000000000000
  //  s: 008000000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  S length is too long
  //  r: 008000000000000000000000000000000000000000000000000000000000000000
  //  s: 00800000000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

const std::vector<std::vector<uint8_t>> s {
  //  R length is zero
  //  r: ""
  //  s: 0080000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  s length is zero
  //  r: 0080000000000000000000000000000000000000000000000000000000000000
  //  s: ""
  {},
  //  R value is negative
  //  r: 80
  //  s: 7f
  { 127 },
  //  S value is negative
  //  r: 7f
  //  s: 80
  { 128 },
  //  R value excessively padded
  //  r: 0010000000000000000000000000000000000000000000000000000000000000
  //  s: 0080000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  S value excessively padded
  //  r: 0080000000000000000000000000000000000000000000000000000000000000
  //  s: 0010000000000000000000000000000000000000000000000000000000000000
  { 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  R length is too long
  //  r: 00800000000000000000000000000000000000000000000000000000000000000000
  //  s: 008000000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  //  S length is too long
  //  r: 008000000000000000000000000000000000000000000000000000000000000000
  //  s: 00800000000000000000000000000000000000000000000000000000000000000000
  { 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

}  // namespace encoded

namespace decoded {

const std::vector<std::vector<uint8_t>> der {
  //  DER sequence length is too short
  //  ffffffffffffff
  { 255, 255, 255, 255, 255, 255, 255 },
  //  DER sequence length is too long
  //  ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
  //  Expected DER sequence
  //  00ffff0400ffffff020400ffffff
  { 0, 255, 255, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  DER sequence length is invalid
  //  30ff020400ffffff020400ffffff
  { 48, 255, 2, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  DER sequence length is invalid
  //  300c030400ffffff030400ffffff0000
  { 48, 12, 3, 4, 0, 255, 255, 255, 3, 4, 0, 255, 255, 255, 0, 0 },
  //  Expected DER integer
  //  300cff0400ffffff020400ffffff
  { 48, 12, 255, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  Expected DER integer
  //  300c020200ffffff020400ffffff
  { 48, 12, 2, 2, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  R length is zero
  //  30080200020400ffffff
  { 48, 8, 2, 0, 2, 4, 0, 255, 255, 255 },
  //  S length is zero
  //  3008020400ffffff0200
  { 48, 8, 2, 4, 0, 255, 255, 255, 2, 0 },
  //  R length is too long
  //  300c02dd00ffffff020400ffffff
  { 48, 12, 2, 221, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  S length is invalid
  //  300c020400ffffff02dd00ffffff
  { 48, 12, 2, 4, 0, 255, 255, 255, 2, 221, 0, 255, 255, 255 },
  //  R value is negative
  //  300c020480000000020400ffffff
  { 48, 12, 2, 4, 128, 0, 0, 0, 2, 4, 0, 255, 255, 255 },
  //  S value is negative
  //  300c020400ffffff020480000000
  { 48, 12, 2, 4, 0, 255, 255, 255, 2, 4, 128, 0, 0, 0 },
  //  R value excessively padded
  //  300c02040000ffff020400ffffff
  { 48, 12, 2, 4, 0, 0, 255, 255, 2, 4, 0, 255, 255, 255 },
  //  S value excessively padded
  //  300c020400ffffff02040000ffff
  { 48, 12, 2, 4, 0, 255, 255, 255, 2, 4, 0, 0, 255, 255 }
};

}  //  namespace decoded
}  //  namespace invalid

}  //  nemspace testCases

void testChecking() {
  Serial.print("\n\n========== testChecking ==========\n");

  auto matches = 0;
  for (auto& e : testCases::encoded) {
    BIP66::check(e) ? ++matches : 0;
  };
  char buf[56];
  sprintf(buf, "\n%d out of %d checks successful!\n", matches, testCases::encoded.size());
  Serial.print(buf);

  Serial.print("\n========== /testChecking ==========\n\n");
}

void testDecoding() {
  Serial.print("\n\n========== testDecoding ==========\n");

  auto matches = 0;
  for (auto& e : testCases::encoded) {
    std::vector<uint8_t> r(ELEMENT_SIZE);
    std::vector<uint8_t> s(ELEMENT_SIZE);
    const auto isDecoded = BIP66::decode(e, r, s);

    std::vector<uint8_t> unencoded;
    unencoded.insert(unencoded.begin(), r.begin(), r.end());
    unencoded.insert(unencoded.begin() + ELEMENT_SIZE, s.begin(), s.end());
 
    if (isDecoded && unencoded == testCases::decoded.at(matches)) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d decodings successful!\n", matches, testCases::encoded.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testDecoding ==========\n\n");
}

void testEncodingPair() {
  Serial.print("\n\n========== testEncodingPair ==========\n");

  auto matches = 0;
  for (auto& e : testCases::decoded) {
    std::vector<uint8_t> r;
    r.reserve(ELEMENT_SIZE);
    std::vector<uint8_t> s;
    s.reserve(ELEMENT_SIZE);
    r.insert(r.begin(), e.begin(), e.begin() + ELEMENT_SIZE);
    s.insert(s.begin(), e.begin() + ELEMENT_SIZE, e.end());

    std::vector<uint8_t> encoded(ELEMENT_SIZE * 2);
    const auto wasEncoded = BIP66::encode(r, s, encoded);
 
    if (wasEncoded &&
        encoded == testCases::encoded.at(matches) &&
        (BIP66::check(encoded))) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d encodings successful!\n", matches, testCases::decoded.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testEncodingPair ==========\n\n");
}

void testEncodingRaw() {
  Serial.print("\n\n========== testEncodingRaw ==========\n");

  auto matches = 0;
  for (auto& e : testCases::decoded) {
    std::vector<uint8_t> signature;
    signature.reserve(SIG_MAX_LEN);

    const auto encoded = BIP66::encode(e.data(), signature);

    if (encoded &&
        signature == testCases::encoded.at(matches) &&
        BIP66::check(signature)) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d encodings successful!\n", matches, testCases::decoded.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testEncodingRaw ==========\n\n");
}

void testEncodeDecode() {
  Serial.print("\n\n========== testEncodeDecode ==========\n");

  auto matches = 0;
  for (auto& e : testCases::encoded) {
    const auto checked = BIP66::check(e);

    std::vector<uint8_t> r;
    r.reserve(ELEMENT_SIZE);
    std::vector<uint8_t> s;
    s.reserve(ELEMENT_SIZE);
    const auto wasDecoded = BIP66::decode(e, r, s);

    std::vector<uint8_t> encoded(ELEMENT_SIZE * 2);
    const auto wasEncoded = BIP66::encode(r, s, encoded);

    std::vector<uint8_t> temp(SIG_MAX_LEN);
    const auto wasReDecoded = BIP66::encode(r, s, temp);
 
    (checked && wasDecoded && wasEncoded && wasReDecoded) ? ++matches : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", matches, testCases::decoded.size());
    Serial.print(buf);

  Serial.print("\n========== testEncodeDecode ==========\n\n");
}

void testShouldBeValid() {
  Serial.print("\n\n========== testShouldBeValid ==========\n");

  auto matches = 0;
  for (auto& e : testCases::valid::der) {
    const auto wasChecked = BIP66::check(e);

    std::vector<uint8_t> r;
    r.reserve(ELEMENT_SIZE);
    std::vector<uint8_t> s;
    s.reserve(ELEMENT_SIZE);
    const auto wasDecoded = BIP66::decode(e, r, s);

    std::vector<uint8_t> temp(SIG_MAX_LEN);
    const auto wasEncoded = BIP66::encode(r, s, temp);

    (wasChecked && wasDecoded && wasEncoded) ? ++matches : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", matches, testCases::valid::der.size());
    Serial.print(buf);

  Serial.print("\n========== testShouldBeValid ==========\n\n");
}

void testShouldBeValidPair() {
  Serial.print("\n\n========== testShouldBeValidPair ==========\n");

  auto matches = 0;
  for (auto& e : testCases::valid::r) {
    std::vector<uint8_t> unencoded(ELEMENT_SIZE);
    const auto wasEncoded = BIP66::encode(testCases::valid::r.at(matches),
                                          testCases::valid::s.at(matches),
                                          unencoded);

    if (wasEncoded && (BIP66::check(unencoded))) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", matches, testCases::valid::r.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testShouldBeValidPair ==========\n\n");
}

void testShouldBeInvalidEncode() {
  Serial.print("\n\n========== testShouldBeInvalidEncode ==========\n");

  auto misses = 0;
  for (auto& e : testCases::invalid::encoded::r) {
    std::vector<uint8_t> signature;
    signature.reserve(SIG_MAX_LEN);

    const auto isInvalid = !BIP66::encode(
                              testCases::invalid::encoded::r.at(misses),
                              testCases::invalid::encoded::s.at(misses),
                              signature) ||
                           !BIP66::check(signature);

    isInvalid ? ++misses : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", misses, testCases::invalid::encoded::r.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testShouldBeInvalidEncode ==========\n\n");
}

void testShouldBeInvalidDecode() {
  Serial.print("\n\n========== testShouldBeInvalidDecode ==========\n");

  auto misses = 0;
  for ( auto& e : testCases::invalid::decoded::der) {
    !BIP66::check(e) ? ++misses : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", misses, testCases::invalid::decoded::der.size());
    Serial.print(buf);
    
  Serial.print("\n========== /testShouldBeInvalidDecode ==========\n\n");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  testChecking();
  testEncodingPair();
  testEncodingRaw();
  testDecoding();
  testEncodeDecode();
  testShouldBeValid();
  testShouldBeValidPair();
  testShouldBeInvalidEncode();
  testShouldBeInvalidDecode();
}

void loop() { }
