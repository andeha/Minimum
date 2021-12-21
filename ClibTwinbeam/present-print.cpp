/* 􀣚 present-print.cpp | 'det' blev icke-klart och presenterades som 'ordning olika'. */

import ClibTwinbeam;
import Stdio;

/* #define UNEXISTING₋IEEE754 */

EXT₋C Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, .kind=1 }; }
EXT₋C Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { { .x=x }, 2 }; }
EXT₋C Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { { .b=b }, 3 }; }
EXT₋C Argᴾ ﹟s8(const char8₋t * u8s) a⃝ { return Argᴾ { { .u8s=(char8₋t *)u8s }, 4 }; }
EXT₋C Argᴾ ﹟s7(const /* signed */ char * s) a⃝ { return Argᴾ { { .u8s=(char8₋t *)s }, 4 }; }
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, const char32̄_t * unterminated₋uc) a⃝ { 
  return Argᴾ { { .ucs={ tetras, (char32̄_t *)unterminated₋uc } }, 5 }; }
EXT₋C Argᴾ ﹟S(const char32̄_t * zero₋terminated₋uc) a⃝ {
  __builtin_int_t tetras=TetrasUntilNull((char32̄_t *)zero₋terminated₋uc,BUILTIN₋INT₋MAX);
 return Argᴾ { { .ucs={ tetras, (char32̄_t *)zero₋terminated₋uc } }, 5 }; }
EXT₋C Argᴾ ﹟s7(__builtin_int_t characters, const /* signed */ char * s) a⃝ {
 return Argᴾ { { .text₁={ characters, (signed char *)s } }, 100 }; }
EXT₋C Argᴾ ﹟s8(__builtin_int_t bytes, const char8₋t * u8s) a⃝ {
 return Argᴾ { { .text₂={ bytes, (char8₋t *)u8s } }, 101 }; }
EXT₋C Argᴾ ﹟c8(char8₋t c) /* a⃝ */ { return Argᴾ { { .c=c }, 6 }; }
EXT₋C Argᴾ ﹟c7(/* signed */ char c) /* a⃝ */ { return Argᴾ { { .c=(char8₋t)c }, 6 }; }
EXT₋C Argᴾ ﹟C(char32̄_t C) { return Argᴾ { { .uc=C }, 7 }; }
#if defined 𝟷𝟸𝟾₋bit₋integers
EXT₋C Argᴾ ﹟U(__uint128_t U) { return Argᴾ { { .U=U }, 11 }; }
EXT₋C Argᴾ ﹟I(__int128_t I) { return Argᴾ { { .I=I }, 12 }; }
#endif
EXT₋C Argᴾ ﹟regs(__builtin_uint_t mask) { return Argᴾ { { .x=mask }, 13 }; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */

EXT₋C Argᴾ ﹟λ(Argᴾ₋output scalar, void * context) { return Argᴾ { { .λ={ scalar, context } }, 10 }; }

EXT₋C Argᴾ ﹟chapter(Unicodes ingress, Plate * anfang)
{
  return Argᴾ { { .chapter={ anfang, ingress } }, 88 };
} /* ⬷ see --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp> for details on PNG::IHDR. */

void Register₋reflect(__builtin_uint_t /* mask */) { }

inexorable void Present(void (^out)(char8₋t * u8s, __builtin_int_t bytes), char32̄_t * terminated₋ucs)
{
   __builtin_int_t tetras = TetrasUntilNull(terminated₋ucs,BUILTIN₋INT₋MAX);
   print(out, "⬚", ﹟S(tetras,terminated₋ucs));
}

inexorable void Coalesc₋present(void (^out)(int count, char32̄_t * unterminated₋ucs), int count, char32̄_t * unterminated₋ucs)
{
   
} /* ⬷ two 'async'-job alt. written coroutines alt. threads for example. */

#pragma mark - in /retrospect/, hidden yet simple:

EXT₋C Argᴾ ﹟F(double f, int format) { return Argᴾ { { .f₁=f } }; }

EXT₋C
int
print﹟(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{  __builtin_int_t i=0, incr; short followers; char32̄_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* bool may𝘖rDidEscape=false; */
    auto out₂ = ^(const char * 𝟽bit₋utf8, __builtin_int_t bytes) {
      out((char8₋t *)𝟽bit₋utf8, bytes); printedBytesExcept0 += bytes; };
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
    auto eight₋bit₋symbol = ^(char8₋t c) { out(&c,1); };
    auto u8c₋stream = ^(char8₋t * utf8) { char8₋t * p = (char8₋t *)utf8; while (*p) { out(p,1); p++; } };
    auto unicode₋symbol = ^(char32̄_t u) { UnicodeToUtf8(u, ^(char8₋t * u8s, 
     short bytes) { out(Critic(u8s),bytes); }); };
#ifndef UNEXISTING₋IEEE754
    auto out𝕕 = ^(double ℝ) {
      /* Format(ℝ, Ieee754form::Scientific, ^(char32̄_t uc) { unicode₋symbol(uc); }); */
      char buf[2048]; sprintf(buf, "%f",ℝ); u8c₋stream((char8₋t *)buf);
    };
#endif
    auto unicode₋stream = ^(int tetras, char32̄_t * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32̄_t uc = *(unicodes + beam); unicode₋symbol(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
#ifdef 𝟷𝟸𝟾₋bit₋integers
    auto 𝟷𝟸𝟾₋out𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿,1); }); };
    auto 𝟷𝟸𝟾₋out𝕟 = ^(__uint128_t U) { Base𝕟(U, 16, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋,1); }); };
#endif
again:
    auto leadOr8Bit = i + (char8₋t *)utf8format;
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
      case 5: unicode₋stream(a.value.ucs.tetras, a.value.ucs.unicodes); break;  \
      case 6: eight₋bit₋symbol(a.value.c); break;                               \
      case 7: unicode₋symbol(a.value.uc); break;                                
#ifndef UNEXISTING₋IEEE754
      case 8: out𝕕((double)(a.value.f₂)); break;                                \
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
       a.value.chapter.ingress.unicodes); break;                                \
      default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
        unicode₋symbol(U'?'); break; }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

extern "C" long write(int fd, const void * s, long unsigned nbyte);

FOCAL EXT₋C
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y;
#if defined __armv8a__ || defined __x86_64__
   bool original = false; int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
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
#if defined __armv8a__ || defined __x86_64__
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif  defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
EXT₋C
int
print(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  ...
) a⃝
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
}

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
  void (^out)(char8₋t * u8s, __builtin_int_t bytes)
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
  void (^out)(char8₋t * u8s, __builtin_int_t bytes)
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
   print(out, "⬚\n", ﹟s7(Vt99::bright));
   Present(out,Critic(ar->header));
   print(out, "⬚ = ⬚ 0x", ﹟s7(Vt99::reset), ﹟s7(Vt99::reverse));
   Base𝕟((__builtin_uint_t)numerics, 16, 8, ^(char 𝟶to𝟿) { print(out,"⬚", ﹟c7(𝟶to𝟿)); });
   print(out, "⬚\n\n", ﹟s7(Vt99::reset));
   present(ar->regcnt,ar->regs,numerics,ar->init);
   Present(out,Critic(ar->footnote));
   print(out,"\n\n");
}



