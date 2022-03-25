/*  endian-base.c | forward-only alternatively planning. */

import ClibTwinbeam;

#if defined(𝟷𝟸𝟾₋bit₋integers)

EXT₋C
void Base𝕫(__int128_t ℤ, 
  unsigned short base, unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿and₋)
) ⓣ
{
  if (ℤ < +0) { out('-'); ℤ = -ℤ; }
  Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, out);
}

EXT₋C
void
Base𝕟(
  __uint128_t ℕ, 
  unsigned short base, 
  unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿)
) ⓣ
{
   typedef void (^Out)(unsigned short r, void (^out)(char));
   Out 𝟶to𝖥 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
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
) ⓣ
{
   typedef void (^Out)(unsigned short r, void (^out)(char));
   Out 𝟬to𝗙 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
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

EXT₋C
void
Base𝕫(
  __builtin_int_t ℤ,
  unsigned short base,
  unsigned short digitsOr0,
  void (^output)(char 𝟬to𝟵and₋)
) ⓣ
{
   if (ℤ < 0) { output('-'); ℤ = -ℤ; }
   Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, output);
}


