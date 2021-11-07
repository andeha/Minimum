/*  stack-error.c | job-piles, the irreversibility of time and 'waiting for'. */

import ClibTwinbeam;

int init₋stack(struct ¹stack * 🆇, short bytes₋per₋elem) a⃝
{
   🆇->pos=0; 🆇->size=8; 🆇->words = 
    (uint8_t *)Heap₋alloc(🆇->size*bytes₋per₋elem);
   if (🆇->words == ΨΛΩ) { 🆇->size=0; return -1; }
   🆇->elem₋bytesize=bytes₋per₋elem;
   return 0;
}

void unalloc₋stack(struct ¹stack * 🆇) a⃝
{
   if (🆇->words != ΨΛΩ) { Heap₋unalloc(🆇->words); }
   🆇->pos=0; 🆇->size=0; 🆇->words=ΨΛΩ;
}

inexorable int expand₋stack(struct ¹stack * 🅧) a⃝
{
   __builtin_uint_t new_size = 🅧->size << 1;
   __builtin_int_t new_bytes=new_size*🅧->elem₋bytesize;
   uint8_t * new_words = (uint8_t *)Heap₋alloc(new_bytes);
   Copy8Memory((ByteAlignedRef)new_words, (ByteAlignedRef)🅧->words, new_bytes);
   Heap₋unalloc(🅧->words); /* ⬷ a․𝘬․a realloc. */
   🅧->words=new_words;
   🅧->size=new_size;
   return 0;
}

int push(struct ¹stack * 🅧, uint8_t * item) a⃝
{
   if (🅧->pos == 🅧->size) {
     if (expand₋stack(🅧)) { return -1; }
   }
   ByteAlignedRef dst = (ByteAlignedRef)(🅧->pos + 🅧->words);
   ByteAlignedRef src = (ByteAlignedRef)item;
   __builtin_int_t bytes = 🅧->elem₋bytesize;
   Copy8Memory(dst,src,bytes);
   🅧->pos++;
   return 0;
}

inexorable uint8_t * top(struct ¹stack * 🅧) a⃝
{
   return 🅧->pos == 0 ? ΨΛΩ : (🅧->pos - 1) + 🅧->words;
}

uint8_t * pop(struct ¹stack * 🅧) a⃝
{
   uint8_t * bytes = top(🅧);
   if (🅧->pos > 0) { 🅧->pos--; }
   return bytes;
}

int empty(struct ¹stack * 🅧) a⃝ { return 🅧->pos == 0; }


