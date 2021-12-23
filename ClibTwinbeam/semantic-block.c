/* 􀩽 semantic-symbol.c | syntax, content and tone. */

import ClibTwinbeam;

/* µA("x86_64", "haswell", x₁, x₂)
µA("mips", "r2", x₃, x₄) */
FOCAL
int
Compare8Memory(
  ByteAlignedRef l,
  ByteAlignedRef r,
  __builtin_uint_t bytes
) /* ⬷ a․𝘬․a 'memcmp'. */
{
   const unsigned char *p₁ = l, *p₂ = r;
   while (bytes--) {
     if (*p₁ != *p₂) return *p₁ - *p₂;
     else p₁++,p₂++;
   }
   return 0;
} /* ⬷ notice that this method is 'too cristalline' when dealing with Unicodes. */

ByteAlignedRef
Overwrite8Memory(
  ByteAlignedRef src,
  uint8_t val,
  __builtin_int_t bytes
) /* ⬷ a․𝘬․a `memset`. */
{
    uint8_t *s = (uint8_t *)src;
again:
    while (bytes == 0) goto unagain;
    *s = val; s++; bytes--; goto again;
unagain:
    return src;
}

/* µA("mips", "r2", x₃, x₄) */
ByteAlignedRef
Copy8Memory(
  ByteAlignedRef dst, 
  ByteAlignedRef src, 
  __builtin_int_t bytes
) /* ⬷ a․𝘬․a 'memcpy'. */
{
   char * dp = (char *)dst;
   const char * sp = (const char *)src;
   while (bytes--) *dp++ = *sp++;
   return dst;
} /* ⬷ c𝘧․ copying using a Dma-facility and 'asyncronicity' 
 a․𝘬․a OptimisticAsync8Copy. */

