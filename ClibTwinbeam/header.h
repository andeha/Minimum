/*  􀪀 ClibTwinbeam.h | the Swift and Twinbeam bridge for Si and O₂. */


#if !defined __cplusplus
#define inexorable
#define structᵢ struct
#define unionᵢ union
#define MACRO static inline INLINED
#else
#define MACRO inline INLINED
#define unionᵢ union __attribute__ ((internal_linkage))
#define structᵢ struct __attribute__((internal_linkage))
#define inexorable static __attribute__ ((internal_linkage))
#endif /* ⬷ see 'nm' for details. */
#define INLINED __attribute__((always_inline))
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
#if defined  __mips__ || defined __armv6__ || defined espressif
typedef unsigned long       uint32_t;
typedef long                int32_t;
typedef uint32_t            __builtin_uint_t;
typedef int32_t             __builtin_int_t;
#define TriboolUnknown 0xFFFFFFFF
#define TriboolUninit 0xFFFFFFFE
#define TriboolUnarbitrated 0xFFFFFFFD
#define 𝟷𝟸𝟾₋bit₋integers /* ⬷ flag -fforce-enable-int128 when Mips. */
#ifdef __MM__
#undef 𝟷𝟸𝟾₋bit₋integers
#endif
#elif defined __armv8a__ || defined __x86_64__
typedef unsigned int        uint32_t;
typedef int                 int32_t; /* ≢'long'. */
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /* ⬷ a․𝘬․a 'sequenta'. */
/* #define 𝟷𝟸𝟾₋bit₋swift₋integers */
#define 𝟷𝟸𝟾₋bit₋integers
/* #define 𝟷𝟸𝟾₋bit₋integers₋with₋calling₋conventions */
#define TriboolUnknown 0xFFFFFFFFFFFFFFFF
#define TriboolUninit 0xFFFFFFFFFFFFFFFE
#define TriboolUnarbitrated 0xFFFFFFFFFFFFFFFD
#endif
typedef short               int16_t; /* ≡ ᵐⁱᵖˢint. */
typedef unsigned short      uint16_t; /* cf. Q16. */
typedef __builtin_uint_t Tribool; /* ⬷ cf․ 'obekant', 'icke-lös' and 'embargo-₍im₎material'. */
#define FOCAL /* ⬷ embossed inexorable. */
#define TROKADERO /* atomic calling convention. (Similar to Ieee754 Nan and Opt<double>.) */ 
#define LEAF /* will at run-time be executed without non-atomicity and 'call' instructions. */
#define ATOMIC /* will be executed without task switch and does not effect yield. */
#define SELDOM /* long-running and will be executed without task switch and is uncontaining 'yield'. */
#define QUOTE(str) #str
#define ΨΛΩ ((void *)0)
#define ᶿ﹡ *

#if defined  __mips__ || defined __armv6__ || defined espressif
#define BUILTIN₋INT₋MAX 2147483647
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
#define BUILTIN₋INT₋MAX 0x7FFFFFFFFFFFFFFF
#endif /* ~0b0>>1 */
/* ⬷ the constant INT₋MAX is an odd number. */

#if defined(𝟷𝟸𝟾₋bit₋swift₋integers) && defined(𝟷𝟸𝟾₋bit₋integers) && defined(𝟷𝟸𝟾₋bit₋integers₋with₋calling₋conventions)
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all);
#else
int Details_in_C(uint64_t pid, int32_t cross);
#endif

#define BITMASK(type) enum : type
#if defined  __mips__
#define Mips __asm__ __volatile__ (/* ".set noat   \n" */ ".set noreorder  \n" ".set nomacro    \n"
#elif defined __x86_64__
#define Intel👈 __asm { .intel_syntax noprefix /* ⬷ requires -fms-extensions */
#define IntelPlusATT👉 asm { .att_syntax .text
#elif defined __armv6__ || defined __armv8a__
#define ArmDS1S2 asm {
#endif

MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t 
 /* volatile */ *) var); }
#if defined __cplusplus
MACRO __builtin_uint_t&  🔧(__builtin_uint_t var) { return (__builtin_uint_t&) 
 *(__builtin_uint_t /* volatile */ *)var; }
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return 
 sizeof(x)*8; } x=(x^(x-1))>>1; int c=0; for (; x; c++) { x >>= 1; } return c; }
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask, 
 void (^update)(__builtin_uint_t& shifted) = ^(__builtin_uint_t&) { } ) {
 __builtin_uint_t word = *symbol, shift=TrailingZeros(mask), orig = mask&word,
 shifted = orig>>shift; if (update) update(shifted); __builtin_uint_t fresh =
 (shifted<<shift)&mask; *symbol = (word & ~mask) | fresh; return orig>>shift; }
#endif

#if !defined(__cplusplus)
typedef unsigned char char8_t; typedef unsigned int /* not uint32_t */ char32_t;
#endif

struct Bitfield { const char32_t * regular; uint32_t mask; const char32_t * text; };
struct AnnotatedRegister { const char32_t * header; int regcnt; struct Bitfield * regs; 
 uint32_t init; const char32_t * footnote; };
typedef struct Bitfield Explained[];

#if defined __cplusplus
#define EXT₋C extern "C"
#define EXT₋C₂ EXT₋C {
#define EXT₋C₋FROM }
#else
#define EXT₋C₋FROM
#define EXT₋C₂
#define EXT₋C
#endif

EXT₋C void NumberformatCatalogue₋Present(
  struct AnnotatedRegister /* Explained */ * ar, 
  uint32_t numerics, 
  int is₋𝟷𝟼₋bits, 
  /* void (^sometime)(int count, char32_t * terminated₋ucs) */
  void (^out)(char8_t * u8s, __builtin_int_t bytes)
);

#define APPEND_PIMPL                                                         \
  struct Internals;                                                          \
  Internals * impl_;
#define 😐 APPEND_PIMPL }

#define a⃝ __attribute__((overloadable))

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* ⬷ a․𝘬․a '__block'. */

EXT₋C FOCAL void Base𝕟(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned 
 short base, unsigned short digitsOr0, /* Not more than 32 alt. 64 digits 
 depending on word size! (Or set to `0` to skip leading zeros.) */ void
 (^out)(char 𝟶to𝟿)) a⃝;
EXT₋C void Base𝕫(__int128_t ℤ, unsigned short base, unsigned short digitsOr0, 
 void (^out)(char 𝟶to𝟿and₋)) a⃝;
EXT₋C void Base𝕟(__uint128_t ℕ, unsigned short base, unsigned short digitsOr0, 
 void (^out)(char 𝟶to𝟿)) a⃝;
EXT₋C void Base𝕫(__builtin_int_t ℤ, unsigned short base, unsigned short digitsOr0,
 void (^output)(char 𝟬to𝟵and₋)) a⃝;

#define false 0
#define true (! false)

struct 𝟽bit₋text { __builtin_int_t bytes; signed char * start; };
struct utf8₋text { __builtin_int_t bytes; char8_t * start; };
struct Unicodes { __builtin_int_t tetras; char32_t * start; };

EXT₋C char32_t Utf8ToUnicode(char8_t *ξ, __builtin_int_t bytes);
EXT₋C int UnicodeToUtf8(char32_t Ξ, void (^sometime₋valid)(char8_t *u8s, short bytes));
EXT₋C short Utf8Followers(char8_t leadOr8Bit);
/* ⬷ The C language char32_t is typealias CChar32 = Unicode.Scalar. */

EXT₋C int IsPrefixOrEqual(const char * 𝟽alt𝟾₋bitstring, const char * 𝟽alt𝟾₋bitprefix);

#define UNITTEST(symbol) extern "C" void Unittest_##symbol()
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",            \
  ﹟s(s), ﹟s(__FUNCTION__), ﹟s(__FILE__), ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog,s); } }
EXT₋C int atexit(void(*func)(void));
EXT₋C void exit(int status);
EXT₋C void Symbols(const char * utf8exepath, void (^each₋symbol)(const char * 
 sym, uint64_t addr, int * stop));

#pragma mark precision and the 128-bits physical bound

union Q6463 { __uint128_t bits; __int128_t frac; };
struct sequent { union Q6463 detail; int valid; };
typedef struct sequent (^computational)(struct sequent x);
enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done };
/* ⬷ for n₋root (non-0-1), sincos, log₃, lnΓ, 2ˣ, modulo, tanh, tanh⁻¹ and Erf. */
/* enum CastToSequentOpinion { accept, rejecting, negate, complete, annul }; */
typedef struct sequent Sequent;
EXT₋C₂
inexorable void int₋to₋sequent(int64_t ℤ, Sequent * ℝ);
inexorable void rounded₋fraction(int count₋upto𝟼𝟺, short 𝟶to𝟿s[], Sequent * ℝ);
/* ⬷ a․𝘬․a digits_to_sequent and 'decimaltxt₋2⁻ⁱ₋round'. See TeX 102 §. */
void print₋sequent(Sequent 𝕏, void (^digits)(int neg, struct 𝟽bit₋text 
 integers, struct 𝟽bit₋text fracts), void (^zero₋alt₋nonused)(), 
 void (^nonvalid)()); /* ⬷ TeX 103 §. */
Sequent add_sequent(Sequent x₁, Sequent x₂);
Sequent minus_sequent(Sequent x₁, Sequent x₂);
void multiply(__uint128_t x₁, __uint128_t x₂, __uint128_t * std, uint64_t * int₋hi, uint64_t * hi₋prec);
Sequent mult_sequent(Sequent x₁, Sequent x₂);
Sequent reciproc_sequent(Sequent yb);
Sequent div_sequent(Sequent x₁, Sequent x₂, int integer₋division); 
/* the symbol 'div' requires __attribute__((overloadable)); */
Sequent product₋abelian(); /* ⬷ a․𝘬․a '1'. */
Sequent accumulative₋zero(); /* ⬷ a․𝘬․a '0'. */
Sequent piano₋ten(); /* ⬷ a․𝘬․a '10'. */
Sequent negative₋infinity(); /* ⬷ a․𝘬․a -Inf. */
Sequent sequent₋floor(Sequent x);
Sequent operator_minus(Sequent x);
Sequent mod_sequent(Sequent x₁, Sequent x₂);
int Newton(computational f, computational f₋prim, Sequent * x₀, 
 void (^ping)(enum Newtoncontrol * ctrl));
Sequent 𝟷𝟸𝟹𝟺₋atan(Sequent y, Sequent x);
int trapezoid(Sequent (^f)(Sequent), Sequent delta₋t, 
 Sequent min, void (^memory)(Sequent integrale, 
 Sequent t₋acc, int * stop));
EXT₋C₋FROM

#define __builtin_fixpoint_add add_sequent
#define __builtin_fixpoint_sub minus_sequent
#define __builtin_fixpoint_mul mult_sequent
#define __builtin_fixpoint_div div_sequent
#define __builtin_fixpoint_rcp reciproc_sequent
/* #define __builtin_fixpoint_sqrt 
#define __builtin_fixpoint_rsqrt
#define __builtin_fixpoint_fmadd(a,b,c)
#define __builtin_fixpoint_min
#define __builtin_fixpoint_max */

struct intel₋sequent₋pair { struct sequent inner[2]; };
typedef struct intel₋sequent₋pair simd256_t;

#pragma mark pythagorean-euclidean and the half type as described in Ieee754-2008

/*** Ieee 754 base-2 half with double-zero (-1)ˢ(1+m*2⁻¹⁰)×2ˣ⁻¹5 ***
                                                                             
 Binary16_SGN ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit
 Binary16_EXP ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|␣xxx|xx␣␣|␣␣␣␣|␣␣␣␣| Signed ex̳ponent -16 to 16 (biased)
 Binary16_MAN ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|␣␣␣␣|␣␣xx|xxxx|xxxx| Fraction/mantissa/significand (10 bits)
                                                                             
 The significand encodes the serie 1 + ∑ k⁻ⁱ where 1 <= k < 11.  (...and not k ∈ [0,9].)
                                                                             
*/

typedef unsigned short half; /* ⬷ not 'typedef _Float16 half' and 
 not 'typedef pythagorean_double half', in Swift already named Float16 and 
 made unavailable in macos. */

BITMASK (uint32_t /* and not 'unsigned short' */) {
  Binary16_SGN = 0x8000, /* sign bit. */
  Binary16_EXP = 0b11111<<10, /* signed exponent -16 to 16. */
  Binary16_MAN = 0x3ff /* fraction/mantissa/significand. */
};

#if defined __armv8a__
typedef __attribute__ ((neon_vector_type(4))) float float32x4_t;
typedef __attribute__ ((neon_vector_type(8))) __fp16 float16x8_t;
#elif defined __x86_64__
typedef half __attribute__ ((__vector_size__(16), __aligned__(16))) __v8hf;
typedef float __attribute__ ((__vector_size__(16), __aligned__(16))) __m128;
typedef float __attribute__ ((__vector_size__(16), __aligned__(16))) __v44f;
typedef __v8hf __m128i; typedef __m128i panko; /* ⬷ in Swift already named SIMD8. On Intel VCVTPH2PS and _m256 _mm256_cvtph_ps ( __m128i m1). */
typedef __v8hf simd_t₈; /* ⬷ a․𝘬․a float16x8_t. */
#endif

#if defined __x86_64__
typedef double __attribute__ ((__vector_size__(16), __aligned__(16))) __m128d;
typedef __m128d simd_tᵦ;
#elif defined __armv8a__
typedef __attribute__ ((neon_vector_type(2))) double float64x2_t;
typedef float64x2_t simd_tᵦ;
#endif

#define IEEE754BASE2_16BIT_PZERO 0b0000000000000000
#define IEEE754BASE2_16BIT_NZERO 0b1000000000000000
#define IEEE754BASE2_16BIT_ONE   0b0011110000000000
#define IEEE754BASE2_16BIT_PINF  0b0111110000000000
#define IEEE754BASE2_16BIT_NINF  0b1111110000000000
#define IEEE754BASE2_16BIT_MAX   0b0111101111111111 /* 𝟲𝟱𝟱𝟬𝟰 (i․𝘦 𝗠𝗔𝗫 when `half` precision.) */
#define IEEE754BASE2_16BIT_EARLY 0b1111101111111111 /* ⬷ -65504. */
/* IEEE754BASE2_16BIT_SNAN and IEEE754BASE2_16BIT_QNAN n/a. */
#define HALF_EPS1 1.0009765625 /* 1+2⁻¹⁰ …maybe 2⁻¹¹. */

typedef union { /* Encodes values between 2⁻¹⁴ to 2⁻¹⁵ or 3․1×10⁻⁵ to 6․5×10⁴. */
   struct { int8_t lsh; uint8_t msh; } signed_little_endian;
   struct { uint8_t msh; int8_t lsh; } unsigned_big_endian;
   struct { /* ⬷ surprisingly not big endian when using colon, in both cases little-endian. ⤐ */
     unsigned mantissa : 10;
     unsigned exponent :  5;
     unsigned sign     :  1;
   } binary16; /* ⬷ a․𝘬․a `ieee754_2008`. */
   struct {
     unsigned fraction : 7;
     unsigned exponent : 8;
     unsigned sign     : 1;
   } bfloat16; /* ⬷ ubiquitous. ARMv8.6-A and 𝘦.𝘨 'BFCVT'. */
   unsigned short bits;
   half location;
} pythagorean_double;

/* When 'typedef _Float16 two₋half;' them]n `two₋half x[] = { 1.2, 3.0, 3.e4 };` */

#define simd_init₈ vdupq_n_f16
/* #define simd_init₈(x) { float16x8_t z = { x, 1,2,3,4,5,6,7 }; uint32_t y = vgetq_lane_f16(z,0); return y; } */
#define __builtin_simd_add₈ __arm_vaddq_f16
#define __builtin_simd_sub₈ __arm_vsubq_f16
#define __builtin_simd_mul₈ __arm_vmulq_f16 /* VMUL.F16 Qd,Qn,Qm */
#define __builtin_simd_div₈ __arm_vdivq_f16
#define __builtin_simd_rcp₈ __arm_vinvq_f16
#define __builtin_simd_sqrt₈ __arm_vrsqrte_f16
#define __builtin_simd_rsqrt₈ __arm_vinvsqrtq_f16
#define __builtin_simd_fmadd₈(a,b,c) __arm_vfmaq_f16(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_min₈ __arm_vminq_f16
#define __builtin_simd_max₈ __arm_vmaxq_f16
#define simd_scalar₈(x) __arm_vgetq_lane_f16(x,0)
/* ⬷ +mve and +mve.fp. */

EXT₋C double To₋doubleprecision(/* unsigned short */ half x);

EXT₋C void NumberformatCatalogue₋Presentᵧ(half val, 
 /* void (^sometime)(int count, char32_t * terminated₋ucs) */ 
 void (^out)(char8_t * u8s, __builtin_int_t bytes));

EXT₋C void * (^Alloc)(__builtin_int_t); EXT₋C void (^Fall⒪⒲)(void *);

/* __builtin_int_t 𝟺𝟶𝟿𝟼₋aligned₋frame(__builtin_int_t byte₋number, __builtin_int_t * modulo); */
struct 𝟺kbframes { __builtin_int_t page₋count; __builtin_uint_t *pages₋base, * idx₋avails; };
/* ⬷ a․𝘬․a expeditionary and 'void * pages[]'/'uint32_t avails[]'. */
EXT₋C₂
int Acquire𝟷ᵈ(__builtin_int_t ﹟, struct 𝟺kbframes * one₋set, void (^every)(uint8_t 
 * 𝟸ⁿ₋frame, int * stop));
int Release𝟷ᵈ(void * 𝟸ⁿ₋frame, struct 𝟺kbframes * one₋set, int secure);
void Init₋frames(unsigned count, unsigned expeditionaries[]);
int ContiguousAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟);
int CoalescingAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟);
int 🄕allo⒲(unsigned expeditionary, void **𝟺kbpages, __builtin_int_t ﹟);
/* void intel₋/mips₋mzda₋Reservoir(unsigned expeditionary, 𝟺kbframes * one₋set, 
 __builtin_int_t * pages₋in₋expedition); */
EXT₋C₋FROM

EXT₋C void * Heap₋alloc(__builtin_int_t bytes);
EXT₋C void Heap₋unalloc(void * p);
EXT₋C void * Heap₋realloc(void * p, __builtin_int_t to₋bytes);

typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
EXT₋C int Compare8Memory(ByteAlignedRef p₁, ByteAlignedRef p₂, __builtin_uint_t bytes);
EXT₋C ByteAlignedRef Overwrite8Memory(ByteAlignedRef src, uint8_t val,
 __builtin_int_t bytes);
EXT₋C ByteAlignedRef Copy8Memory(ByteAlignedRef dst, ByteAlignedRef src, 
 __builtin_int_t bytes);

#define MEASURE_START(prefix) int64_t prefix##Start = __rdtsc();
#define MEASURE_END(prefix)                                                  \
 int64_t prefix##End = (int64_t)cycles();                                    \
 int64_t prefix##Nanos = prefix##End - prefix##Start;                        \
 print(#prefix " measures ⬚ ns\n", ﹟d(prefix##Nanos));
static inline uint32_t __dwt_cyccnt() { return *(volatile unsigned *)0xe0001004; }
#if defined __armv8a__
#define cycles __dwt_cyccnt
#elif defined __x86_64__
#define cycles __rdtsc
#endif

#define rt₋namespace namespace /* ⬷ a library (an .a-file) consists of functions, not variables. */
#define Pult💡(x) ++x

struct distance { half length; int unit; };
enum Image₋kind { PNGrgba8 };
struct PngRGBA8Pixel { uint8_t R,G,B,A; };
union Image₋rectangle { struct PngRGBA8Pixel * pngRgba8; /* ⬷ 𝘤𝘧․ Scatter. */ };
struct Image { int scanlines, columns, pixelsize; int unpurged; 
 union Image₋rectangle material; int kind; /* ∈[1,7] */ };
struct Cropped₋image { struct Image picture; };
struct Plate { struct Cropped₋image image; int unit; };
EXT₋C int Init₋image(struct Image * image, int secure);
EXT₋C int Release₋image(struct Image * image);

EXT₋C int mfprint(const char * utf8format, ...);
EXT₋C int print(void (^out)(char8_t * u8s, __builtin_int_t bytes), 
 const char * utf8format, ...) a⃝;
EXT₋C int print(const char * utf8format, ...) a⃝;

#ifndef __cplusplus
typedef int bool;
#define Wordbytes (sizeof(__builtin_uint_t))
static inline __builtin_int_t Syspagesize() { return 4096; }
#else
#define WHEN_COMPILING constexpr static
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /* ⬷ must be assigned to a 'const' and no inline assembler. */
#define NOT_EVERYTIME const static
#define 🥇 NOT_EVERYTIME
template <typename T> T * Critic(const T * x) { return const_cast<T*>(x); }
template <typename T> T& Critic(const T &x) { return const_cast<T&>(x); } /* ⬷ a․𝘬․a "away 𝙘𝙤𝙣𝙨𝙩 evil". */
__builtin_int_t 🥈 Wordbytes=sizeof(__builtin_uint_t);
__builtin_int_t constexpr Syspagesize() { return 4096; }
#endif

#if defined __cplusplus
constexpr
#else
inline
#endif
__builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize)
{ return (__builtin_int_t)((size + framesize - 1) & ~(framesize - 1)); }
/* ⬷ may be evaluated at compile-time a․𝘬․a 'constexpr'. */

typedef void (^Argᴾ₋Unicode)(bool anfang, char32_t * prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, 
 void * context);
typedef void (*Argᴾ₋Unicode₂)(bool anfang, char32_t * prvNxtEOTOr0x0000, 
 void * context₁, void * context₂);
typedef void (^Argᴾ₋output)(Argᴾ₋Unicode set, void * context); /* ⬷ C and C++. */
typedef void (*Argᴾ₋output₂)(Argᴾ₋Unicode₂ set, void * context); /* ⬷ C, C++ and Swift. */

struct Lambda₋2 { Argᴾ₋output scalar; void * context; };
struct Lambda { Argᴾ₋output₂ scalar; void * context; };
struct Chapter { struct Plate * anfang; struct Unicodes ingress; };

typedef struct Arg₋𝓟 {
 union { __builtin_int_t d; __builtin_uint_t x, b; char8_t * u8s; 
  char8_t c; char32_t uc; double f₁; float f₂; struct Unicodes ucs;
  uint8_t paddingbytes[16];
#if defined 𝟷𝟸𝟾₋bit₋integers
  __uint128_t U; __int128_t I;
#endif
  uint64_t hi₋and₋lo₋128bits[2];
  struct Lambda₋2 λ₂;
  struct Lambda λ;
  struct Chapter chapter;
 } value;
 int kind;
} Argᴾ;

EXT₋C Argᴾ ﹟d(__builtin_int_t d);
EXT₋C Argᴾ ﹟x(__builtin_uint_t x);
EXT₋C Argᴾ ﹟b(__builtin_uint_t b);
EXT₋C Argᴾ ﹟s(char8_t * u8s) a⃝;
EXT₋C Argᴾ ﹟s(const char8_t * u8s) a⃝;
EXT₋C Argᴾ ﹟s(const /* signed */ char * s) a⃝;
EXT₋C Argᴾ ﹟s(/* signed */ char * s) a⃝;
EXT₋C Argᴾ ﹟S₁(__builtin_int_t tetras, char32_t * unterminated₋uc) a⃝;
EXT₋C Argᴾ ﹟S₁(__builtin_int_t tetras, const char32_t * unterminated₋uc) a⃝;
EXT₋C Argᴾ ﹟c(/* signed */ char c) a⃝;
EXT₋C Argᴾ ﹟c(char8_t c) a⃝;
EXT₋C Argᴾ ﹟C(char32_t C);
#if defined(𝟷𝟸𝟾₋bit₋integers)
EXT₋C Argᴾ ﹟U(__uint128_t U);
EXT₋C Argᴾ ﹟I(__int128_t I);
#endif
EXT₋C Argᴾ ﹟F(double f, int format);
EXT₋C Argᴾ ﹟λ(Argᴾ₋output₂ scalar, void * context);
EXT₋C Argᴾ ﹟chapter(struct Unicodes ingress, struct Plate * anfang);
/* ⬷ PRO|29|17. See also PRO|3|30. */
EXT₋C Argᴾ ﹟S₂(char32_t * zero₋terminated₋uc);

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref)))

struct fifo { __builtin_uint_t * 𝟷₋tile; 
 __builtin_int_t brk, count, words₋to₋unity;
};

EXT₋C int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * 𝟷₋tile);
EXT₋C void 𝟷₋tile₋fifo₋pop(struct fifo * 🅵);
EXT₋C int 𝟷₋tile₋copy₋include(struct fifo * 🅵, __builtin_int_t ﹟, 
 __builtin_uint_t * words);
EXT₋C int 𝟷₋tile₋shiftout(struct fifo * 🅵, __builtin_int_t words);

struct structa {
  __builtin_int_t cached₋number, tile₋count, bytes₋per₋tile, unused₋bytes;
  void * treelist, *cached₋tile;
};

typedef struct structa Structa;
typedef void * (^Leaf₋alloc)(short bytes);
EXT₋C int structa₋init(Structa * 🅢, __builtin_int_t bytes₋per₋tile);
EXT₋C int structa₋lengthen(Structa * 🅢, __builtin_int_t ﹟, void * 
 fixedKbframes[], Leaf₋alloc leaf₋alloc);
EXT₋C uint8_t * structa₋relative₋alt₋zero(Structa * 🅢, __builtin_int_t 
 byte₋offset);
EXT₋C int structa₋copy₋append(Structa * 🅢, __builtin_int_t bytes, 
 uint8_t * material, void (^inflate)(__builtin_int_t ﹟, int * cancel));
EXT₋C __builtin_int_t structa₋bytes(Structa * 🅢);
/* auto leaf₋alloc = ^(int bytes) { return malloc(bytes); };
 let register₋reflect = { (mask: __builtin_uint_t) -> Void in print("") } 
 as @convention(block) (__builtin_uint_t) -> Void */
/* the 'overloadable' attribute in C-code not yet found in Swift code. */
/* also page with table idx|offset. */

union Tetra𝘖rUnicode { int32_t count; char32_t uc; };
typedef __builtin_int_t Nonabsolute; /* ⬷ index to symbols in swift Array<UInt32>. */

typedef void (^Text₋dealloc)(void *);
typedef void (^Node₋dealloc)(void *);
typedef void * (^Node₋alloc)(__builtin_int_t bytes);
typedef void * (^Text₋alloc)(__builtin_int_t bytes);

EXT₋C int rope₋append₋text(void ᶿ﹡* opaque, union Tetra𝘖rUnicode * length₋prefixed₋text, 
 Text₋dealloc dealloc₂, Node₋dealloc dealloc₁, void * (^heap₋alloc)(
 __builtin_int_t bytes)); /* ⬷ the 'Tetra𝘖rUnicode * length₋prefixed₋text' is a․𝘬․a 'text𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶'. */
EXT₋C int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, 
 void ᶿ﹡ wedge, Text₋dealloc dealloc₂, Node₋dealloc dealloc₁, 
 Node₋alloc nalloc, Text₋alloc talloc);
EXT₋C int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, 
 __builtin_int_t len, Text₋dealloc dealloc₂, Node₋dealloc dealloc₁, 
 Node₋alloc nalloc, Text₋alloc talloc);
EXT₋C __builtin_int_t rope₋length(void ᶿ﹡ opaque);
EXT₋C char32_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx);
EXT₋C void unalloc₋rope(void ᶿ﹡ opaque, Node₋dealloc dealloc₁, 
 Text₋dealloc dealloc₂);

struct debripaper { }; /* ⬷ a․𝘬․a 'bits₋on₋tiles' and usb-planetary. */
struct two₋command₋queue { };

struct smallpool { struct structa symbol₋storage; void ᶿ﹡ opaque; };

EXT₋C int init₋smallpool(struct smallpool * 🅿, __builtin_int_t 
 tetras₋per₋tile, __builtin_int_t count, void * kbXtiles[], Leaf₋alloc 
 leaf₋alloc);
EXT₋C int optional₋uninit₋smallpool(struct smallpool * 🅿, Text₋dealloc 
 dealloc₂, Node₋dealloc dealloc₁);
EXT₋C int inflate₋smallpool(struct smallpool * 🅟, __builtin_int_t count, 
 void * kbXtiles[], Leaf₋alloc alloc);
EXT₋C int copy₋append₋text(struct smallpool * 🅟, int count, char32_t cs[], 
 Nonabsolute * ref, void (^inflate)(__builtin_int_t ﹟, void **kbXtiles, 
 int * cancel));
EXT₋C int datum₋text(struct smallpool * 🅟, int32_t tetras);
EXT₋C union Tetra𝘖rUnicode * at(struct smallpool * 🅟, Nonabsolute relative);
EXT₋C int textual₋similar(struct smallpool * 🅟, struct Unicodes uc₁, 
 Nonabsolute relative);
#if defined 𝟷𝟸𝟾₋bit₋integers
EXT₋C void ᶿ﹡ store₋impression(struct smallpool * 🅟, __uint128_t fineprint, 
 Leaf₋alloc alloc);
EXT₋C void ᶿ﹡ seek₋impression(struct smallpool * 🅟, __uint128_t fineprint);
#endif
/* ⬷ operating system releases allocated memory space when program ends. */
/* ⬷ enough space to store all Unicode symbols in an utf-8 file 
 may be found from the file's byte length. */

struct ¹stack { uint8_t * words; 
  __builtin_int_t size, elem₋bytesize, pos;
   void * (^initial₋area₋alloc)(__builtin_int_t);              /* ⬷ init₋stack */
   void (^area₋dealloc)(void *);                               /* ⬷ stack₋unalloc */
   void * (^area₋realloc)(void * p, __builtin_int_t to₋bytes); /* ⬷ push */
}; /* ⬷ a․𝘬․a machinestack. */

EXT₋C int init₋stack(struct ¹stack * 🆇, short bytes₋per₋elem) a⃝;
EXT₋C void stack₋unalloc(struct ¹stack * 🆇) a⃝;
EXT₋C int push(struct ¹stack * 🅧, uint8_t * item) a⃝;
EXT₋C uint8_t * pop(struct ¹stack * 🅧) a⃝;
EXT₋C int empty(struct ¹stack * 🅧) a⃝;

typedef uint64_t chronology₋instant;
typedef uint32_t chronology₋UQ32;
typedef int32_t chronology₋relative;
struct chronology₋date { int32_t y,m,d; };
struct chronology₋time { int32_t h,m,s; chronology₋UQ32 partials; };
EXT₋C struct chronology₋date chronology₋date(chronology₋instant timestamp);
EXT₋C struct chronology₋time chronology₋sinceMidnight(chronology₋instant timestamp);
EXT₋C int chronology₋integers₋encode(int32_t parts[6], chronology₋UQ32 frac, chronology₋instant * instant);
EXT₋C chronology₋instant chronology₋addSeconds(chronology₋instant relative, uint32_t seconds, chronology₋UQ32 frac);
EXT₋C chronology₋instant chronology₋subtractSeconds(chronology₋instant relative, uint32_t seconds, chronology₋UQ32 frac);
EXT₋C int chronology₋dayofweek(chronology₋instant timestamp, int * wd);

#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
union treeint { struct { int64_t key; uint64_t val; } keyvalue; __uint128_t bits; };
#elif defined __mips__ || defined __armv6__ || defined espressif
union treeint { struct { int32_t key; uint32_t val; } keyvalue; uint64_t bits; };
#endif

typedef union treeint Treeint;
EXT₋C void * Insert(void ᶿ﹡ opaque, Treeint valkey, void * (^alloc)(short bytes));
EXT₋C void Forall(void ᶿ﹡ opaque, void (^dfs)(Treeint valkey, int * stop));
EXT₋C Treeint * Lookup(void ᶿ﹡ opaque, Treeint leafkey);
struct node { Treeint payload; struct node *right, *left; };

#define CARDINALS(...) enum Cardinal { __🄦hole=0, __VA_ARGS__ };           \
  static jmp_buf __snapshot;                                                \
  typedef void (^CSession)(enum Cardinal sin);                              \
  CSession confess = ^(enum Cardinal sin) { longjmp(__snapshot, (int)sin); };
#define NEARBYCROSS                                                         \
  int __ctrl = setjmp(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS

#define va_epilogue __builtin_va_end(__various);
#define va_prologue(symbol)                                                 \
 __builtin_va_list __various;                                               \
 __builtin_va_start(__various, symbol);

enum Impediment { MustBeOrdered, JustSwap };
struct Peekey { __builtin_int_t board₁, palm₂; };
EXT₋C int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, 
 enum Impediment it); TROKADERO SELDOM

typedef int pid_t;

EXT₋C pid_t Twinbeam₋spawn(const char * pathandcommand₋u8s, const char * 
 command₋u8s, int * fd_p2c, int * fd_c2p /*, const char * NULLterminatedEnv */);

EXT₋C int Twinbeam₋mmap(const char * canonicalUtf8RegularOrLinkpath, 
 __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
 __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
 void * outcome);

EXT₋C void * mapfileʳᵚ(const char * canonicalUtf8RegularOrLinkpath, 
 __builtin_int_t, __builtin_int_t , __builtin_int_t, __builtin_int_t *);

typedef half Artnumerical;
/* ⬷ and neither 'struct sequent' nor 'struct Artnumerical { half value; }' for Swift half literal. */

struct A₋point { Artnumerical x,y; };
struct Illustration { double size, place₋origo, offset₋drawing₋on; };
EXT₋C int Draw₋Bezier(int columns, int count, struct Illustration * ctxt, struct A₋point, ...);
/* ⬷ arbitrary number of other points. ⤐ */
typedef void (^Visual)(struct Plate layer, bool * stop);
EXT₋C int Set₋text(struct Unicodes symbols, struct A₋point start, int mode, Visual plates);
EXT₋C int Define₋image(struct 𝟽bit₋text regular, char base₋23, int ansamla);
EXT₋C int Place₋image(struct 𝟽bit₋text regular, struct A₋point p₁, struct A₋point p₂, int mode);
typedef struct A₋point A₋size; /* ⬷ a․𝘬․a ground₋size alt․ nested₋size. */

#if defined __mips__ && !defined NON₋SIMD
extern v2f64 __builtin_msa_cast_to_vector_double(double);
#define simd_initᵦ __builtin_msa_cast_to_vector_double
#define __builtin_simd_addᵦ __builtin_msa_fadd_d
#define __builtin_simd_subᵦ __builtin_msa_fsub_d
#define __builtin_simd_mulᵦ __builtin_msa_fmul_d
#define __builtin_simd_divᵦ __builtin_msa_fdiv_d
#define __builtin_simd_rcpᵦ __builtin_msa_frcp_d
#define __builtin_simd_sqrtᵦ __builtin_msa_fsqrt_d
#define __builtin_simd_rsqrtᵦ __builtin_msa_frsqrt_d
#define __builtin_simd_fmaddᵦ(a,b,c) __builtin_msa_fmadd_d(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_minᵦ __builtin_msa_fmin_d
#define __builtin_simd_maxᵦ __builtin_msa_fmax_d
#elif defined __armv8a__ && !defined NON₋SIMD
#define simd_initᵦ vmovq_n_f64
#define __builtin_simd_addᵦ vaddq_f64
#define __builtin_simd_subᵦ vsubq_f64
#define __builtin_simd_mulᵦ vmulxq_f64
#define __builtin_simd_divᵦ vdivq_f64
#define __builtin_simd_rcpᵦ vrecpsq_f64
#define __builtin_simd_sqrtᵦ vrsqsq_f64
#define __builtin_simd_rsqrtᵦ vrsqrtsq_f64
#define __builtin_simd_fmaddᵦ(a,b,c) vmlaq_f64(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_minᵦ vminq_f64
#define __builtin_simd_maxᵦ vmaxq_f64
#elif defined __x86_64__
#define simd_initᵦ _mm_set1_pd
#define __builtin_simd_addᵦ _mm_add_pd
#define __builtin_simd_subᵦ _mm_sub_pd
#define __builtin_simd_mulᵦ _mm_mul_pd
#define __builtin_simd_divᵦ _mm_div_pd
#define __builtin_simd_rcpᵦ _mm_rcp_pd
#define __builtin_simd_sqrtᵦ _mm_sqrt_pd
#define __builtin_simd_rsqrtᵦ _mm_rsqrt_pd
#define __builtin_simd_fmaddᵦ(a,b,c) _mm_fmadd_pd(a,b,c) /* ⬷ a₁*a₂ + a₃. */
#define __builtin_simd_minᵦ _mm_min_pd
#define __builtin_simd_maxᵦ _mm_max_pd
#endif

#define max(x₁, x₂) ((x₁) < (x₂) ? (x₂) : (x₁))
#define min(x₁, x₂) ((x₂) < (x₁) ? (x₂) : (x₁))


