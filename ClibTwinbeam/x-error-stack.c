/*  stack-error.c | job-piles, the irreversibility of time and 'waiting for'. */

import ClibTwinbeam;

int init₋stack(struct ¹stack * 🆇, short bytes₋per₋element) ⓣ
{
   🆇->initial₋area₋alloc = ^(__builtin_int_t bytes) { return Heap₋alloc(bytes); };
   🆇->area₋dealloc = ^(void * p) { Heap₋unalloc(p); };
   🆇->area₋realloc = ^(void * p, __builtin_int_t to₋bytes) { return Heap₋realloc(p,to₋bytes); };
   __builtin_int_t count = 1 + 4096/bytes₋per₋element;
   🆇->pos=0; 🆇->size=count; 🆇->words = 
    (uint8_t *)🆇->initial₋area₋alloc(🆇->size*bytes₋per₋element);
   if (🆇->words == ΨΛΩ) { 🆇->size=0; return -1; }
   🆇->elem₋bytesize=bytes₋per₋element;
   return 0;
}

void stack₋unalloc(struct ¹stack * 🆇) ⓣ
{
   if (🆇->words != ΨΛΩ) { 🆇->area₋dealloc(🆇->words); }
   🆇->pos=0; 🆇->size=0; 🆇->words=ΨΛΩ;
}

inexorable int expand₋stack(struct ¹stack * 🅧) ⓣ
{
   __builtin_uint_t new_size = 🅧->size << 1;
   __builtin_int_t new_bytes=new_size*🅧->elem₋bytesize;
   uint8_t * new_words = (uint8_t *)🅧->area₋realloc(🅧->words,new_bytes);
   🅧->words=new_words;
   🅧->size=new_size;
   return 0;
}

int stack₋push(struct ¹stack * 🅧, uint8_t * item) ⓣ
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

uint8_t * stack₋top(struct ¹stack * 🅧) ⓣ
{
   return 🅧->pos == 0 ? ΨΛΩ : (🅧->pos - 1) + 🅧->words;
}

uint8_t * stack₋pop(struct ¹stack * 🅧) ⓣ
{
   uint8_t * bytes = stack₋top(🅧);
   if (🅧->pos > 0) { 🅧->pos--; }
   return bytes;
}

__builtin_int_t stack₋count(struct ¹stack * 🅧) ⓣ { return 🅧->pos; }

int stack₋empty(struct ¹stack * 🅧) ⓣ { return 🅧->pos == 0; }

