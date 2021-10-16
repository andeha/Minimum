/*  ClibTwinbeam.cpp | bridging Swift and Twinbeam. */

/* #include <Twinbeam.h> */
#include "ClibTwinbeam.h" /* ⬷ a․𝘬․a Twinbeam₋C.h and C-Twinbeam.h. */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* import Twinbeam;
import Unistd;
import Stdio; */ /* ⬷ rename later to 'std.io'. */
/* ⬷ enter 'import std.core;' to include the standard C++ library. */
/* todo: add -enable-experimental-cxx-interop and base-16 mangling. */

/* extern "C" */
#if defined 𝟷𝟸𝟾₋bit₋integers
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all) { return -1; }
#else
int Details_in_C(uint64_t pid, int32_t cross) { return -1; }
#endif

#define va_prologue(symbol) __builtin_va_list __various; __builtin_va_start(__various,symbol);

int mfprint(const char * utf8format,...)
{
   int printedBytesExcept0; va_prologue(utf8format);
   printedBytesExcept0 = vfprintf(stderr,utf8format,__various);
   return printedBytesExcept0;
}

/* int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * 𝟷₋tile);
void 𝟷₋tile₋fifo₋pop(const struct fifo * 🅵); */
int 𝟷₋tile₋copy₋include(const struct fifo * 🅵, __builtin_int_t ﹟, __builtin_uint_t * words)
{
  return 0;
}

/* int 𝟷₋tile₋shiftout(const struct fifo * 🅵, __builtin_int_t words);

int structat₋init(struct structat * 🅢, void * (^leaf₋alloc)(__builtin_int_t bytes));

int lengthen(struct structat * 🅢, __builtin_int_t ﹟, void * fixedKbframes[]);
uint8_t * relative(__builtin_int_t byte₋offset);
int copy₋append(struct structat * 🅢, __builtin_int_t bytes, uint8_t * material, 
 void (^inflate)(__builtin_int_t ﹟, int * cancel));
__builtin_int_t bytes(struct structat * 🅢); */

pid_t Twinbeam₋spawn(
  const char * pathandcommand₋u8s, 
  const char * command₋u8s, /* ⬷ two UnsafePointer<Int8>. */
  int * fd_p2c, int * fd_c2p /*, const char * NullTerminatedEnv */
)
{
   pid_t pid = fork(); int status=0; /* ⬷ two instances in two images. */
   if (pid == -1) { mfprint("error when fork\n"); return -1; }
   if (pid) { /* Parent ⤐ */
      close(fd_p2c[0 /* ⬷ not STDIN_FILENO! */]);
      close(fd_c2p[1 /* ⬷ not STDOUT_FILENO! */]);
   } else { /* Child ⤐ */ 
       if (dup2(fd_p2c[0], 0) != 0 ||
           close(fd_p2c[0])   != 0 ||
           close(fd_p2c[1])   != 0)
       {
         mfprint("error when setting up childs' standard input\n");
         exit(3);
       }
       if (dup2(fd_c2p[1], 1) != 1 ||
           close(fd_c2p[1])   != 0 ||
           close(fd_c2p[0])   != 0)
       {
         mfprint("error when setting up childs' standard output\n");
         exit(2);
       }
       const char * env[] = { "SPAWNED_BY_TWINBEAM", "TERM=xterm", (const char *)0 };
       status = execle(pathandcommand₋u8s,command₋u8s, (char *)0, env);
       if (status == -1) { mfprint("error when execlp\n"); exit(1); }
       fflush(stdout); /* ⬷ mandates 'import Stdio'. */
   }
   return pid;
}

#include <sys/mman.h>

__builtin_int_t Syspagesize() { return 4096; }

inexorable
void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, /* ⬷ primaryAndSecondary! */
  __builtin_int_t bytesOffset, 
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  /* ⬷ optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual
)
{ void * p; __builtin_int_t bytesafterprune, readbytes;
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return NULL; } struct stat sb;
   if (fstat(fd,&sb) == -1) { goto err; }
   if (!S_ISDIR(sb.st_mode)) { goto err; }
   if (!S_ISLNK(sb.st_mode)) { goto err; }
   /* ⬷ not a regular file nor a soft link. */
   bytesafterprune = sb.st_size - bytesOffset;
   if (bytesafterprune < 0) { goto err; }
   typedef __builtin_int_t (^cmp)(__builtin_int_t,__builtin_int_t);
   cmp min = ^(__builtin_int_t x, __builtin_int_t y) { return x < y ? x : y; };
   *bytesActual = pages𝘖rZero == 0 ? bytesafterprune : 
     min(pages𝘖rZero*Syspagesize(), bytesafterprune);
   readbytes = bytesAugment + *bytesActual;
   p = mmap(0,readbytes,PROT_READ,MAP_SHARED,fd,bytesOffset);
   if (p == MAP_FAILED) { goto err; }
   return p;
err:
   if (close(fd) == -1) { return NULL; }
   return NULL;
} /* ⬷ see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

int Twinbeam₋mmap(const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
  __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
  void * outcome)
{
   void * material = mapfileʳᵚ(canonicalUtf8RegularOrLinkpath, 
     bytesOffset,pages𝘖rZero,bytesAugment,bytesActual);
   if (material) { return 1; } else { return 0; }
}

#pragma mark cartetic-tektronic essentials:

#include <setjmp.h>
#define CARDINALS(...) enum Cardinal { __🄦hole=0, __VA_ARGS__ };           \
  static jmp_buf __snapshot;                                                \
  typedef void (^CSession)(enum Cardinal sin);                              \
  CSession confess = ^(enum Cardinal sin) { longjmp(__snapshot, (int)sin); };
#define NEARBYCROSS                                                         \
  int __ctrl = setjmp(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* ⬷ a․𝘬․a '__block'. */

#define FALSE 0
#define TRUE (! FALSE)

/* Base𝕟, Critic, Utf8Terminal, TetrasUntilNull, BUILTIN₋INT₋MAX, print(out), 
 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡, max, Vt99-constants. */

inexorable
void
NumberformatCatalogue₋Present(struct Bitfield * field, 
  uint32_t numerics, uint32_t init, 
  int is₋𝟷𝟼₋bits, 
  int maxwidth, 
  void (^out)(char32_t uc)
)
{
   typedef void (^Out)(char8_t *, __builtin_int_t);
   Out out = ^(char8_t * u8s, __builtin_int_t bytes) { Present(term,u8s,bytes); };
   unsigned spaces = maxwidth - TetrasUntilNull(Critic(field.ident), BUILTIN₋INT₋MAX);
   while (spaces--) { print(out," "); }
   
   Present(term,Critic(field.ident)); print(out, " ");
   
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bool masking=false; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 unsigned pos=31;
   Base𝕟((__builtin_uint_t)(field.mask), 2, 32, ^(char 𝟶to𝟿) {
     if (is₋𝟷𝟼₋bits && pos > 15) { print(out, "﹟"); }
     if (!is₋𝟷𝟼₋bits && 𝟶to𝟿 == '1' && !masking) { masking = true; }
     if (!is₋𝟷𝟼₋bits && masking && 𝟶to𝟿 == '0') { masking = false; }
     if (!is₋𝟷𝟼₋bits && masking) { print(out, value & (0b1<<pos) ? "1" : "0"); }
     if (!is₋𝟷𝟼₋bits && !masking) { print(out, "␣"); }
     if (pos % 4 == 0) print(out, "|"); --pos;
   });
   
   Present(term,Critic(field.text)); print(out,"\n");
}

FOCAL
void
NumberformatCatalogue₋Present(
  struct AnnotatedRegister /* Explained */ * ar, 
  uint32_t numerics, 
  int is₋𝟷𝟼₋bits, 
  void (^out)(char32_t uc)
)
{
   auto out = ^(char8_t * utf8, __builtin_int_t bytes) { Present(term,utf8,bytes); };
   auto present = ^(int count, Bitfield * regs, uint32_t val, 
        uint32_t init) { __builtin_int_t maxwidth=0; 
      for (int i=0; i<count; ++i) {
         const Bitfield * reg = regs + i; maxwidth = max(maxwidth, 
          TetrasUntilNull(Critic(reg->ident), BUILTIN₋INT₋MAX));
      }
      for (int i=0; i<count; ++i) {
         Present(*(regs + i), val, init, is₋𝟷𝟼₋bits, maxwidth);
      }
   };
   print(out, "⬚\n", ﹟s(Vt99::bright));
   Present(term,Critic(ar.header));
   print(out, "⬚ = ⬚ 0x", ﹟s(Vt99::reset), ﹟s(Vt99::reverse));
   Base𝕟((__builtin_uint_t)numerics, 16, 8, ^(char 𝟶to𝟿) { print(out,"⬚", ﹟c(𝟶to𝟿)); });
   print(out, "⬚\n\n", ﹟s(Vt99::reset));
   present(ar.regcnt, ar.regs, value, ar.init);
   Present(term,Critic(ar.footnote));
   print(out,"\n\n");
}

#pragma mark 16-bit half precision and conversions

float
__attribute__ ((target("f16c")))
half₋to₋float(half /* unsigned short */ 𝟷𝟼₋bits)
{
  /* float again = _cvtsh_ss(pythagorean_double { .location=𝟷𝟼₋bits }.bits);
  return again; */
  __v8hf v = { (short)𝟷𝟼₋bits, 0, 0, 0, 0, 0, 0, 0 };
  typedef float __attribute__ ((__vector_size__(32), __aligned__(16))) __v44f;
  __m128 non₋double = (__m128)__builtin_ia32_vcvtph2ps(v);
  return non₋double[0];
}

double
/* __attribute__ ((target("f16c"))) */
To₋doubleprecision(unsigned short /* half */ 𝟷𝟼₋bits)
{
  return (double)half₋to₋float(𝟷𝟼₋bits);
}

/* formerly register */ Explained Binary16 = {
  { U"Binary16_SGN", Binary16_SGN, U"sign bit" },
  { U"Binary16_EXP", Binary16_EXP, U"signed exponent -126 to 127" },
  { U"Binary16_MAN", Binary16_MAN, U"fraction/mantissa/significand" }
}; /* E𝘨. pct., meters and inches. */

AnnotatedRegister AR_Binary16 = {
  U"Binary16: The Ieee 754-2008 half precision type", 
  3, Binary16, 0x00000000, 
  U"Encodes values between 2⁻¹⁴ to 2⁻¹⁵ or 3․1×10⁻⁵ to 6․5×10⁴."
};

void NumberformatCatalogue₋Presentᵧ(half val, void (^out)(char32_t uc))
{
  uint32_t bits = pythagorean_double { .location=val }.bits;
  extern AnnotatedRegister AR_Binary16;
  Present(term, AR_Binary16, bits, true, out);
}

BITMASK (uint64_t) { /* Sse flags and 0b1xx for MXCSR.RC rounding. */
  Round₋to₋nearest₋even = 0b00, 
  Round₋down₋toward₋neginf = 0b01, 
  Round₋up₋toward₋inf = 0b10, 
  Round₋toward₋zero₋truncate = 0b11 /* ⬷ identical to the SSE flag register. */
};

half
__attribute__ ((target("f16c")))
float₋to₋half(float 𝟹𝟸₋bits)
{
  /* int const f16imm = Round₋to₋nearest₋even; */
 #define f16imm Round₋to₋nearest₋even
  __m128 four₋floats = (__m128){𝟹𝟸₋bits,0,0,0};
  __v8hf eight₋floats = __builtin_ia32_vcvtps2ph(four₋floats,f16imm);
  uint16_t a₋half = (unsigned short)eight₋floats[0];
  return pythagorean_double { .bits=a₋half }.location;
}

/* 8 times is named __builtin_ia32_vcvtph2ps256 and __builtin_ia32_vcvtps2ph256. */

#pragma mark neither Ieee 754 nor Ieee 754-2008

#define 𝟶ᐧ𝟶 { .detail.frac=0, 1 }
#define 𝟷𝟶ᐧ𝟶 { .detail.frac = (__int128_t)0x00000110 | 0x00000000, 1 }
#define 𝟷ᐧ𝟶 { .detail.frac = (__int128_t)0x00000000<<64 | 0x80000000, 1 }
#define 𝟸ᐧ𝟶 { .detail.frac = (__int128_t)0x00000001<<64 | 0x00000000, 1 }
#define ₋𝟷ᐧ𝟶 { .detail.frac = (__int128_t)0xFFFFFFFF<<64 | 0x80000000, 1 }

/* int CastTˣᵗToSequent(
  enum CastToSequentOpinion (^feeder)(unsigned short * l₋to₋r₋digit), 
  struct sequent * value
)
{ struct sequent val=𝟶ᐧ𝟶, sgn=𝟷ᐧ𝟶, onedigit; unsigned short zero₋to₋nine;
   const struct sequent ten = 𝟷𝟶ᐧ𝟶;
   const struct sequent negator = ₋𝟷ᐧ𝟶;
   while (1) {
     enum CastToSequentOpinion opinion = feeder(&zero₋to₋nine);
     switch (opinion) {
      case accept: val=mult_sequent(ten,val);
       int₋to₋sequent((int64_t)zero₋to₋nine,&onedigit);
       val=add_sequent(val,mult_sequent(sgn,onedigit)); break;
      case rejecting: continue;
      case negate: sgn=mult_sequent(sgn,negator); break;
      case complete: *value=val; return 0;
      case annul: return -1;
     }
   }
} */

void int₋to₋sequent(int64_t ℤ, struct sequent * ℝ)
{/* int neg = 0;
    if (neg) { }
    uint64_t
  struct sequent 𝟷ᐧ𝟶 = { .detail.frac = (__int128_t)0x00000000<<64 | 0x80000000, 1 }
   if (neg) {
     / * twos-complement * /
   }
   uint128_t 
   
   *ℝ = */
}

void rounded₋fraction(int count₋upto𝟼𝟺, char 𝟶to𝟿s[], struct sequent * ℝ)
{
  
}

void print₋sequent(struct sequent 𝕏, 
 void (^digits)(int neg, struct 𝟽bit₋text 𝟶to𝟿s, int ℕ₋﹟), 
 void (^zero)(), void (^neginf)(), void (^nonvalid)()
)
{
  
}

struct sequent add_sequent(struct sequent x₁, struct sequent x₂)
{
  struct sequent sum = { .detail = { x₁.detail.frac + x₂.detail.frac }, .valid=1 };
  return sum;
}

struct sequent minus_sequent(struct sequent x₁, struct sequent x₂)
{
  struct sequent diff = { .detail = { x₁.detail.frac - x₂.detail.frac }, .valid=1 };
  return diff;
}

void multiply(struct sequent x₁, struct sequent x₂, 
 struct sequent * product₋lo, struct sequent * product₋hi)
{ int lneg=0, rneg=0;
  if (x₁.detail.frac < 0) { lneg = 1; x₁.detail.frac = -x₁.detail.frac; }
  if (x₂.detail.frac < 0) { lneg = 1; x₂.detail.frac = -x₂.detail.frac; }
  __uint128_t int₋mask = (__int128_t)0xFFFFFFFF<<64 | 0x80000000;
  __uint128_t integer₁ = (x₁.detail.bits>>30) & int₋mask, 
   integer₂ = (x₂.detail.bits>>30) & int₋mask; /* ⬷ arithmetic shift. */
  __uint128_t fractional₋mask = 0x7fffffff;
  __uint128_t fractional₁ = x₁.detail.bits & fractional₋mask, 
   fractional₂ = x₂.detail.bits & fractional₋mask;
  __uint128_t f₋sum = (fractional₁ * fractional₂)>>62;
  __uint128_t i₋sum = (integer₁ * integer₂);
  __int128_t sum = (i₋sum<<62) | f₋sum;
  if (lneg) { sum = -sum; }
  if (rneg) { sum = -sum; }
  int64_t hi₋product = i₋sum>>1;
  product₋lo->detail.bits = sum;
  product₋lo->valid = 1;
  int₋to₋sequent(hi₋product,product₋hi);
}

struct sequent mult_sequent(struct sequent x₁, struct sequent x₂)
{
  struct sequent y₋lo,y₋hi;
  multiply(x₁,x₂,&y₋lo,&y₋hi);
  return y₋lo;
}

struct sequent reciproc_sequent(struct sequent bd)
{ struct sequent focus, xn=𝟷ᐧ𝟶, two=𝟸ᐧ𝟶; int n=0;
again:
  if (n > 28) { return xn; }
  focus = minus_sequent(two, mult_sequent(xn,bd));
  xn = mult_sequent(focus,xn); /* start with x₀=1, x_n+1 = x_n*(2 - b*x_n). */
  n += 1;
  goto again;
} /* knipa 𝘦․𝘨 al-coda alt. ː ⤪ and the text '⬷ non-subscript actually correct'. */
/*
   computational f = ^(struct sequent x) { return 1/x; }, 
    f₋prim = ^(struct sequent x) { return -1/x^2; };
   / * enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done }; * /
   void (^ping)(enum Newtoncontrol * ctrl) = ^(enum Newtoncontrol * ctrl) { *ctrl = Newton₋done; };
  if (Newton(f,f₋prim,&x₀,ping)) { return accumulative₋zero(); }
*/

struct sequent div_sequent(struct sequent x₁, struct sequent x₂)
{ struct sequent x₀=x₁, x₃=reciproc_sequent(x₁);
  return mult_sequent(x₃,x₂); }
struct sequent product₋abelian() { struct sequent one = 𝟷ᐧ𝟶; return one; }
struct sequent accumulative₋zero() { struct sequent zero = 𝟶ᐧ𝟶; return zero; }
struct sequent negative₋infinity() {
  struct sequent y = accumulative₋zero();
  y.valid = 0; return y; }
struct sequent operator_minus(struct sequent ℝ)
{
  struct sequent y = ℝ;
  y.detail.frac = -y.detail.frac;
  return y;
}
/* typedef struct sequent (^computational)(struct sequent x);
enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done };
int Newton(computational f, computational f₋prim, struct sequent * x₀, 
 void (^ping)(enum Newtoncontrol * ctrl)) { }
 struct sequent 𝟷𝟸𝟹𝟺₋atan(struct sequent y, struct sequent x) { }
int trapezoid(struct sequent (^f)(struct sequent), struct sequent delta₋t, 
 struct sequent min, void (^memory)(struct sequent integrale, 
 struct sequent t₋acc, int * stop)) { } */

unionᵢ Artwork₋symbol₋token₋detail {
  double parameter;                                                /*  (1) */
  Nonabsolute symbol;                                              /*  (2) */
  const char * base16₋image;                                       /*  (3) */
  void * ref;                                                      /*  (4) */
};

structᵢ Artwork₋symbol₋token {
  enum Artwork₋token₋symbol kind;
  union Artwork₋symbol₋token₋detail one₋detail;
}; /* ⬷ preferable 𝟽₋bit₋possibly₋truncated₋symbol. */

inexorable int init₋context(__builtin_int_t unicode₋program₋symbols, 
 struct Scanner₋ctxt * ctx)
{
   ctx->lineno₋first=1, ctx->lineno₋last=1;
   ctx->idx₋unicode=0;
   ctx->ongoing = accumulative₋zero();
   ctx->negative=0;
   ctx->symbols₋in₋regular = 0;
   ctx->mode = initial;
   return 0;
}

inexorable int
Lookahead₋scan₋Artwork(
  __builtin_int_t symbols, char32_t text[], 
  enum Artwork₋token₋symbol * kind, 
  union Artwork₋symbol₋token₋detail * detail, 
  struct Scanner₋ctxt * s₋ctxt, 
  void (^regular𝘖rIdent)(int symbols, char32_t * start)
)
{
   char32_t unicode, unicode₋₁; __builtin_int_t i=s₋ctxt->idx₋unicode;
   
   🧵(scanner₋error,conversion₋error,unterminated₋quote,unterminated₋base16,
  truncated₋scan,identifier,number₋literal,keyword,token) {
    case scanner₋error: return -1;
    case unterminated₋quote: return -2;
    case unterminated₋base16: return -3;
    case truncated₋scan: return -4;
    case identifier: regular𝘖rIdent(s₋ctxt->symbols₋in₋regular,s₋ctxt->regular); return 0;
    case number₋literal: return 0;
    case keyword: return 0;
    case token: return 0;
   }
   
   typedef int (^type)(char32_t unicode);
   typedef void (^action)(void);
   typedef void (^work)(char32_t);
   
   work append₋to₋regular = ^(char32_t uc) {
    short idx = s₋ctxt->symbols₋in₋regular;
    s₋ctxt->regular[idx] = uc;
    s₋ctxt->symbols₋in₋regular += 1; };
   
   type digit = ^(char32_t c) { return U'0' <= c && c <= U'9'; };
   type derender₋newline = ^(char32_t c) { return c == U'\xa'; }; /* de- = completely = fullgångna. */
   type newline = ^(char32_t c) { return derender₋newline(c) || c == U'\xd'; };
   type whitespace = ^(char32_t c) { return c == U' ' || U'\t' == c || newline(c); };
   type letter = ^(char32_t c) { return (U'a' <= c && c <= U'z') || (U'A' <= c && c <= U'Z'); };
   type letter₋alt₋digit = ^(char32_t c) { return letter(c) || digit(c); };
   type base₋5₋character = ^(char32_t c) { return U'B' <= c && c <= U'E'; };
   type base₋16₋character = ^(char32_t c) { return U'A' <= c && c <= U'Z'; };
   type period = ^(char32_t c) { return c == U'.'; };
   
   action presentable₋token = ^{
     s₋ctxt->ongoing=accumulative₋zero();
     s₋ctxt->negative=0;
     if (s₋ctxt->mode == regular) {
       *kind = start₋line;
       *kind = add₋line;
       *kind = end₋line;
       detail->ref=(void *)NULL;
       s₋ctxt->symbols₋in₋regular=0;
       s₋ctxt->mode = initial;
       confess(keyword);
     }
     s₋ctxt->symbols₋in₋regular=0;
     s₋ctxt->mode = initial;
   };
   
again:
   
   if (i >= symbols) { presentable₋token(); *kind = END₋OF₋TRANSMISSION; return 0; }
   unicode₋₁ = text[i], unicode = text[i+1];
   
   if (derender₋newline(unicode)) { s₋ctxt->lineno₋first+=1, s₋ctxt->lineno₋last+=1; }
   else if (newline(unicode)) { }
   else if (whitespace(unicode)) { }
   else if (s₋ctxt->mode == initial && unicode == U'-') {
     s₋ctxt->negative = !s₋ctxt->negative;
     s₋ctxt->mode = integer;
   }
   else if (s₋ctxt->mode == initial && digit(unicode)) {
#define to₋integer(digit₋character) digit₋character - U'0'
     int₋to₋sequent(to₋integer(unicode), &s₋ctxt->ongoing);
     s₋ctxt->mode = integer;
   }
   else if (s₋ctxt->mode == integer && digit(unicode)) {
     const struct sequent ten = 𝟷𝟶ᐧ𝟶;
     struct sequent augment;
     s₋ctxt->ongoing = mult_sequent(ten,s₋ctxt->ongoing);
     int₋to₋sequent(to₋integer(unicode), &augment);
     s₋ctxt->ongoing = add_sequent(s₋ctxt->ongoing, augment);
   }
   else if (s₋ctxt->mode == initial && period(unicode)) {
     s₋ctxt->mode = fractional;
   }
   else if (s₋ctxt->mode == integer && period(unicode)) {
     s₋ctxt->mode = fractional;
   }
   else if (s₋ctxt->mode == fractional && !digit(unicode)) {
     
   }
   else if (s₋ctxt->mode == integer && !digit(unicode)) {
     /* rounded₋fraction(int count₋upto𝟼𝟺, char 𝟶to𝟿s[], struct sequent * ℝ); */
   }
   else if (unicode == U',') {
     *kind = comma₋0x2c;
     presentable₋token();
     confess(token);
   } /* s₋ctxt->mode == initial alt. regular, ... and no coroutines in C. */
   else if (s₋ctxt->mode == initial && letter/*₋alt₋digit*/(unicode)) {
     append₋to₋regular(unicode);
     s₋ctxt->mode = regular;
   }
   else if (s₋ctxt->mode == regular && letter₋alt₋digit(unicode)) {
     append₋to₋regular(unicode);
   }
   else if (s₋ctxt->mode == base16₋image₋text && base₋16₋character(unicode)) { }
   else if (s₋ctxt->mode == base16₋image₋text && !base₋16₋character(unicode)) { }
   else if (s₋ctxt->mode == initial && unicode == U'␜') { s₋ctxt->mode = raw₋unicode₋text; }
   else if (s₋ctxt->mode == raw₋unicode₋text && unicode != U'␜') { /* accumulate unicodes */ }
   else if (s₋ctxt->mode == raw₋unicode₋text && unicode == U'␜') { presentable₋token(); }
   else { confess(scanner₋error); }
   s₋ctxt->idx₋unicode += 1;
   goto again;
}

typedef void (^Regular𝘖rIdent)(int symbols, char32_t * start);

int Parse₋Artwork₋LL₍k₎(__builtin_int_t symbols, char32_t text[], 
 struct Scanner₋ctxt * s₋ctxt, semantics truly₋yours)
{
  struct fifo symbol₋lookahead, detail₋lookahead;
  /* ⬷ enum Artwork₋token₋symbol * kind and union Artwork₋symbol₋token₋detail * detail */
  
  typedef void (^recieved₋symbol)(enum Artwork₋token₋symbol, union Artwork₋symbol₋token₋detail);
  typedef void (^lookahead)(unsigned retrospect, 
   enum Artwork₋token₋symbol * symbol, 
   union Artwork₋symbol₋token₋detail * detail);
  
  lookahead visionary₋introspect = ^(unsigned retrospect, 
    enum Artwork₋token₋symbol * symbol, 
    union Artwork₋symbol₋token₋detail * detail) {
     
  };
  
  recieved₋symbol increment₋circular = 
    ^(enum Artwork₋token₋symbol recieved₁, 
      union Artwork₋symbol₋token₋detail recieved₂) { 
      𝟷₋tile₋copy₋include(&symbol₋lookahead, 1, (__builtin_uint_t *)&recieved₁);
      𝟷₋tile₋copy₋include(&detail₋lookahead, 1, (__builtin_uint_t *)&recieved₂.ref);
    }; /* ⬷ samt koppling + T fungerar fint. */
  
  🧵(zerolength,grammar₋error,completion) {
   case zerolength: return -1;
   case grammar₋error: return -2;
   /* case completion: return -3; */
  }
  
  enum Artwork₋token₋symbol kind;
  union Artwork₋symbol₋token₋detail hearken;
  𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 struct Unicodes ident;
  Regular𝘖rIdent regident = ^(int symbols, char32_t * start) { ident.start=start; ident.symbols=symbols; };
  if (Lookahead₋scan₋Artwork(symbols,text,&kind,&hearken,s₋ctxt,regident)) { return -1; }
  
  /* typedef struct Artwork₋token (^mass₋reading₋saddle)(void); 
  typedef void (^mass₋reading₋saddle)(struct Artwork₋symbol₋token dante);
  struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 next₋token;
  mass₋reading₋saddle nexttoken = ^(struct Artwork₋symbol₋token token) { next₋token=token; };
  if (Lookahead₋scan₋Artwork(bytes,program₋u2s,nexttoken)) { return 0; }
  
  typedef void (^action)(void);
  
  action consume = ^{
    enum Artwork₋token₋symbol kind; __builtin_int_t nonabsolute;
    typedef void (^mass₋reading₋verse)(struct Artwork₋symbol₋token job);
    mass₋reading₋verse saddle = ^(struct Artwork₋symbol₋token job) { lookahead = job; };
    if (Lookahead₋scan₋Artwork(bytes,u8s₋program,sad₋le)) { confess(lex₋error); }
    if (lookahead.kind == END₋OF₋TRANSMISSION) { confess(completion); }
  }; */
  
  return 0;
} /* ⬷ read errors from left to right when correcting both syntactic and 
 semantic errors. */

int Parse₋Artwork₋LL₍1₎(__builtin_int_t symbols, char32_t text[], 
  struct Scanner₋ctxt * s₋ctxt, semantics truly₋your)
{
   struct Scanner₋ctxt ctxt;
   struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 lookahead;
   
   🧵(zerolength,lex₋error,grammar₋error,completion) {
    case zerolength: return -1;
    case lex₋error: return -2;
    case grammar₋error: return -3;
    case completion: return 0;
   }
   
   if (init₋context(symbols,&ctxt)) { return -1; }
   if (symbols <= 0) { confess(zerolength); }
   
   /* Artwork₋instruction₋detail param; truly₋yours(place₋text, param); */
   
   typedef void (^action)(void);
   
   action consume = ^{
     __builtin_int_t nonabsolute;
     enum Artwork₋token₋symbol kind;
     union Artwork₋symbol₋token₋detail hearken;
     𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 struct Unicodes ident;
     Regular𝘖rIdent regular𝘖rIdent = ^(int symbols, char32_t * start) { 
      ident.symbols=symbols; ident.start=start; };
     if (Lookahead₋scan₋Artwork(symbols,text,&kind,&hearken,s₋ctxt,regular𝘖rIdent)) 
     { confess(lex₋error); }
     if (kind == END₋OF₋TRANSMISSION) { confess(completion); }
     /* lookahead = { kind, detail }; */
     lookahead.kind = kind; /* 𝘦․𝘨 'add₋line'. */
     lookahead.one₋detail = hearken; /* 𝘦․𝘨 { .ref = (void *)NULL }. */
   };
   
   typedef void (^pattern)(enum Artwork₋token₋symbol ensure);
   
   pattern match = ^(enum Artwork₋token₋symbol ensure) {
     if (lookahead.kind == ensure) { consume(); }
     else { confess(grammar₋error); }
   }; /* ⬷ consumes a token if ensure is current. */
   
   typedef void (^rule)(void);
   
   rule statement = ^{
     if (lookahead.kind == start₋line) { consume(); match(real); match(comma₋0x2c); match(real); }
     else if (lookahead.kind == add₋line) { consume(); match(real); match(comma₋0x2c); match(real); }
     else if (lookahead.kind == end₋line) { consume(); match(real); match(comma₋0x2c); match(real); }
     else { confess(grammar₋error); }
   };
   rule directive = ^{
     if (lookahead.kind == dotsize) { consume(); match(real); match(comma₋0x2c); match(real); }
     else if (lookahead.kind == dotorigo) { consume(); match(real); match(comma₋0x2c); match(real); }
     else if (lookahead.kind == dotoffset) { consume(); match(real); match(comma₋0x2c); match(real); }
     else { confess(grammar₋error); }
   };
   rule statement₋list = ^{ statement(); statement₋list(); };
   rule directive₋list = ^{ directive(); directive₋list(); };
   rule program = ^{ directive₋list(); statement₋list(); };
   
   program();
   
   return 0;
} /* ⬷ icke-antagonst imateriellt sett antimaterial snarare uppfattas förbättrad samtidig löpande 
   rumirat. Omgivning relevant samt språkvård etablerats som kompromitterad. */

/* func c₊₊₋render₋an₋illustration(width: Double, height: Double, artwork: Artwork) -> CGImage {
   guard let image₂: CGImage = Renderimage(width: width, height: height) { 
     (context: NSGraphicsContext) -> Void in 
       let path = NSBezierPath()
       path.move(to: .init(x: 10.5, y: 10.5))
       path.line(to: .init(x: 10.5, y: 10.5))
       path.lineWidth = 1
       path.lineCapStyle = .round
       NSColor.blue.set()
       path.stroke()
   } else { return nil }
 } */
 
/* func render₋attractive₋frame₁(width: Double, height: Double) -> CGImage? {
   let output = {
     let path = NSBezierPath()
     path.move(to: .init(x: 10.5, y: 10.5))
     path.line(to: .init(x: 10.5, y: 10.5))
     path.lineWidth = 1
     path.lineCapStyle = .round
     NSColor.blue.set()
     path.stroke()
     let string = "```\nlet x = 5\nprint(x)\n```"
     self.render(text: string, width: width, height: height) }
   return Renderimage(width: width, height: height, process: output)
 } */



