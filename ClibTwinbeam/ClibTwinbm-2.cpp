/*  􀈐 ClibTwinbm-2.cpp | 'det' blev icke-klart och presenterades som 'ordning olika'. */

import ClibTwinbeam;

#if defined(𝟷𝟸𝟾₋bit₋integers)

inexorable void Base𝕫(__int128_t ℤ, 
  unsigned short base, unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿and₋)
)
{
  if (ℤ < +0) { out('-'); ℤ = -ℤ; }
  Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, out);
}

inexorable void
Base𝕟(
  __uint128_t ℕ, 
  unsigned short base, 
  unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿)
)
{
   auto 𝟶to𝖥 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
     out('0' + r) : out('a' - 10 + r); };
   
   unsigned short cycle[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   
   short k = 0;
   
   do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
   if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 
     𝟶to𝖥(cycle[k], out); } }
   else { k = 127; while (cycle[k] == 0 && k > 0) { k--; }
     for (; k >= 0; k--) { 𝟶to𝖥(cycle[k], out); }
   }
} /* ⬷ requires 128-bits-`fractions`, { `__umodti3`, `__udivti3` }, `__udivmodti4`. */

#endif

EXT₋C
void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* ⬷ not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char 𝟬to𝟵)
) /* __attribute__ ((extern_c)) */
{
   auto 𝟬to𝗙 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
     out('0' + r) : out('a' - 10 + r); };
   
   unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
     0, 0, 0, 0 }; short k = 0;
   
   do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
   
   if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟬to𝗙(cycle[k], 
     output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
      for (; k >= 0; k--) { 𝟬to𝗙(cycle[k], output); }
   }
} /*  ⬷ note 128-bit duplicate earlier in text. */

__builtin_int_t TetrasUntilNull(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t i=0;
again:
   if (i >= maxtetras) { return maxtetras; }
   char32_t * uc = ucs + i;
   if (*uc == 0x0000) { return i; }
   ++i; goto again;
}

#define WHEN_COMPILING constexpr static
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /* ⬷ must be assigned to a 'const' and no inline assembler. */

FOCAL
short
Utf8Followers(char8_t leadOr8Bit)
{
    if (leadOr8Bit < 128) { return 0; }
    if (128 <= leadOr8Bit && leadOr8Bit < 192) return -1;
    if (248 <= leadOr8Bit) return -1;
    
#if defined __mips__ || defined __armv6__ || defined __armv8a__
    /* Mips: clz $a0, $v0, Arm: clz r0, r14. */
    __builtin_int_t onesUntilZero = __builtin_clz(~((uint32_t)leadOr8Bit<<24));
#elif defined __x86_64__ /* BSF, BSR, LZCNT, TZCNT, __lzcnt64 on Win64. */
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
char32_t
Utf8ToUnicode(
  char8_t *ξ,
  __builtin_int_t bytes
)
{
    char8_t first = *ξ;
    if (248 <= first || (128 <= first && first < 192)) return 0x0000FFFF;
    switch (bytes) { case 1: return (char32_t)(char8_t)*ξ; case 2: return 
    (0b11111&*ξ) << 6 | (0b111111&(*(ξ + 1))); case 3: return (0b1111&*ξ) << 
    12 | (0b111111&(*(ξ + 1))) << 6 | (0b111111&(*(ξ + 2))); case 4: return 
    (0b111&*ξ) << 18 | (0b111111&(*(ξ + 1))) << 12 | (0b111111&(*(ξ + 2))) << 
    6 | (0b111111&(*(ξ + 3))); } return 0x0000FFFE;
}

FOCAL
int
UnicodeToUtf8(
  char32_t Ξ,
  void (^sometime₋valid)(char8_t *u8s, short bytes)
)
{
    unsigned char 🥈 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 
      0xF8, 0xFC };
    
    char32_t 🥈 byteMask=0xBF, byteMark=0x80;
    
    short bytesToWrite=0;
    
    if (Ξ < 0x80L) { bytesToWrite=1; }
    else if (Ξ < 0x800L) { bytesToWrite=2; }
    else if (Ξ < 0x10000L) { bytesToWrite=3; }
    else if (Ξ <= 0x0010FFFFL) { bytesToWrite=4; }
    else { return 1; }
    
    char8_t target[4];
    
    switch (bytesToWrite) {
    case 4: target[3] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 3: target[2] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 2: target[1] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 1: target[0] = (char8_t) (Ξ | firstByteMark[bytesToWrite]);
    }
    
    sometime₋valid(target,bytesToWrite);
    
    return 0;
}

int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /* ⬷ possibly 'normalizedUtf8' */
  const char * 𝟽alt𝟾₋bitprefix  /* ⬷ smiley appears when 'prompt> nm'! */
) /* ⬷ consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{  const char *s=𝟽alt𝟾₋bitstring, *p=𝟽alt𝟾₋bitprefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters 'string' and 'prefix' are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in 'prefix' equal to 'string'. Return first character following 'eightbitPrefix'. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; } /* Savannah and Samura. */
    s++, p++;
    goto again;
}

template <typename T> T * Critic(const T * x) { return const_cast<T*>(x); }

#pragma mark - Inte₋ger₋s

EXT₋C Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, .kind=1 }; }
EXT₋C Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { { .x=x }, 2 }; }
EXT₋C Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { { .b=b }, 3 }; }
EXT₋C Argᴾ ﹟s(const char8_t * u8s) a⃝ { return Argᴾ { { .u8s=(char8_t *)u8s }, 4 }; }
EXT₋C Argᴾ ﹟s(char8_t * u8s) a⃝ { return Argᴾ { { .u8s=u8s }, 4 }; }
EXT₋C Argᴾ ﹟s(const /* signed */ char * s) a⃝ { return Argᴾ { { .u8s=(char8_t *)s }, 4 }; }
EXT₋C Argᴾ ﹟s(/* signed */ char * s) a⃝ { return Argᴾ { { .u8s=(char8_t *)s }, 4 }; }
EXT₋C Argᴾ ﹟S₁(__builtin_int_t tetras, char32_t * unterminated₋uc) a⃝ { return Argᴾ { { .ucs={ tetras, unterminated₋uc } }, 5 }; }
EXT₋C Argᴾ ﹟S₁(__builtin_int_t tetras, const char32_t * unterminated₋uc) a⃝ { return Argᴾ { { .ucs={ tetras, (char32_t *)unterminated₋uc } }, 5 }; }
EXT₋C Argᴾ ﹟c(char8_t c) a⃝ { return Argᴾ { { .c=c }, 6 }; }
EXT₋C Argᴾ ﹟c(/* signed */ char c) a⃝ { return Argᴾ { { .c=(char8_t)c }, 6 }; }
EXT₋C Argᴾ ﹟C(char32_t C) { return Argᴾ { { .uc=C }, 7 }; }
#if defined 𝟷𝟸𝟾₋bit₋integers
EXT₋C Argᴾ ﹟U(__uint128_t U) { return Argᴾ { { .U=U }, 11 }; }
EXT₋C Argᴾ ﹟I(__int128_t I) { return Argᴾ { { .I=I }, 12 }; }
#endif
EXT₋C Argᴾ ﹟regs(__builtin_uint_t mask) { return Argᴾ { { .x=mask }, 13 }; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */

EXT₋C Argᴾ ﹟λ(Argᴾ₋output₂ scalar, void * context) { return Argᴾ { { .λ={ scalar, context } }, 10 }; }

EXT₋C Argᴾ ﹟chapter(Unicodes ingress, Plate * anfang)
{
  return Argᴾ { { .chapter={ anfang, ingress } }, 88 };
} /* ⬷ see --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp> for details on PNG::IHDR. */

void Register₋reflect(__builtin_uint_t /* mask */) { }

inexorable void Present(void (^out)(char8_t * u8s, __builtin_int_t bytes), char32_t * terminated₋ucs)
{
   __builtin_int_t tetras = TetrasUntilNull(terminated₋ucs,BUILTIN₋INT₋MAX);
   print(out, "⬚", ﹟S₁(tetras,terminated₋ucs));
}

EXT₋C Argᴾ ﹟S₂(char32_t * terminated₋uc) {
  __builtin_int_t tetras = TetrasUntilNull(terminated₋uc,BUILTIN₋INT₋MAX);
  return Argᴾ { { .ucs={ tetras, terminated₋uc } }, 5 };
}

inexorable void Coalesc₋present(void (^out)(int count, char32_t * unterminated₋ucs), int count, char32_t * unterminated₋ucs)
{
   
} /* ⬷ two 'async'-job alt. written coroutines alt. threads for example. */

#pragma mark - in /retrospect/, hidden yet simple:

#define UNEXISTING₋IEEE754

inexorable
int
print﹟(
  void (^out)(char8_t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{  __builtin_int_t i=0, incr; short followers; char32_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* bool may𝘖rDidEscape=false; */
    auto out₂ = ^(const char * 𝟽bit₋utf8, __builtin_int_t bytes) {
      out((char8_t *)𝟽bit₋utf8, bytes); printedBytesExcept0 += bytes; };
    auto out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s,1); }); };
    auto out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16, 
#if defined __x86_64__ || defined __armv8a__
      16
#elif defined  __mips__ || defined __armv6__ || defined espressif
       8
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto 𝟷𝟶𝟷𝟷𝟶₋out = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#if defined __x86_64__ || defined __armv8a__
       64
#elif defined  __mips__ || defined __armv6__ || defined espressif
       32
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto eight₋bit₋symbol = ^(char8_t c) { out(&c,1); };
    auto u8c₋stream = ^(char8_t * utf8) { char8_t * p = (char8_t *)utf8; while (*p) { out(p,1); p++; } };
    auto unicode₋symbol = ^(char32_t u) { UnicodeToUtf8(u, ^(char8_t * u8s, 
     short bytes) { out(Critic(u8s),bytes); }); };
#ifndef UNEXISTING₋IEEE754
    auto out𝕕 = ^(double ℝ) { Format(ℝ, Ieee754form::Scientific, ^(char32_t uc) { unicode₋symbol(uc); }); };
#endif
    auto unicode₋stream = ^(int tetras, char32_t * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32_t uc = *(unicodes + beam); unicode₋symbol(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
#ifdef 𝟷𝟸𝟾₋bit₋integers
    auto 𝟷𝟸𝟾₋out𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿,1); }); };
    auto 𝟷𝟸𝟾₋out𝕟 = ^(__uint128_t U) { Base𝕟(U, 16, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋,1); }); };
#endif
again:
    auto leadOr8Bit = i + (char8_t *)utf8format;
    if (*leadOr8Bit == 0x0) { goto unagain; }
    followers = Utf8Followers(*leadOr8Bit);
    if (followers < 0) { return -1; }
    incr = followers + 1;
    uc = Utf8ToUnicode(leadOr8Bit,incr);
    if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }
    else if (uc != U'⬚') { unicode₋symbol(uc); }
    else { /* ⬷ reflecting natives /to/ terminal. */
      const Argᴾ a = __builtin_va_arg(argument, Argᴾ);                          \
      switch (a.kind) {                                                         \
      case 1: out𝕫(a.value.d); break;                                           \
      case 2: out𝕟(a.value.x); break;                                           \
      case 3: 𝟷𝟶𝟷𝟷𝟶₋out(a.value.b); break;                                       \
      case 4: u8c₋stream(a.value.u8s); break;                                   \
      case 5: unicode₋stream(a.value.ucs.tetras, a.value.ucs.start); break;     \
      case 6: eight₋bit₋symbol(a.value.c); break;                               \
      case 7: unicode₋symbol(a.value.uc); break;                                
#ifndef UNEXISTING₋IEEE754
      case 8: out𝕕(double(a.value.f₂)); break;                                  \
      case 9: out𝕕(a.value.f₁); break;                                          
#endif
/*    case 10: { Argᴾ₋Unicode set = ^(bool anfang, char32_t * prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, \
       void * context) { }; a.value.λ.scalar(set, a.value.λ.context); break; } */
#ifdef 𝟷𝟸𝟾₋bit₋integers
      case 11: 𝟷𝟸𝟾₋out𝕟(a.value.U); break;                                      \
      case 12: 𝟷𝟸𝟾₋out𝕫(a.value.I); break;
#endif
      case 13: Register₋reflect(a.value.x); break;                              \
      case 88: unicode₋stream(a.value.chapter.ingress.tetras,                   \
       a.value.chapter.ingress.start); break;                                   \
      default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
        unicode₋symbol(U'?'); break; }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

extern "C" long write(int fd, const void * s, long unsigned nbyte);
#define NOT_EVERYTIME const static
#define 🥇 NOT_EVERYTIME

FOCAL EXT₋C
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y; 
#ifdef __x86_64__
   bool original = false; int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
} /* int mfprint(const char * utf8format,...)
{
   int printedBytesExcept0; va_prologue(utf8format);
   printedBytesExcept0 = vfprintf(stderr,utf8format,__various);
   return printedBytesExcept0;
} */

FOCAL
EXT₋C
int
print(const char * utf8format, ...) a⃝ /* Here all variable args are of the type `Argᴾ`. */
{ int y; va_prologue(utf8format);
#ifdef __x86_64__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

EXT₋C
FOCAL
int
print(
  void (^out)(char8_t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  ...
) a⃝
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
}

template <typename T> T max(T x₁, T x₂) { return x₁ < x₂ ? x₂ : x₁; }
namespace Vt99 { const /* signed */ char * bright = "\x1B[1m", *dim = "\x1B[2m", 
 *fg₋blue = "\x1B[34m", *fg₋red = "\x1B[31m", *reset = "\x1B[0m", 
 *reverse = "\x1B[7m"; }

inexorable
void
Present(struct Bitfield * field, 
  uint32_t numerics, uint32_t init, 
  int is₋𝟷𝟼₋bits, 
  int maxwidth, 
  /* void (^output)(char32_t uc) */
  /* void (^sometime)(int count, char32_t * terminated₋ucs) */
  void (^out)(char8_t * u8s, __builtin_int_t bytes)
)
{
   unsigned spaces = maxwidth - TetrasUntilNull(Critic(field->regular), BUILTIN₋INT₋MAX);
   while (spaces--) { print(out," "); }
   
   Present(out,Critic(field->regular)); print(out, " ");
   
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bool masking=false; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 unsigned pos=31;
   Base𝕟((__builtin_uint_t)(field->mask), 2, 32, ^(char 𝟶to𝟿) {
     if (is₋𝟷𝟼₋bits && pos > 15) { print(out, "x"); } else {
      if (𝟶to𝟿 == '1' && !masking) { masking = true; }
      if (masking && 𝟶to𝟿 == '0') { masking = false; }
      if (masking) { print(out, numerics & (0b1<<pos) ? "1" : "0"); }
      if (!masking) { print(out, "␣"); } }
     if (pos % 4 == 0) print(out, "|"); --pos;
   });
   
   Present(out,Critic(field->text)); print(out,"\n");
}

FOCAL EXT₋C
void
NumberformatCatalogue₋Present(
  struct AnnotatedRegister /* Explained */ * ar, 
  uint32_t numerics, 
  int is₋𝟷𝟼₋bits, 
  /* void (^output)(char32_t uc) */
  /* void (^sometime)(int count, char32_t * terminated₋ucs) */
  void (^out)(char8_t * u8s, __builtin_int_t bytes)
)
{
   auto present = ^(int count, Bitfield * regs, uint32_t val, 
        uint32_t init) { __builtin_int_t maxwidth=0; 
      for (int i=0; i<count; ++i) {
         const Bitfield * reg = regs + i; maxwidth = max(maxwidth, 
          TetrasUntilNull(Critic(reg->regular), BUILTIN₋INT₋MAX));
      }
      for (int i=0; i<count; ++i) {
         Present((regs + i), val, init, is₋𝟷𝟼₋bits, maxwidth, out);
      }
   };
   print(out, "⬚\n", ﹟s(Vt99::bright));
   Present(out,Critic(ar->header));
   print(out, "⬚ = ⬚ 0x", ﹟s(Vt99::reset), ﹟s(Vt99::reverse));
   Base𝕟((__builtin_uint_t)numerics, 16, 8, ^(char 𝟶to𝟿) { print(out,"⬚", ﹟c(𝟶to𝟿)); });
   print(out, "⬚\n\n", ﹟s(Vt99::reset));
   present(ar->regcnt,ar->regs,numerics,ar->init);
   Present(out,Critic(ar->footnote));
   print(out,"\n\n");
}

#pragma mark blue, white and something to keep

/* namespace __cxxabiv1 { */
EXT₋C int __cxa_guard_acquire(__builtin_uint_t * p) {
  __builtin_uint_t expected[1] = { 0 }, desired[1] = { 1 };
  const int relaxed=0;
  int success_order=relaxed, failure_order=relaxed;
  bool locked = __atomic_compare_exchange(p, expected, desired, 0, 
   success_order, failure_order);
  return locked; }
EXT₋C int __cxa_guard_release(__builtin_uint_t * p) {
  __builtin_uint_t desired[1] = { 0 }, expected[1] = { 1 };
  const int relaxed=0;
  int success_order=relaxed, failure_order=relaxed;
  bool unlocked = __atomic_compare_exchange(p, expected, desired, 0, 
   success_order, failure_order);
  return unlocked;
}
EXT₋C void __cxa_guard_abort(__builtin_uint_t * p) {
  __builtin_uint_t desired[1] = { 0 };
  const int relaxed=0;
  int ordering=relaxed;
  __atomic_store(p,desired,ordering);
}
/* } / * ⬷ a․𝘬․a coroutine and async 'yield'. */

FOCAL
EXT₋C
int
#if defined __x86_64__
__attribute__ ((target("rtm")))
#elif defined __armv8a__
__attribute__ ((target("tme")))
#endif
OptimisticSwap(
  __builtin_int_t * p₁, __builtin_int_t * p₂,
  enum Impediment it
) TROKADERO SELDOM
{
#if defined __armv8a__
   uint64_t cause = __tstart();
   if (cause) { return -1; }
#elif defined __x86_64__
   unsigned status = _xbegin();
   if (status != _XBEGIN_STARTED) { return -1; }
#elif defined Kirkbridge
   uint32_t start = U₋begin();
#endif
   if (it == MustBeOrdered && *p₁ < *p₂) { return -1; }
   *p₁ = *p₁ ^ *p₂;
   *p₂ = *p₁ ^ *p₂;
   *p₁ - *p₁ ^ *p₂;
   if (it == MustBeOrdered && *p₁ > *p₂) {
#if defined __armv8a__
#define _TMFAILURE_UNORDERED 0x8000u /* ⬷ a․𝘬․a retry. */
#define _TMFAILURE_RTRY 0x8000u
#define _TMFAILURE_REASON 0x7fffu
    uint64_t cancellation₋reason = _TMFAILURE_UNORDERED | (0x01 & _TMFAILURE_REASON);
    __tcancel(cancellation₋reason);
#elif defined __x86_64__
    _xabort(0xfe);
#elif defined Kirkbridge
    U₋err();
#endif
     return -1;
   }
#if defined __armv8a__
   __tcommit();
#elif defined __x86_64__
   _xend(); /* ⬷ see [Twinbeam]--<Source>--<System.cpp>. */
#elif defined Kirkbridge
   U₋forward();
#endif
   return 0;
}

EXT₋C int momentary₋always₋swap(struct Peekey * p) LEAF TROKADERO
{
  /* return __cxa_guard_release(p); */
  return OptimisticSwap(&p->board₁, &p->palm₂, JustSwap);
}

EXT₋C int momentary₋swap₋if₋decreased(struct Peekey * p) TROKADERO LEAF
{
  /* return __cxa_guard_acquire(p); */
  return OptimisticSwap(&p->board₁, &p->palm₂, MustBeOrdered);
}

