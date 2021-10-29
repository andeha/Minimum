/*  􀪀 ClibTwinbeam.h | the Swift and Twinbeam bridge for Si and O₂. */

#define structᵢ struct
#define unionᵢ union
#if defined (__cplusplus)
#define inexorable static __attribute__ ((internal_linkage))
/* ⬷ see 'nm' for details. */
#else
#define inexorable /* static */
#endif
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
#if defined  __mips__ || defined __armv6__ || defined espressif
typedef unsigned long       uint32_t;
typedef long                int32_t;
typedef uint32_t            __builtin_uint_t;
typedef int32_t             __builtin_int_t;
#define 𝟷𝟸𝟾₋bit₋integers /* ⬷ flag -fforce-enable-int128 when Mips. */
#ifdef __MM__
#undef 𝟷𝟸𝟾₋bit₋integers
#endif
#elif defined __armv8a__ || defined __x86_64__
typedef unsigned int        uint32_t;
typedef int                 int32_t; /* ≢'long'. */
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /* ⬷ a․𝘬․a 'sequenta'. */
#define 𝟷𝟸𝟾₋bit₋swift₋integers
#define 𝟷𝟸𝟾₋bit₋integers
/* #define 𝟷𝟸𝟾₋bit₋integers₋with₋calling₋conventions */
#endif
typedef short               int16_t; /* ≡ ᵐⁱᵖˢint. */
#define FOCAL /* ⬷ embossed inexorable. */
#define TROKADERO /* atomic calling convention. (Similar to Ieee754 Nan and Opt<double>.) */ 
#define LEAF /* will at run-time be executed without non-atomicity and 'call' instructions. */
#define ATOMIC /* will be executed without task switch and does not effect yield. */
#define SELDOM /* long-running and will be executed without task switch and is uncontaining 'yield'. */
#define QUOTE(str) #str

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

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* ⬷ a․𝘬․a '__block'. */

#define false 0
#define true (! false)

struct 𝟽bit₋text { __builtin_int_t bytes; signed char * start; };

#if !defined(__cplusplus)
typedef unsigned char char8_t; typedef unsigned int /* not uint32_t */ char32_t;
#endif

#if defined __cplusplus
#define EXT₋C extern "C"
#define EXT₋C₂ EXT₋C {
#define EXT₋C₋FROM }
#else
#define EXT₋C₋FROM
#define EXT₋C₂
#define EXT₋C
#endif

EXT₋C char32_t Utf8ToUnicode(char8_t *ξ, __builtin_int_t bytes);
EXT₋C int UnicodeToUtf8(char32_t Ξ, void (^sometime₋valid)(char8_t *u8s, short bytes));
EXT₋C short Utf8Followers(char8_t leadOr8Bit);
/* ⬷ C language char32_t is typealias CChar32 = Unicode.Scalar. */

#define BITMASK(type) enum : type

int IsPrefixOrEqual(const char * 𝟽alt𝟾₋bitstring, const char * 𝟽alt𝟾₋bitprefix);

struct Unicodes { __builtin_int_t tetras; char32_t * start; };

#define UNITTEST(symbol) extern "C" void Unittest_##symbol()
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",            \
  ﹟s(s), ﹟s(__FUNCTION__), ﹟s(__FILE__), ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog,s); } }
EXT₋C void Symbols(const char * utf8exepath, void (^each₋symbol)(const char * 
 sym, uint64_t addr, int * stop));
EXT₋C void exit(int status);

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
void multiply(Sequent x₁, Sequent x₂, Sequent * y₋lo, Sequent * y₋hi);
Sequent mult_sequent(Sequent x₁, Sequent x₂);
Sequent reciproc_sequent(Sequent yb);
Sequent div_sequent(Sequent x₁, Sequent x₂, int integer₋division); 
/* the symbol 'div' requires __attribute__((overloadable)); */
Sequent product₋abelian(); /* ⬷ a․𝘬․a '1'. */
Sequent accumulative₋zero(); /* ⬷ a․𝘬․a '0'. */
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

typedef half __attribute__ ((__vector_size__(16), __aligned__(16))) __v8hf;
typedef __v8hf __m128i;
typedef float __attribute__ ((__vector_size__(16), __aligned__(16))) __m128;
typedef __m128i panko; /* ⬷ in Swift already named SIMD8. On Intel VCVTPH2PS and _m256 _mm256_cvtph_ps ( __m128i m1). */

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
   } bfloat16; /* ⬷ ubiquitous. */
   unsigned short bits;
#if defined __x86_64__
   half location;
#endif
} pythagorean_double;

/* When 'typedef _Float16 two₋half;' them]n `two₋half x[] = { 1.2, 3.0, 3.e4 };` */

EXT₋C FOCAL void Base𝕟(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned 
 short base, unsigned short digitsOr0, /* Not more than 32 alt. 64 digits 
 depending on word size! (Or set to `0` to skip leading zeros.) */ void
 (^out)(char 𝟶to𝟿));

EXT₋C double To₋doubleprecision(/* unsigned short */ half x);

EXT₋C void NumberformatCatalogue₋Presentᵧ(half val, 
 /* void (^sometime)(int count, char32_t * terminated₋ucs) */ 
 void (^out)(char8_t * u8s, __builtin_int_t bytes));

struct Bitfield { const char32_t * regular; uint32_t mask; const char32_t * text; };
struct AnnotatedRegister { const char32_t * header; int regcnt; struct Bitfield * regs; 
 uint32_t init; const char32_t * footnote; };
typedef struct Bitfield Explained[];

EXT₋C void NumberformatCatalogue₋Present(
  struct AnnotatedRegister /* Explained */ * ar, 
  uint32_t numerics, 
  int is₋𝟷𝟼₋bits, 
  /* void (^sometime)(int count, char32_t * terminated₋ucs) */
  void (^out)(char8_t * u8s, __builtin_int_t bytes)
);

struct distance { half length; int unit; };
enum Image₋kind { PNGrgba8 };
struct PngRGBA8Pixel { uint8_t R,G,B,A; };
union Image₋rectangle { struct PngRGBA8Pixel * pngRgba8; /* ⬷ 𝘤𝘧․ Scatter. */ };
struct Image { int scanlines, columns, pixelsize; int unpurged; 
 union Image₋rectangle material; int kind; /* ∈[1,7] */ };
struct Cropped₋image { struct Image picture; };
struct Plate { struct Cropped₋image image; int unit; };
int Init₋image(struct Image * image, int secure);
int Release₋image(struct Image * image);

#define a⃝ __attribute__((overloadable))
 
EXT₋C int mfprint(const char * utf8format, ...);
EXT₋C int print(void (^out)(char8_t * u8s, __builtin_int_t bytes), 
 const char * utf8format, ...) a⃝;
EXT₋C int print(const char * utf8format, ...) a⃝;

#ifndef __cplusplus
typedef int bool;
#endif

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

struct fifo {
 __builtin_int_t brk, count, *𝟷₋tile, words₋to₋unity;
};

EXT₋C int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * 𝟷₋tile);
EXT₋C void 𝟷₋tile₋fifo₋pop(const struct fifo * 🅵);
EXT₋C int 𝟷₋tile₋copy₋include(const struct fifo * 🅵, __builtin_int_t ﹟, 
 __builtin_uint_t * words);
EXT₋C int 𝟷₋tile₋shiftout(const struct fifo * 🅵, __builtin_int_t words);

struct structa {
  __builtin_int_t cached₋number, tile₋count, bytes₋per₋tile, unused₋bytes;
  void * treelist, *cached₋tile;
};

typedef void * (^Leaf₋alloc)(__builtin_int_t /* bytes */);
typedef Structa struct structa;
EXT₋C int structa₋init(Structa * 🅢, Leaf₋alloc leaf₋alloc);
EXT₋C int structa₋lengthen(Structa * 🅢, __builtin_int_t ﹟, void * fixedKbframes[]);
EXT₋C uint8_t * structa₋relative(Structa * 🅢, __builtin_int_t byte₋offset);
EXT₋C int structa₋copy₋append(Structa * 🅢, __builtin_int_t bytes, uint8_t * material, 
 void (^inflate)(__builtin_int_t ﹟, int * cancel));
EXT₋C __builtin_int_t structa₋bytes(Structa * 🅢);
/* c++ mangling and __attribute__((overloadable)); = ^{ return malloc(bytes); };
 let register₋reflect = { (mask: __builtin_uint_t) -> Void in print("") } 
 as @convention(block) (__builtin_uint_t) -> Void */
/* __attribute__((overloadable)) is not yet executed in swift code. */

#define va_epilogue __builtin_va_end(__various);
#define va_prologue(symbol)                                                 \
 __builtin_va_list __various;                                               \
 __builtin_va_start(__various, symbol);

/* #define NULL 0 */
typedef int pid_t;

EXT₋C pid_t Twinbeam₋spawn(const char * pathandcommand₋u8s, const char * 
 command₋u8s, int * fd_p2c, int * fd_c2p /*, const char * NULLterminatedEnv */);

EXT₋C int Twinbeam₋mmap(const char * canonicalUtf8RegularOrLinkpath, 
 __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
 __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
 void * outcome);

enum Impediment { MustBeOrdered, JustSwap };
struct Peekey { __builtin_int_t board₁, palm₂; };
EXT₋C int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, 
 enum Impediment it); TROKADERO SELDOM

/* Överhandsavtal och underhandsuppfattning: 
 
 ━━━   ━━━
  ┊ 􀲯  ┊   ⤐ t 
 ━━━   ━━━
 
 samtalar utan uppmärksamhet kvicknar. */

/*
  
  E․𝘨 .size 89.0  .offset -5.0, 12.0  .origo 50.0, 50.0 .columned 1
  
  program <- directive-list statement-list-nandalt-twolevel
  directive-list <- directive directive-list
  statement-list-alt-hierarchy <- statement statement-list
  statement-list alt. directive-list <- empty
  
  directive <- '.pixel-height' real 
  directive <- '.origo' real ',' real
  directive <- '.offset' real ',' real
  directive <- '.columned' natural
  
  real-literal <- '-'* digit+ '.' digit*
  
  statement <- 'start-line' real ',' real
  statement <- 'add-line' real ',' real
  statement <- 'last-line' real ',' real
  statement <- 'base16-image' [a-z]+                               and not base 21
  statement <- 'utf8-text' ␜ <text> ␜
  statement <- 'next'
  statement <- 'azimuth' azimuth-flavor real ',' real ',' real ',' real
  azimuth-flavor <- 'relative' | unit 'absolut' 
  statement <- identifier '<-' 'cyan' real ',' real ',' real ',' real 
   'mangenta' real ',' real ',' real ',' real 
   'yellow' real ',' real ',' real ',' real 
   'black' real ',' real ',' real ',' real color-unit real
  statement <- 'color-clog' identifier 'on' identifier 
  statement <- 'pressure' ⬷ with later relative alt. absolut ∓ADSR F
  color-unit <- 'relative' | 'absolute'
  statement <- 'ellipsoid' '(' real ',' real ')' 'and' '(' real ',' real ')'
  statement <- 'intention' 'inner' | 'middle' | 'outer'
  statement <- 'bleed' real unit
  
  unit <- 'mm'
  unit <- 'cm'
  unit <- 'in'
  unit <- 'pc'
  unit <- 'throu'
  
  two-level <- 'frame' statement-list 'closed' ⬷ a․𝘬․a 'draft'.
  
 */

/* Typechecked in your military-project: */

union Tetra𝘖rUnicode { int32_t count; char32_t uc; };
typedef __builtin_int_t Nonabsolute; /* ⬷ index to symbols in swift Array<UInt32>. */
typedef half Artnumerical;
/* ⬷ and neither 'struct sequent' nor 'struct Artnumerical { half value; }' for Swift half literal. */

struct A₋point { double x,y; };
struct Illustration { double size, place₋origo, offset₋drawing₋on; };
EXT₋C int Draw₋Bezier(int columns, int count, struct Illustration * ctxt, struct A₋point, ...);
/* ⬷ arbitrary number of other points. ⤐ */
typedef void (^Visual)(struct Plate layer, bool * stop);
EXT₋C int Set₋text(struct Unicodes symbols, struct A₋point start, int mode, Visual plates);
EXT₋C int Define₋image(struct 𝟽bit₋text regular, char base₋23, int ansamla);
EXT₋C int Place₋image(struct 𝟽bit₋text regular, struct A₋point p₁, struct A₋point p₂, int mode);
typedef struct A₋point A₋size; /* ⬷ a․𝘬․a ground₋size alt․ nested₋size. */
union Artwork₋directive {
  int Count; /* ar: short. */
  double Scalar;
  /* struct */ A₋size Size;
  struct A₋point Point;
};

enum Artwork₋token₋symbol { dotsize, dotorigo, dotoffset, real, comma₋0x2c, 
 start₋line, add₋line, end₋line, base16₋image, base16₋text, 
 utf8₋text, rawtext₋sentinel, text, next, END₋OF₋TRANSMISSION };

union Artwork₋instruction₋detail {
  double * four₋parameters;                                        /*  (1) */
  Nonabsolute symbol;                                              /*  (2) */
  struct Unicodes identifier;                                      /*  (3) */
  union Artwork₋directive various₋signatures;                      /*  (4) */
};

typedef char8_t uchar;
typedef void (*semantics)(int artwork₋instruction, 
 union Artwork₋instruction₋detail parameters, void * ctx);

enum Artwork₋scanner₋mode { initial, regular, 
 integer, period, fractional, 
 base16₋image₋text, raw₋unicode₋text, 
 div₋prefix₋comment, div₋suffix₋comment₋ie₋comment
};

struct Scanner₋ctxt {
  __builtin_int_t lineno₋first, lineno₋last;
  __builtin_int_t idx₋unicode; /* ⬷ and not idx₋u8s. */
  struct sequent ongoing; int negative;
  char32_t regular[1024]; short symbols₋in₋regular;
  enum Artwork₋scanner₋mode mode;
};

EXT₋C int Parse₋Artwork₋LL₍1₎(__builtin_int_t symbols, char32_t text[], 
 struct Scanner₋ctxt * s₋ctxt, semantics truly₋your);
EXT₋C int Parse₋Artwork₋LL₍k₎(__builtin_int_t symbols, char32_t text[], 
 struct Scanner₋ctxt * s₋ctxt, semantics truly₋your);

typedef enum Artwork₋instruction { columned=1, 
 pixel₋height, place₋origo, offset₋drawing₋on,          /* ⬷ directive. */
 dualbezier₋initial, dualbezier₋add, dualbezier₋last,   /* ⬷ instruction. */
 quadbezier₋initial, quadbezier₋add, quadbezier₋last, 
 beziercurve₋initial, beziercurve₋add, beziercurve₋last, 
 line₋initial, line₋add, line₋last, 
 bezier₋alt₋line₋close, 
 𝟸ᵈ₋intervallic, sample, link₋master₋detail, 
 base16₋encoded₋later₋layered₋png, place₋png, 
 color₋select, fill, 
 set₋letterbox₋anchor, set₋letterbox₋origo, 
 place₋text /* p3₋color₋select */
} Artwork₋instruction; /* ⬷ a․𝘬․a ¹directives and ¹instruction. */


