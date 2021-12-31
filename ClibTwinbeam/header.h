/*  􀪀 ClibTwinbeam.h | the Swift and Twinbeam bridge for Si and O₂. */


#if !defined __cplusplus
#define MACRO static inline INLINED
#define unionᵢ union
#define structᵢ struct
#else
#define MACRO inline INLINED
#define unionᵢ union __attribute__ ((always_inline))
#define structᵢ struct __attribute__((always_inline))
#endif /* ⬷ see 'nm' for details. */
#define inexorable static INLINED
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
typedef unsigned short      uint16_t; /* 𝘊f․ Q16. */
typedef __builtin_uint_t Tribool; /* ⬷ c𝘧․ 'obekant', 'icke-lös' and 'embargo-₍im₎material'. */
#define FOCAL /* ⬷ embossed inexorable. */
#define TROKADERO /* atomic calling convention. (Similar to Ieee754 Nan and Opt<double>.) */
#define LEAF /* will at run-time be executed without non-atomicity and 'call' instructions. */
#define ATOMIC /* will be executed without task switch and does not effect yield. */
#define SELDOM /* long-running and will be executed without task switch and is uncontaining 'yield'. */
#define QUOTE(str) #str
#define ΨΛΩ ((void *)0)
#define ᶿ﹡ *
/* #define ■ 1
#define □ 0 */

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
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return 
 sizeof(x)*8; } x=(x^(x-1))>>1; int c=0; for (; x; c++) { x >>= 1; } return c; }
#if !defined(__cplusplus)
MACRO __builtin_uint_t * 🔧(__builtin_uint_t var) { return (__builtin_uint_t *)var; }
#else
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask, 
 void (^update)(__builtin_uint_t& shifted) = ^(__builtin_uint_t&) { } ) {
 __builtin_uint_t word = *symbol, shift=TrailingZeros(mask), orig = mask&word,
 shifted = orig>>shift; if (update) update(shifted); __builtin_uint_t fresh =
 (shifted<<shift)&mask; *symbol = (word & ~mask) | fresh; return orig>>shift; }
MACRO __builtin_uint_t& 🔧(__builtin_uint_t var) { return (__builtin_uint_t&) 
 *(__builtin_uint_t /* volatile */ *)var; }
#endif

typedef uint8_t char8₋t; /* ⬷ a․𝘬․a 'utf-8 byte'. The flag -fno-char8_t 
 deactivates the unused c++ builtin type char8_t not found in llvm-c source. */
typedef unsigned int char32̄_t; /* ⬷ from uchar.h and do-not-use-char32_t. */
/* A C language U"abc" is of 'const unsigned int' width and a c++ language 
 U"abc" is 'const char32_t *'. */

struct Bitfield { const char32̄_t * regular; uint32_t mask; const char32̄_t * text; };
struct AnnotatedRegister { const char32̄_t * header; int regcnt; struct Bitfield * regs; 
 uint32_t init; const char32̄_t * footnote; };
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
  void (^out)(char8₋t * u8s, __builtin_int_t bytes)
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

struct 𝟽bit₋text { __builtin_int_t count; signed char * keyputs; };
/* the flag '-fsigned-char' forces plain char to be signed. */
struct utf8₋text { __builtin_int_t bytes; char8₋t * u8s; };
struct Unicodes { __builtin_int_t tetras; char32̄_t * unicodes; };

#define KEYPUTS(x) ((signed char *)(x))
#define UC(x) ((char32̄_t *)(U##x))
#define U8(x) ((char8₋t *)(u8##x))
#define UNICODES(s) ᵊ(UC(s))

EXT₋C char32̄_t Utf8ToUnicode(char8₋t *ξ, __builtin_int_t bytes);
EXT₋C int UnicodeToUtf8(char32̄_t Ξ, void (^sometime₋valid)(char8₋t *u8s, short bytes));
EXT₋C short Utf8Followers(char8₋t leadOr8Bit);
/* ⬷ The C language char32_t is typealias CChar32 = Unicode.Scalar. */

EXT₋C int IsPrefixOrEqual(const char * 𝟽alt𝟾₋bitstring, const char * 𝟽alt𝟾₋bitprefix);
/* ⬷ downward from 127 the ASCII table is del, ~, }, |, {, z, y, ... */
EXT₋C __builtin_int_t TetrasUntilNull(char32̄_t * ucs, __builtin_int_t maxtetras);
EXT₋C __builtin_int_t Utf8BytesUntilNull(char8₋t * u8s, __builtin_int_t maxutf8bytes);
EXT₋C __builtin_int_t ExactUtf8bytes(char32̄_t * ucs, __builtin_int_t maxtetras);

#define UNITTEST(symbol) EXT₋C void Unittest_##symbol()
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",            \
 ﹟s7((char *)s), ﹟s7((char *)__FUNCTION__), ﹟s7((char *)__FILE__),        \
 ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog,s); } }
EXT₋C int atexit(void(*func)(void));
EXT₋C void exit(int status);
EXT₋C void Symbols(const char * utf8exepath, void (^each₋symbol)(const char * 
 sym, uint64_t addr, int * stop));

/*  the 128-bits precision arithmetics. */

union Q6364 { __uint128_t bits; __int128_t frac; };
struct sequent { union Q6364 detail; int valid; };
typedef struct sequent Sequenta;
typedef struct sequent (^computational)(struct sequent x);
enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done };
/* ⬷ for n₋root (non-0-1), sincos, log₃, lnΓ, 2ˣ, modulo, tanh, tanh⁻¹ and Erf. */
/* enum CastToSequentOpinion { accept, rejecting, negate, complete, annul }; */
EXT₋C₂
void int₋to₋sequent(int64_t ℤ, Sequenta * ℝ);
void rounded₋fraction(int count₋upto𝟼𝟺, short 𝟶to𝟿s[], 
 Sequenta * ℝ); /* ⬷ See TeX 102 §. */
Sequenta add_sequent(Sequenta x₁, Sequenta x₂);
Sequenta subtract_sequent(Sequenta x₁, Sequenta x₂);
Sequenta multiply_sequent(Sequenta x₁, Sequenta x₂);
Sequenta divide_sequent(Sequenta x₁, Sequenta x₂, int integer₋division);
Sequenta absolute_sequent(Sequenta x);
Sequenta negate_sequent(Sequenta x);
Sequenta floor_sequent(Sequenta x);
Sequenta modulo_sequent(Sequenta x₁, Sequenta x₂);
Sequenta product₋abelian(); /* ⬷ a․𝘬․a '1'. */
Sequenta accumulative₋zero(); /* ⬷ a․𝘬․a '0'. */
Sequenta piano₋ten(); /* ⬷ a․𝘬․a '10'. */
Sequenta negative₋infinity(); /* ⬷ a․𝘬․a -Inf. */
void print₋sequent(Sequenta 𝕏, void (^digits)(int neg, struct 𝟽bit₋text 
 integers, struct 𝟽bit₋text fracts), void (^zero₋alt₋nonused)(), 
 void (^nonvalid)()); /* ⬷ TeX 103 §. */
int Newton(computational f, computational f₋prim, Sequenta * x₀, 
 void (^ping)(enum Newtoncontrol * ctrl));
Sequenta 𝟷𝟸𝟹𝟺₋atan(Sequenta y, Sequenta x);
int trapezoid(Sequenta (^f)(Sequenta), Sequenta delta₋t, 
 Sequenta min, void (^memory)(Sequenta integrale, 
 Sequenta t₋acc, int * stop)); /* see [Inside Interesting 
 Integrals, Paul J. Nahin, Undergraduate Lecture Notes in 
 Physics, Springer Nature, Switzerland, 2020] for insights. */
EXT₋C₋FROM

#define __builtin_fixpoint_add add_sequent
#define __builtin_fixpoint_sub subtract_sequent
#define __builtin_fixpoint_mul multiply_sequent
#define __builtin_fixpoint_div divide_sequent
#define __builtin_fixpoint_negate negate_sequent
#define __builtin_fixpoint_modulo modulo_sequent
#define __builtin_fixpoint_floor floor_sequent
/* #define __builtin_fixpoint_sqrt
#define __builtin_fixpoint_rsqrt
#define __builtin_fixpoint_fmadd(a,b,c)
#define __builtin_fixpoint_min
#define __builtin_fixpoint_max */

struct intel₋sequent₋pair { struct sequent inner[2]; };
typedef struct intel₋sequent₋pair simd256_t;

/* pythagorean-euclidean and the half type as described in Ieee754-2008 */

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
typedef __attribute__ ((neon_vector_type(2))) double float64x2_t;
typedef float64x2_t simd_tᵦ;
#elif defined __x86_64__
typedef half __attribute__ ((__vector_size__(16), __aligned__(16))) __v8hf;
typedef float __attribute__ ((__vector_size__(16), __aligned__(16))) __m128;
typedef float __attribute__ ((__vector_size__(16), __aligned__(16))) __v44f;
typedef __v8hf __m128h; typedef __m128h panko; /* ⬷ in Swift already named SIMD8. On Intel VCVTPH2PS and _m256 _mm256_cvtph_ps ( __m128i m1). */
typedef __v8hf simd_t₈; /* ⬷ a․𝘬․a float16x8_t. */
typedef double __attribute__ ((__vector_size__(16), __aligned__(16))) __m128d;
typedef __m128d simd_tᵦ;
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

#if defined __armv8q__ && !defined NON₋SIMD
#define simd_init₈ vdupq_n_f16
/* #define simd_init₈(x) { float16x8_t z = { x, 1,2,3,4,5,6,7 }; uint32_t y = vgetq_lane_f16(z,0); return y; } */
#define __builtin_simd_add₈ vaddq_f16
#define __builtin_simd_sub₈ vsubq_f16
#define __builtin_simd_mul₈ vmulq_f16 /* VMUL.F16 Qd,Qn,Qm. */
#define __builtin_simd_div₈ vdivq_f16
#define __builtin_simd_rcp₈ vrecpeq_f16
#define __builtin_simd_sqrt₈ vsqrtq_f16
#define __builtin_simd_rsqrt₈ vrecpsq_f16
#define __builtin_simd_fmadd₈(a,b,c) vfmaq_f16(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_min₈ vminq_f16
#define __builtin_simd_max₈ vmaxq_f16
#define simd_scalar₈(x) vgetq_lane_f16(x,0)
#elif defined __mips__ && !defined NON₋SIMD
#elif defined __x86_64__
#define simd_init₈ _mm_set1_ph
#define __builtin_simd_add₈ _mm_add_ph
#define __builtin_simd_sub₈ _mm_sub_ph
#define __builtin_simd_mul₈ _mm_mul_ph
#define __builtin_simd_div₈ _mm_div_ph
#define __builtin_simd_rcp₈ _mm_rcp_ph /* VRCPPH */
#define __builtin_simd_sqrt₈ _mm_sqrt_ph
#define __builtin_simd_rsqrt₈ _mm_rsqrt_ph
#define __builtin_simd_fmadd₈ _mm_fmadd_sh
#define __builtin_simd_max₈ _mm_max_ph
#define __builtin_simd_min₈ _mm_min_ph
#define simd_scalar₈(x) _mm_cvtsh_h
#endif

EXT₋C double To₋doubleprecision(/* unsigned short */ half x);

EXT₋C void NumberformatCatalogue₋Presentᵧ(half val, 
 /* void (^sometime)(int count, char32_t * terminated₋ucs) */ 
 void (^out)(char8₋t * u8s, __builtin_int_t bytes));

EXT₋C void * (^Alloc)(__builtin_int_t); EXT₋C void (^Fall⒪⒲)(void *);
EXT₋C void * (^Realloc)(void * p, __builtin_int_t to₋bytes);

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
EXT₋C __builtin_int_t Heap₋object₋size(void * p);
EXT₋C void * Heap₋realloc(void * p, __builtin_int_t to₋bytes);
EXT₋C void Heap₋unalloc(void * p);

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
union Image₋rectangle { struct PngRGBA8Pixel * pngRgba8; /* ⬷ c𝘧․ Scatter. */ };
struct Image { int scanlines, columns, pixelsize; int unpurged; 
 union Image₋rectangle material; int kind; /* ∈[1,7] */ };
struct Cropped₋image { struct Image picture; };
struct Plate { struct Cropped₋image image; int unit; };
EXT₋C int Init₋image(struct Image * image, int secure);
EXT₋C int Release₋image(struct Image * image);

EXT₋C int mfprint(const char * utf8format, ...);
EXT₋C int print(void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
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

typedef void (*Argᴾ₋output₋p)(struct Unicodes set, void * context); /* ⬷ C, C++ and Swift. */
typedef void (^Argᴾ₋output₋b)(struct Unicodes set, void * context); /* ⬷ C and C++. */
struct Lambda₋b { Argᴾ₋output₋b scalar; void * context; };
struct Lambda₋p { Argᴾ₋output₋p scalar; void * context; };
struct Chapter { struct Plate * anfang; struct Unicodes ingress; };
/* typedef void (^Argᴾ₋Unicode)(bool anfang, char32_t * prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, 
 void * context);
typedef void (*Argᴾ₋Unicode₂)(bool anfang, char32_t * prvNxtEOTOr0x0000, 
 void * context₁, void * context₂); */

typedef struct Arg₋𝓟 {
 union { __builtin_int_t d; __builtin_uint_t x, b; char8₋t * u8s; 
  char8₋t c; char32̄_t uc; double f₁; float f₂; struct Unicodes ucs;
  struct 𝟽bit₋text text₁; struct utf8₋text text₂;
  uint8_t paddingbytes[16];
#if defined 𝟷𝟸𝟾₋bit₋integers
  __uint128_t U; __int128_t I;
#endif
  uint64_t hi₋and₋lo₋128bits[2];
 } value;
 int kind;
 struct Lambda₋b λ₋b;
 struct Lambda₋p λ₋p;
 struct Chapter chapter;
} Argᴾ;

EXT₋C Argᴾ ﹟d(__builtin_int_t d);
EXT₋C Argᴾ ﹟x(__builtin_uint_t x);
EXT₋C Argᴾ ﹟b(__builtin_uint_t b);
EXT₋C Argᴾ ﹟s8(const char8₋t * u8s) a⃝;
EXT₋C Argᴾ ﹟s7(const /* signed */ char * s) a⃝;
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, const char32̄_t * unterminated₋uc) a⃝;
EXT₋C Argᴾ ﹟S(const char32̄_t * zero₋terminated₋uc) a⃝;
EXT₋C Argᴾ ﹟s7(__builtin_int_t characters, const /* signed */ char * s) a⃝;
EXT₋C Argᴾ ﹟s8(__builtin_int_t bytes, const char8₋t * u8s) a⃝;
EXT₋C Argᴾ ﹟c7(/* signed */ char c) /* a⃝ */;
EXT₋C Argᴾ ﹟c8(char8₋t c) /* a⃝ */;
EXT₋C Argᴾ ﹟C(char32̄_t C);
#if defined(𝟷𝟸𝟾₋bit₋integers)
EXT₋C Argᴾ ﹟U(__uint128_t U);
EXT₋C Argᴾ ﹟I(__int128_t I);
#endif
EXT₋C Argᴾ ﹟λ₋p(Argᴾ₋output₋p scalar, void * context);
/* EXT₋C Argᴾ ﹟λ₋b(Argᴾ₋output₋b scalar, void * context); */
EXT₋C Argᴾ ﹟chapter(struct Unicodes ingress, struct Plate * anfang);
/* ⬷ PRO|29|17. See also PRO|3|30. */
EXT₋C Argᴾ ﹟F(double f, int format);
/* EXT₋C Argᴾ ﹟H(half h); */
/* EXT₋C Argᴾ ﹟S128(struct sequent s); */

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref)))

struct fifo { __builtin_uint_t * 𝟷₋tile; 
 __builtin_int_t brk, count, words₋to₋unity;
};

EXT₋C int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * 𝟷₋tile);
EXT₋C void 𝟷₋tile₋fifo₋pop(struct fifo * 🅵);
EXT₋C int 𝟷₋tile₋copy₋include(struct fifo * 🅵, __builtin_int_t ﹟, 
 __builtin_uint_t * words);
EXT₋C int 𝟷₋tile₋shiftout(struct fifo * 🅵, __builtin_int_t words);

typedef __builtin_uint_t structa₋middle₋index;

struct structa {
  structa₋middle₋index * index;
  __builtin_int_t item₋count, middleindex₋count, 
   last₋middleindex₋availables, last₋tile₋availables;
  unsigned bytes₋per₋item, bytes₋per₋tile, 
   pointers₋per₋middleindex;
}; /* ⬷ a․𝘬․a Tape and primary-memory so not '__builtin_int_t cached₋number; 
 void *cached₋tile'. */

EXT₋C int structa₋init(unsigned bytes₋per₋item, unsigned 
 bytes₋per₋tile, struct structa * 🅰);
EXT₋C int copy₋append₋items(__builtin_int_t count₋not₋bytes, void * 
 bytesequence₋objects, struct structa * 🅐);
EXT₋C uint8_t * structa₋at(__builtin_int_t idx, struct structa * 🅐);
EXT₋C __builtin_int_t structa₋bytes(struct structa * 🅐);
EXT₋C int deinit₋structa(struct structa * 🅰);
/* ...also pages with table index and offset. */
/* ...the 'overloadable attribute in C-code not yet found in Swift code. */
/* let register₋reflect = { (mask: __builtin_uint_t) -> Void in print("") } 
 as @convention(block) (__builtin_uint_t) -> Void */
/* do not forget in main.cpp alternatively main.c (i.e 'once'):
auto Fall⒪⒲ = ^(void * p) { Heap₋unalloc(p); };
auto Alloc = ^(__builtin_int_t bytes) { return Heap₋alloc(bytes); };
here not:
typedef void * (^Leaf₋alloc)(short bytes);
auto leaf₋alloc = ^(int bytes) { return malloc(bytes); }; */
typedef struct structa Structa;

struct two₋memory {
  void (*text₋dealloc)(void *);
  void (*node₋dealloc)(void *);
  void * (*node₋alloc)(__builtin_int_t bytes);
  void * (*text₋alloc)(__builtin_int_t bytes);
  __builtin_int_t (*text₋bytesize)(void *);
};

typedef char32̄_t * unicode₋shatter; /* and 'Heap₋object₋size' for length of text. */
EXT₋C void unalloc₋shatter(unicode₋shatter shat);
EXT₋C unicode₋shatter branch₋to₋shatter(struct Unicodes ucs);
EXT₋C int rope₋append₋text(void ᶿ﹡* opaque, unicode₋shatter text, 
 struct two₋memory dynmem);
EXT₋C int rope₋insert(void ᶿ﹡* opaque, __builtin_int_t idx, 
 void ᶿ﹡ wedge, struct two₋memory dynmem);
EXT₋C int rope₋delete(void ᶿ﹡* opaque, __builtin_int_t idx, 
 __builtin_int_t len, struct two₋memory dynmem);
EXT₋C __builtin_int_t rope₋length(void ᶿ﹡ opaque);
EXT₋C char32̄_t rope₋index(void ᶿ﹡ opaque, __builtin_int_t idx);
EXT₋C void unalloc₋rope(void ᶿ﹡ opaque, struct two₋memory dynmem);
/* ⬷ a․𝘬․a mutable₋string, radio₋editor, recollect₋transmit and remmingway. */

/* struct geometrypaper { }; / * ⬷ a․𝘬․a 'bits₋on₋tiles' and usb-planetary. * /
struct two₋command₋queue { }; */

union Tetra𝘖rUnicode { int32_t count; char32̄_t uc; };
typedef __builtin_int_t Nonabsolute; /* ⬷ index to symbols in swift Array<UInt32>. */

EXT₋C int init₋regularpool(struct structa * 🅿);
EXT₋C int optional₋uninit₋regularpool(struct structa * 🅿);
EXT₋C int copy₋append₋onto₋regular(struct structa * 🅟, int32_t tetras, char32̄_t cs[]);
EXT₋C int regularpool₋datum₋text(struct structa * 🅟, int32_t tetras, Nonabsolute * reference);
EXT₋C struct Unicodes regularpool₋at(struct structa * 🅟, Nonabsolute relative);
/* ⬷ note operating system releases allocated memory space and pages when program ends. */
/* ⬷ enough space to store all Unicode symbols in an utf-8 file 
 may be found from the file's byte length. */

#if defined 𝟷𝟸𝟾₋bit₋integers
struct regularprint { void ᶿ﹡ opaque; };
typedef void * (^Leaf₋alloc)(__builtin_int_t bytes);
/* EXT₋C int textual₋similar(struct symbolpool * 🅡, struct Unicodes uc₁, 
 Nonabsolute relative); */
EXT₋C void ᶿ﹡ store₋impression(struct regularprint * 🅡, __uint128_t fineprint, 
 Leaf₋alloc alloc);
EXT₋C void ᶿ﹡ seek₋impression(struct regularprint * 🅡, __uint128_t fineprint);
#if defined __cplusplus
template <typename Note> Note * jot(Unicodes regular, struct regularprint * 🅡)
{
  __uint128_t fineprint = 0;
  void ᶿ﹡ node = seek₋impression(🅡,fineprint);
  if (node == ΨΛΩ) {
    Leaf₋alloc leaf₋alloc = ^(__builtin_int_t bytes) { return Alloc(bytes); };  
    void ᶿ﹡ node2 = store₋impression(🅡,fineprint,leaf₋alloc);
  } else { return ;}
}
#endif
#endif

struct poecilonyme { struct structa symbols; void ᶿ﹡ opaque; 
  unsigned (*norm)(struct Unicodes alt₁, struct Unicodes alt₂);
};
int form₋ōnymon(struct Unicodes key, struct Unicodes value, int shares, 
 struct poecilonyme * 🅓);
int dissociate₋isolate(struct Unicodes key, struct Unicodes value);
int evidence₋related(struct Unicodes key, void (^right)(int count, 
 struct Unicodes value[], unsigned distance[]), struct poecilonyme * 🅓);
int thesaurus₋init(struct poecilonyme * 🅳);
int uninit₋thesaurus(struct poecilonyme * 🅳);
/* ⬷ a․𝘬․a 'company', 'association', 'thesaurus', liability₋alt₋indemnity 
 and 'unicode₋map'. */

struct ¹stack { uint8_t * words; 
 __builtin_int_t size, elem₋bytesize, pos;
 void * (^initial₋area₋alloc)(__builtin_int_t);              /* ⬷ init₋stack */
 void (^area₋dealloc)(void *);                               /* ⬷ stack₋unalloc */
 void * (^area₋realloc)(void * p, __builtin_int_t to₋bytes); /* ⬷ push */
}; /* ⬷ a․𝘬․a machinestack. */

EXT₋C int init₋stack(struct ¹stack * 🆇, short bytes₋per₋element) a⃝;
EXT₋C void stack₋unalloc(struct ¹stack * 🆇) a⃝;
EXT₋C int push(struct ¹stack * 🅧, uint8_t * item) a⃝;
EXT₋C uint8_t * pop(struct ¹stack * 🅧) a⃝;
EXT₋C __builtin_int_t count(struct ¹stack * 🅧) a⃝;
EXT₋C int empty(struct ¹stack * 🅧) a⃝;
EXT₋C uint8_t * top(struct ¹stack * 🅧) a⃝;
typedef struct ¹stack Stack;

typedef uint64_t chronology₋instant;
typedef uint32_t chronology₋UQ32;
typedef int32_t chronology₋Q31;
struct chronology₋relative { int32_t seconds; chronology₋Q31 frac; };
struct chronology₋date { int32_t y,M,d; }; /* 1-12 and 1-31 */
struct chronology₋time { int32_t h,m,s; chronology₋UQ32 partial; };
EXT₋C struct chronology₋date chronology₋date(chronology₋instant instant);
EXT₋C struct chronology₋relative chronology₋since₋midnight₁(chronology₋instant ts);
EXT₋C struct chronology₋time chronology₋since₋midnight₂(chronology₋instant ts);
EXT₋C chronology₋instant chronology₋timestamp(int32_t parts[6], chronology₋UQ32 frac);
EXT₋C chronology₋instant add₋seconds(chronology₋instant relative, uint32_t 
 seconds, chronology₋UQ32 frac);
EXT₋C chronology₋instant subtract₋seconds(chronology₋instant relative, 
 uint32_t seconds, chronology₋UQ32 deduct₋frac);
EXT₋C int chronology₋dayofweek(chronology₋instant instant, int * wd);
EXT₋C void Present₋instant(chronology₋instant instant, int incl₋frac, 
 void (^out)(char digitHyphenColonPeriodOrSpace));

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

EXT₋C int Twinbeam₋mmap(char8₋t * canonicalUtf8RegularOrLinkpath, 
 __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
 __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
 uint8_t ** material);

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
EXT₋C int Define₋image(struct 𝟽bit₋text regular, char base₋22, int ansamla);
EXT₋C int Place₋image(struct 𝟽bit₋text regular, struct A₋point p₁, struct A₋point p₂, int mode);
typedef struct A₋point A₋size; /* ⬷ a․𝘬․a ground₋size alt․ nested₋size. */

typedef __builtin_int_t version₋ts;
struct timeserie { Structa pendings; void * currents, *uncommits; 
 Structa points, versions, events, temporals; 
 version₋ts *revision, earliest; unsigned short checkpoint₋modulo; };
enum timeserie₋operation { ts₋create, ts₋update, ts₋delta, ts₋remove };
union historypod {
  __uint128_t machineunsigned;
  simd_tᵦ two₋real;
  union Q6364 fixed;
};

EXT₋C int timeserie₋init(version₋ts * revision, version₋ts earliest, 
 unsigned short snapshot₋cycle, struct timeserie * 🅹);
EXT₋C void timeserie₋uninit(struct timeserie * 🅹);
EXT₋C void timeserie₋rollback(struct timeserie * 🅙);
struct timeserie₋entry { struct Unicodes key; union historypod entry; 
 struct 𝟽bit₋text reference; };
typedef union historypod (*Timeserie₋summation)(union historypod x₁, union historypod x₂);
typedef void (^Row₋completed)(version₋ts revision, struct timeserie₋entry row, int * bye);
EXT₋C int timeserie₋commit(version₋ts * revision, Row₋completed persisted, 
 struct timeserie * 🅙, Timeserie₋summation addition);
EXT₋C int timeserie₋first(struct timeserie * 🅙, version₋ts * instant);
EXT₋C int timeserie₋last(struct timeserie * 🅙, version₋ts * instant);
EXT₋C int timeserie₋end(struct timeserie * 🅙, version₋ts * instant);
EXT₋C int timeserie₋remove(struct Unicodes key, struct timeserie * 🅙);
EXT₋C int timeserie₋create(struct timeserie₋entry * initial, struct timeserie * 🅙);
EXT₋C int timeserie₋delta(struct timeserie₋entry * relative, union historypod * 
 current, struct timeserie * 🅙, Timeserie₋summation addition);
EXT₋C int timeserie₋update(struct timeserie₋entry * absolute, struct timeserie * 🅙);
EXT₋C void state₋before(int count, struct Unicodes keys[], version₋ts ordin, void 
 (^search₋found)(int count, struct timeserie₋entry row[], int permanent[]), 
 struct timeserie * 🅙, Timeserie₋summation addition);
EXT₋C void state₋after(int count, struct Unicodes keys[], version₋ts ordin, void 
 (^search₋found)(int count, struct timeserie₋entry row[], int permanent[]), 
 struct timeserie * 🅙, Timeserie₋summation addition);
EXT₋C void Present₋timeserie₋overview(unsigned columns, struct timeserie * 🅙, 
 void (^out)(char8₋t * u8s, __builtin_int_t bytes));
EXT₋C void Present₋timeserie₋transacts(struct timeserie * 🅙, int incl₋tables, 
 void (^out)(char8₋t * u8s, __builtin_int_t bytes));

int read₋utf8₋exposition(int byte₋count, char8₋t * utf8₋bytes, 
 struct structa * pool, struct structa * words);
int steganography₋hide(Nonabsolute word, Nonabsolute * code);
int steganography₋reveal(Nonabsolute code, Nonabsolute * word);

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


