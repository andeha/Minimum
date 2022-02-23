/*  big-concrete.c | a 128-bit search tree. */

import ClibTwinbeam;

__uint128_t FNV1b(__builtin_int_t bytes, void * material)
{
   __uint128_t prime = (__uint128_t)0b1<<88 | 0b1<<8 | 0x3b, 
    h = ((__uint128_t)(0x6c62272e07bb0142))<<64 | 0x62b821756295c58d;
    uint8_t * p = (uint8_t *)material;
    for (__builtin_int_t i=0; i<bytes; i+=1) {
      h = h ^ (h ^ prime) * p[i];
    }
    return h;
}

inexorable struct w₋node * new₋node(__uint128_t fineprint, ALLOC alloc)
{
   struct w₋node * node = (struct w₋node *)alloc(sizeof(struct w₋node));
   if (node == ΨΛΩ) { return ΨΛΩ; }
   node->key = fineprint; node->left=ΨΛΩ; node->right=ΨΛΩ;
   return node;
}

void * impression₋seek(void ᶿ﹡ opaque, __uint128_t target)
{ struct w₋node * node = (struct w₋node *)opaque;
   if (node == ΨΛΩ) { return ΨΛΩ; }
   else { if (target == node->key) { return node; }
     if (target < node->key) return impression₋seek(node->left,target);
     else return impression₋seek(node->right,target);
   }
}

void * impression₋store(void ᶿ﹡ opaque, __uint128_t fineprint, ALLOC alloc)
{ struct w₋node * node = (struct w₋node *)opaque;
   if (opaque == ΨΛΩ) { return new₋node(fineprint,alloc); }
   else {
     if (fineprint <= node->key) {
       node->left = impression₋store(node->left,fineprint,alloc);
     } else { node->right=impression₋store(node->right,fineprint,alloc); }
     return node;
   }
}

/* void * Impression₋store(void ᶿ﹡* opaque, __uint128_t fineprint, ALLOC alloc)
{
   struct w₋node * node = impression₋store(*opaque,fineprint,alloc);
   if (*opaque == ΨΛΩ) { *opaque = node; }
} */

notepointer jot(struct Unicodes token, void ᶿ﹡* opaque, __builtin_int_t 
 notebytes, ALLOC alloc, INIT init)
{ __uint128_t fineprint=FNV1b(4*token.tetras,(void *)token.unicodes);
  struct w₋node * node = (struct w₋node *)impression₋seek(*opaque,fineprint);
  if (node == ΨΛΩ) {
    node = (struct w₋node *)impression₋store(*opaque,fineprint,alloc);
    node->note = alloc(notebytes);
    if (init(node->note)) { return ΨΛΩ; }
  }
  if (*opaque == ΨΛΩ) { *opaque=node; }
  return node->note;
}

