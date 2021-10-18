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
} /*  ⬷ note 128-bit duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> and --<Print.cpp>. */

__builtin_int_t TetrasUntilNull(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t i=0;
again:
   if (i >= maxtetras) { return maxtetras; }
   char32_t * uc = ucs + i;
   if (*uc == 0x0000) { return i; }
   ++i; goto again;
}

inexorable
void
NumberformatCatalogue₋Present₋inner(struct Bitfield * field, 
  uint32_t numerics, uint32_t init, 
  int is₋𝟷𝟼₋bits, 
  int maxwidth, 
  void (^out)(char32_t uc)
)
{
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Present(term,u8s,bytes); };
   unsigned spaces = maxwidth - TetrasUntilNull(Critic(field->regular), BUILTIN₋INT₋MAX);
   while (spaces--) { print(out," "); }
   
   Present(term,Critic(field->regular)); print(out, " ");
   
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bool masking=false; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 unsigned pos=31;
   Base𝕟((__builtin_uint_t)(field->mask), 2, 32, ^(char 𝟶to𝟿) {
     if (is₋𝟷𝟼₋bits && pos > 15) { print(out, "﹟"); }
     if (!is₋𝟷𝟼₋bits && 𝟶to𝟿 == '1' && !masking) { masking = true; }
     if (!is₋𝟷𝟼₋bits && masking && 𝟶to𝟿 == '0') { masking = false; }
     if (!is₋𝟷𝟼₋bits && masking) { print(out, numerics & (0b1<<pos) ? "1" : "0"); }
     if (!is₋𝟷𝟼₋bits && !masking) { print(out, "␣"); }
     if (pos % 4 == 0) print(out, "|"); --pos;
   });
   
   Present(term,Critic(field->text)); print(out,"\n");
}

FOCAL EXT₋C
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
   Present(term,Critic(ar->header));
   print(out, "⬚ = ⬚ 0x", ﹟s(Vt99::reset), ﹟s(Vt99::reverse));
   Base𝕟((__builtin_uint_t)numerics, 16, 8, ^(char 𝟶to𝟿) { print(out,"⬚", ﹟c(𝟶to𝟿)); });
   print(out, "⬚\n\n", ﹟s(Vt99::reset));
   present(ar->regcnt,ar->regs,numerics,ar->init);
   Present(term,Critic(ar->footnote));
   print(out,"\n\n");
}

#pragma mark - Inte₋ger₋s

EXT₋C Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, .kind=1 }; }
EXT₋C Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { { .x=x }, 2 }; }
EXT₋C Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { { .b=b }, 3 }; }
EXT₋C Argᴾ ﹟s(const char8_t * utf8) { return Argᴾ { { .utf8=Critic(utf8) }, 4 }; }
EXT₋C Argᴾ ﹟s(char8_t * utf8) { return Argᴾ { { .utf8=utf8 }, 4 }; }
EXT₋C Argᴾ ﹟s(const char * utf8) { return Argᴾ { { .utf8=(char8_t *)utf8 }, 4 }; }
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, char32_t * uc) { return Argᴾ { { .ucs={ uc, tetras } }, 5 }; }
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, const char32_t * uc) { return Argᴾ { { .ucs={ Critic(uc), tetras } }, 5 }; }
EXT₋C Argᴾ ﹟c(char8_t c) { return Argᴾ { { .c=c }, 6 }; }
EXT₋C Argᴾ ﹟c(char c) { return Argᴾ { { .c=(char8_t)c }, 6 }; }
EXT₋C Argᴾ ﹟C(char32_t C) { return Argᴾ { { .uc=C }, 7 }; }
#if defined 𝟷𝟸𝟾₋bit₋integers
EXT₋C Argᴾ ﹟U(__uint128_t U) { return Argᴾ { { .U=U }, 11 }; }
EXT₋C Argᴾ ﹟I(__int128_t I) { return Argᴾ { { .I=I }, 12 }; }
#endif
EXT₋C Argᴾ ﹟regs(__builtin_uint_t mask) { return Argᴾ { { .x=mask }, 13 }; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */
EXT₋C Argᴾ ﹟λ(Argᴾ::Output scalar, void * context) { return Argᴾ { { .λ={ scalar, context } }, 10 }; }

#pragma mark - in /retrospect/, hidden yet simple:

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
    auto u8c₋stream = ^(const char8_t * utf8) { char8_t * p = (char8_t *)utf8; while (*p) { out(p,1); p++; } };
    auto unicode₋symbol = ^(char32_t u) { UnicodeToUtf8(u, ^(char8_t * u8s, 
     short bytes) { out(Critic(u8s),bytes); }); };
/* #ifndef UNEXISTING₋IEEE754 */
    auto out𝕕 = ^(double ℝ) { Format(ℝ, Ieee754form::Scientific, ^(char32_t uc) { unicode₋symbol(uc); }); };
/* #endif */
    auto unicode₋stream = ^(int tetras, char32_t 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 * unicodes) { __builtin_int_t 
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
      case 4: u8c₋stream(a.value.utf8); break;                                  \
      case 5: unicode₋stream(a.value.ucs.tetras, a.value.ucs.unicodes); break;  \
      case 6: eight₋bit₋symbol(a.value.c); break;                               \
      case 7: unicode₋symbol(a.value.uc); break;                                \
      case 8: out𝕕(double(a.value.f₂)); break;                                  \
      case 9: out𝕕(a.value.f₁); break;                                          \
      case 10: { Argᴾ::Unicode set = ^(bool anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, \
       void * context) { if (!anfang) { print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); }    \
       else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,        \
       a.value.λ.context); break; }
#ifdef 𝟷𝟸𝟾₋bit₋integers
      case 11: 𝟷𝟸𝟾₋out𝕟(a.value.U); break;                                      \
      case 12: 𝟷𝟸𝟾₋out𝕫(a.value.I); break;
#endif
      case 13: register₋reflect(a.value.x); break;                              \
      default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
        unicode₋symbol(U'?'); break; }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

#if defined __x86_64__
extern "C" long write(int fd, const void * s, long unsigned nbyte);
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
extern void (^Putₒ)(char8_t * u8s, __builtin_int_t bytes);
extern void (^Trace₁)(char8_t * u8s, __builtin_int_t bytes);
extern void (^Trace₂)(char8_t * u8s, __builtin_int_t bytes);
#endif

FOCAL EXT₋C
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y; va_prologue(utf8format);
#ifdef __x86_64__
   bool original = false;
   int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

/* #define va_prologue(symbol) __builtin_va_list __various; __builtin_va_start(__various,symbol);
int mfprint(const char * utf8format,...)
{
   int printedBytesExcept0; va_prologue(utf8format);
   printedBytesExcept0 = vfprintf(stderr,utf8format,__various);
   return printedBytesExcept0;
} */

FOCAL EXT₋C
int
print(const char * utf8format, ...) /* Here all variable args are of the type `Argᴾ`. */
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
)
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
} /* ⬷ a․𝘬․a `print⁺⁺`. See --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> for more details. */

