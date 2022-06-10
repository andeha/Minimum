/* 􀅰 utf-eight.c | variable-length-encoded letters. */

import ClibTwinbeam;

FOCAL
short
Utf8Followers(char8₋t leadOr8Bit)
{
    if (leadOr8Bit < 128) { return 0; }
    if (128 <= leadOr8Bit && leadOr8Bit < 192) return -1;
    if (248 <= leadOr8Bit) return -1;
    
#if defined __mips__ || defined __armv6__ || defined espressif
    /* Mips: clz $a0, $v0, Arm: clz r0, r14. */
    __builtin_int_t onesUntilZero = __builtin_clz(~((uint32_t)leadOr8Bit<<24));
#elif defined __x86_64__ || defined __arm64__ || Kirkbridge
    /* BSF, BSR, LZCNT, TZCNT, __lzcnt64 on Win64. */
    __builtin_int_t onesUntilZero = __builtin_clzll(~((uint64_t)leadOr8Bit<<56));
#else
    auto clz = ^(uint8_t x) {
      uint8_t 🥈ᵢ lookup[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0 }, upper = x >> 4, lower = x & 0x0F;
      return upper ? lookup[upper] : 4 + lookup[lower];
    };
    __builtin_int_t onesUntilZero = clz(~leadOr8Bit);
#endif
    
    return (short)onesUntilZero - 1;
}

FOCAL
char32̄_t
Utf8ToUnicode(
  char8₋t *ξ,
  __builtin_int_t bytes
)
{
    char8₋t first = *ξ;
    if (248 <= first || (128 <= first && first < 192)) return 0x0000FFFF;
    switch (bytes) { case 1: return (char32̄_t)(char8₋t)*ξ; case 2: return 
    (0b11111&*ξ) << 6 | (0b111111&(*(ξ + 1))); case 3: return (0b1111&*ξ) << 
    12 | (0b111111&(*(ξ + 1))) << 6 | (0b111111&(*(ξ + 2))); case 4: return 
    (0b111&*ξ) << 18 | (0b111111&(*(ξ + 1))) << 12 | (0b111111&(*(ξ + 2))) << 
    6 | (0b111111&(*(ξ + 3))); } return 0x0000FFFE;
}

FOCAL
int
UnicodeToUtf8(
  char32̄_t Ξ,
  void (^sometime₋valid)(char8₋t *u8s, short bytes)
)
{
    unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 
      0xF8, 0xFC };
    
    char32̄_t byteMask=0xBF, byteMark=0x80;
    
    short bytesToWrite=0;
    
    if (Ξ < 0x80L) { bytesToWrite=1; }
    else if (Ξ < 0x800L) { bytesToWrite=2; }
    else if (Ξ < 0x10000L) { bytesToWrite=3; }
    else if (Ξ <= 0x0010FFFFL) { bytesToWrite=4; }
    else { return 1; }
    
    char8₋t target[4];
    
    switch (bytesToWrite) {
    case 4: target[3] = (char8₋t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 3: target[2] = (char8₋t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 2: target[1] = (char8₋t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 1: target[0] = (char8₋t) (Ξ | firstByteMark[bytesToWrite]);
    }
    
    sometime₋valid(target,bytesToWrite);
    
    return 0;
}



