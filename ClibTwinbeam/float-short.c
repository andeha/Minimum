/*  float-short.c | half precision - 16-bit - with conversions routines. */

import ClibTwinbeam;

float
#if defined __x86_64__
__attribute__ ((target("f16c")))
#endif
half₋to₋float(half /* unsigned short */ 𝟷𝟼₋bits)
{
#if defined __armv8a__
  float16x4_t a = { 𝟷𝟼₋bits, 0, 0, 0 };
  float32x4_t b = vcvt_f32_f16(a);
  return b[0];
#elif defined __x86_64__
  __v8hf v = { 𝟷𝟼₋bits, 0, 0, 0, 0, 0, 0, 0 };
  __v44f non₋double = (__v44f)__builtin_ia32_vcvtph2ps(v);
  return non₋double[0]; /* defined as _cvtsh_ss in 'f16cintrin.h'. */
#endif
}

double To₋doubleprecision(/* unsigned short */ half 𝟷𝟼₋bits)
{
  return (double)half₋to₋float(𝟷𝟼₋bits);
}

struct /* formerly register */ Bitfield Binary16[] = {
  { U"Binary16_SGN", Binary16_SGN, U"sign bit" },
  { U"Binary16_EXP", Binary16_EXP, U"signed exponent -126 to 127" },
  { U"Binary16_MAN", Binary16_MAN, U"fraction/mantissa/significand" }
}; /* E𝘨․ pct․, meters and inches. */

struct AnnotatedRegister AR_Binary16 = {
  U"Binary16: The Ieee 754-2008 half precision type", 
  3, Binary16, 0x00000000, 
  U"Encodes values between 2⁻¹⁴ to 2⁻¹⁵ or 3․1×10⁻⁵ to 6․5×10⁴."
};

void NumberformatCatalogue₋Presentᵧ(half val, /* void (^out)(char32_t uc) */ 
 void (^out)(char8₋t * u8s, __builtin_int_t bytes))
{
  pythagorean_double dbl = { .location=val };
  uint32_t bits = dbl.bits;
  extern struct AnnotatedRegister AR_Binary16;
  NumberformatCatalogue₋Present(&AR_Binary16,bits,true,out);
}

BITMASK (uint64_t) { /* Sse flags and 0b1xx for MXCSR.RC rounding. */
  Round₋to₋nearest₋even = 0b00, 
  Round₋down₋toward₋neginf = 0b01, 
  Round₋up₋toward₋inf = 0b10, 
  Round₋toward₋zero₋truncate = 0b11 /* ⬷ identical to the SSE flag register. */
};

half
#if defined __x86_64__
__attribute__ ((target("f16c")))
#endif
float₋to₋half(float 𝟹𝟸₋bits)
{
#if defined __armv8a__X
  float16x8_t a = { 0, 0, 0, 0, 0, 0, 0, 0 };
  float32x4_t b = { 𝟹𝟸₋bits, 0, 0, 0 }, 
   c = __builtin_arm_mve_vcvttq_f16_f32(a,b); // __arm_vcvttq_f16_f32
  return c[0];
#elif defined __x86_64__
  /* int const f16imm = Round₋to₋nearest₋even; */
 #define f16imm Round₋to₋nearest₋even
  __m128 four₋floats = (__m128){𝟹𝟸₋bits,0,0,0};
  __v8hf eight₋floats = __builtin_ia32_vcvtps2ph(four₋floats,f16imm);
  uint16_t a₋half = (unsigned short)eight₋floats[0];
  pythagorean_double dbl = { .bits=a₋half };
  return dbl.location;
#else
  return 0.0;
#endif
} /* 8 times is named __builtin_ia32_vcvtph2ps256 and __builtin_ia32_vcvtps2ph256. */


