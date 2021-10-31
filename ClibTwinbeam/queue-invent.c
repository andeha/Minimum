/* 􀻸 ätstörning.c | biblic fold military projects measured. */

import ClibTwinbeam;

int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * 𝟷₋tile)
{
   🅵->words₋to₋unity = words;
   🅵->brk=0; 🅵->count=0;
   🅵->𝟷₋tile = (__builtin_uint_t *)𝟷₋tile;
   return 0;
}

void 𝟷₋tile₋fifo₋pop(struct fifo * 🅵)
{ 🅵->brk -= 1;
  if (🅵->brk < 0) { 🅵->brk = 🅵->words₋to₋unity - 1; }
  🅵->count -= 1;
}

inexorable void 
Copy(__builtin_int_t 𝟹𝟸or64₋words,
 __builtin_uint_t * src, __builtin_uint_t * dst
)
{
  Copy8Memory((ByteAlignedRef)dst, (ByteAlignedRef)src, Wordbytes * 𝟹𝟸or64₋words);
}

int 𝟷₋tile₋copy₋include(struct fifo * 🅵, __builtin_int_t ﹟, __builtin_uint_t * Ɀ)
{
   if (﹟ > 🅵->words₋to₋unity) { return -1; }
   __builtin_int_t elems₋until₋wrap = min(﹟, 🅵->words₋to₋unity - 🅵->brk);
   Copy(elems₋until₋wrap, Ɀ, 🅵->brk + 🅵->𝟷₋tile);
   __builtin_int_t elems₋after₋wrap = ﹟ - elems₋until₋wrap;
   if (elems₋after₋wrap > 0) { Copy(elems₋after₋wrap, Ɀ + elems₋until₋wrap, 🅵->𝟷₋tile); }
   🅵->count = min(🅵->count + ﹟, 🅵->words₋to₋unity);
   __builtin_int_t unwrapped₋new₋brk = 🅵->brk + ﹟;
   if (unwrapped₋new₋brk < 🅵->words₋to₋unity) { 🅵->brk = unwrapped₋new₋brk; }
   else { 🅵->brk = 🅵->words₋to₋unity - unwrapped₋new₋brk; }
   return 0;
}

int 𝟷₋tile₋shiftout(struct fifo * 🅵, __builtin_int_t words)
{ 🅵->count -= words; return 0; }


