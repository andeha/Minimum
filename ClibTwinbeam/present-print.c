/* 􀣚 present-print.cpp | 'det' blev icke-klart och presenterades som 'ordning olika'. */

import ClibTwinbeam;
import Stdio;

/* #define UNEXISTING₋IEEE754 */

EXT₋C Argᴾ ﹟d(__builtin_int_t d) { Argᴾ y = { .value.d=d, .kind=1 }; return y; }
EXT₋C Argᴾ ﹟x(__builtin_uint_t x) { Argᴾ y = { { .x=x }, 2 }; return y; }
EXT₋C Argᴾ ﹟b(__builtin_uint_t b) { Argᴾ y = { { .b=b }, 3 }; return y; }
EXT₋C Argᴾ ﹟s8(const char8₋t * u8s) ⓣ { Argᴾ y = { { .u8s=(char8₋t *)u8s }, 4 }; return y; }
EXT₋C Argᴾ ﹟s7(const /* signed */ char * s) ⓣ { Argᴾ y = { { .u8s=(char8₋t *)s }, 4 }; return y; }
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, const char32̄_t * unterminated₋uc) ⓣ { 
  Argᴾ y = { { .ucs={ tetras, (char32̄_t *)unterminated₋uc } }, 5 }; return y; }
EXT₋C Argᴾ ﹟S(const char32̄_t * zero₋terminated₋uc) ⓣ {
  __builtin_int_t tetras=TetrasUntilZero((char32̄_t *)zero₋terminated₋uc,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .ucs={ tetras, (char32̄_t *)zero₋terminated₋uc } }, 5 };
  return y; }
EXT₋C Argᴾ ﹟s7(__builtin_int_t characters, signed char * keyput) ⓣ {
 Argᴾ y = { { .text₁={ characters, keyput } }, 100 }; return y; }
EXT₋C Argᴾ ﹟s8(__builtin_int_t bytes, const char8₋t * u8s) ⓣ {
 Argᴾ y= { { .text₂={ bytes, (char8₋t *)u8s } }, 101 }; return y; }
EXT₋C Argᴾ ﹟c8(char8₋t c) /* a⃝ */ { Argᴾ y= { { .c=c }, 6 }; return y; }
EXT₋C Argᴾ ﹟c7(/* signed */ char c) /* a⃝ */ { Argᴾ y= { { .c=(char8₋t)c }, 6 }; return y; }
EXT₋C Argᴾ ﹟C(char32̄_t C) { Argᴾ y = { { .uc=C }, 7 }; return y; }
#if defined 𝟷𝟸𝟾₋bit₋integers
EXT₋C Argᴾ ﹟U(__uint128_t U) { Argᴾ y = { { .U=U }, 11 }; return y; }
EXT₋C Argᴾ ﹟I(__int128_t I) { Argᴾ y = { { .I=I }, 12 }; return y; }
#endif
EXT₋C Argᴾ ﹟regs(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 13 }; return y; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */

EXT₋C Argᴾ ﹟λ(Argᴾ₋output₋p scalar, void * context) { Argᴾ y = { .λ₋p={ scalar, context }, .kind=10 }; return y; }

EXT₋C Argᴾ ﹟chapter(double multiple, struct Plate * anfang)
{
  Argᴾ y = { .chapter={ anfang, multiple }, .kind=88 }; return y;
} /* ⬷ see --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp> for details on PNG::IHDR. */

void Register₋reflect(__builtin_uint_t /* mask */) { }

inexorable void Present(void (^out)(char8₋t * u8s, __builtin_int_t bytes), char32̄_t * terminated₋ucs)
{
   __builtin_int_t tetras = TetrasUntilZero(terminated₋ucs,BUILTIN₋INT₋MAX);
   print(out, "⬚", ﹟S(tetras,terminated₋ucs));
}

inexorable void Coalesc₋present(void (^out)(int count, char32̄_t * unterminated₋ucs), int count, char32̄_t * unterminated₋ucs)
{
   
} /* ⬷ two 'async'-job alt. written coroutines alt. threads for example. */

#pragma mark - in /retrospect/, hidden yet simple:

EXT₋C Argᴾ ﹟F(double f, int format) { Argᴾ y = { { .f₁=f } }; return y; }

EXT₋C
int
print﹟(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{  __builtin_int_t i=0, incr; short followers; char32̄_t uc; char8₋t *leadOr8Bit;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* bool may𝘖rDidEscape=false; */
    typedef void (^Out₂)(const char *,__builtin_int_t);
    typedef void (^Out𝕫)(__builtin_int_t);
    typedef void (^Out𝕟)(__builtin_uint_t);
    typedef void (^Out₋𝟷𝟶𝟷𝟷𝟶)(__builtin_uint_t);
    typedef void (^Eight₋bit₋symbol)(char8₋t);
    typedef void (^U8c₋stream)(char8₋t *);
    typedef void (^Unicode₋symbol)(char32̄_t);
    typedef void (^Out𝕕)(double);
    typedef void (^Unicode₋stream)(int,char32̄_t *);
    typedef void (^𝟷𝟸𝟾₋Out𝕫)(__int128_t);
    typedef void (^𝟷𝟸𝟾₋Out𝕟)(__uint128_t);
    Out₂ out₂ = ^(const char * 𝟽bit₋utf8, __builtin_int_t bytes) {
      out((char8₋t *)𝟽bit₋utf8, bytes); printedBytesExcept0 += bytes; };
    Out𝕫 out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s,1); }); };
    Out𝕟 out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16, 
#if defined __x86_64__ || defined __arm64__ || Kirkbridge
      16
#elif defined  __mips__ || defined __armv6__ || defined espressif
       8
#endif
      , ^(char s) { out₂(&s,1); }); };
    Out₋𝟷𝟶𝟷𝟷𝟶 𝟷𝟶𝟷𝟷𝟶₋out = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#if defined __x86_64__ || defined __arm64__ || Kirkbridge
       64
#elif defined  __mips__ || defined __armv6__ || defined espressif
       32
#endif
      , ^(char s) { out₂(&s,1); }); };
    Eight₋bit₋symbol eight₋bit₋symbol = ^(char8₋t c) { out(&c,1); };
    U8c₋stream u8c₋stream = ^(char8₋t * utf8) { char8₋t * p = (char8₋t *)utf8; while (*p) { out(p,1); ++p; } };
    Unicode₋symbol unicode₋symbol = ^(char32̄_t u) { UnicodeToUtf8(u, ^(char8₋t * u8s, 
     short bytes) { out(u8s,bytes); }); };
#ifndef UNEXISTING₋IEEE754
    Out𝕕 out𝕕 = ^(double ℝ) {
      /* Format(ℝ, Ieee754form::Scientific, ^(char32̄_t uc) { unicode₋symbol(uc); }); */
      char buf[2048]; sprintf(buf, "%f",ℝ); u8c₋stream((char8₋t *)buf);
    };
#endif
    Unicode₋stream unicode₋stream = ^(int tetras, char32̄_t * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32̄_t uc = *(unicodes + beam); unicode₋symbol(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
#ifdef 𝟷𝟸𝟾₋bit₋integers
    𝟷𝟸𝟾₋Out𝕫 𝟷𝟸𝟾₋out𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿,1); }); };
    𝟷𝟸𝟾₋Out𝕟 𝟷𝟸𝟾₋out𝕟 = ^(__uint128_t U) { Base𝕟(U, 16, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋,1); }); };
#endif
again:
    leadOr8Bit = i + (char8₋t *)utf8format;
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
      case 88: /* unicode₋stream(a.value.chapter.anfang,                        \
       a.chapter.ingress.unicodes); */ break;                                   \
      default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
        unicode₋symbol(U'?'); break; }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

EXT₋C long write(int fd, const void * s, long unsigned nbyte);

FOCAL EXT₋C
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y;
   typedef void (^Out)(char8₋t *, __builtin_int_t);
#if defined __arm64__ || defined __x86_64__ || Kirkbridge
   int original = false; int descript = original ? 1 /* stdout */ : 2 /* stderr */;
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
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
print(const char * utf8format, ...) ⓣ /* Here all variable args are of the type `Argᴾ`. */
{ int y; va_prologue(utf8format);
   typedef void (^Out)(char8₋t *, __builtin_int_t);
#if defined __arm64__ || defined __x86_64__ || defined Kirkbridge
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif  defined __mips__ || defined espressif || defined __armv6__
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
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
) ⓣ
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
}

#define VT99₋BRIGHT "\x1B[1m"
#define VT99₋DIM "\x1B[2m"
#define VT99₋BLUE "\x1B[34m"
#define VT99₋RED "\x1B[31m"
#define VT99₋RESET "\x1B[0m"
#define VT99₋REVERSE "\x1B[7m"

inexorable
void
Present₋Bitfield(struct Bitfield * field, 
  uint32_t numerics, uint32_t init, 
  int is₋𝟷𝟼₋bits, 
  int maxwidth, 
  /* void (^output)(char32_t uc) */
  /* void (^sometime)(int count, char32_t * terminated₋ucs) */
  void (^out)(char8₋t * u8s, __builtin_int_t bytes)
)
{
   unsigned spaces = maxwidth - TetrasUntilZero((char32̄_t *)(field->regular), BUILTIN₋INT₋MAX);
   while (spaces--) { print(out," "); }
   
   Present(out,(char32̄_t *)(field->regular)); print(out, " ");
   
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int masking=false; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 unsigned pos=31;
   Base𝕟((__builtin_uint_t)(field->mask), 2, 32, ^(char digit) {
     if (is₋𝟷𝟼₋bits && pos > 15) { print(out, "x"); } else {
      if (digit == '1' && !masking) { masking = true; }
      if (masking && digit == '0') { masking = false; }
      if (masking) { print(out, numerics & (0b1<<pos) ? "1" : "0"); }
      if (!masking) { print(out, "␣"); } }
     if (pos % 4 == 0) print(out, "|"); --pos;
   });
   
   Present(out,(char32̄_t *)(field->text)); print(out,"\n");
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
   typedef void (^PresenT)(int, struct Bitfield *, uint32_t, uint32_t);
   PresenT present = ^(int count, struct Bitfield * regs, uint32_t val, 
        uint32_t init) { __builtin_int_t maxwidth=0; 
      for (int i=0; i<count; ++i) {
         const struct Bitfield * reg = regs + i; maxwidth = max(maxwidth, 
          TetrasUntilZero((char32̄_t *)(reg->regular), BUILTIN₋INT₋MAX));
      }
      for (int i=0; i<count; ++i) {
         Present₋Bitfield((regs + i), val, init, is₋𝟷𝟼₋bits, maxwidth, out);
      }
   };
   print(out, "⬚\n", ﹟s7(VT99₋BRIGHT));
   Present(out,(char32̄_t *)(ar->header));
   print(out, "⬚ = ⬚ 0x", ﹟s7(VT99₋RESET), ﹟s7(VT99₋REVERSE));
   Base𝕟((__builtin_uint_t)numerics, 16, 8, ^(char 𝟶to𝟿) { print(out,"⬚", ﹟c7(𝟶to𝟿)); });
   print(out, "⬚\n\n", ﹟s7(VT99₋RESET));
   present(ar->regcnt,ar->regs,numerics,ar->init);
   Present(out,(char32̄_t *)(ar->footnote));
   print(out,"\n\n");
}

