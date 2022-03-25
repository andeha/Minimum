/*  big-concrete.c | not longer than 128-bit search tree. */

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

inexorable struct w₋node * new₋node(__uint128_t fineprint, void * material, ALLOC alloc)
{
   struct w₋node * node = (struct w₋node *)alloc(sizeof(struct w₋node));
   if (node == ΨΛΩ) { return ΨΛΩ; }
   node->key = fineprint; node->left=ΨΛΩ; node->right=ΨΛΩ; node->material=material;
   return node;
}

struct w₋node * impression₋seek(void ᶿ﹡ opaque, __uint128_t target)
{ struct w₋node * node = (struct w₋node *)opaque;
   if (node == ΨΛΩ) { return ΨΛΩ; }
   else { if (target == node->key) { return node; }
     if (target < node->key) return impression₋seek(node->left,target);
     else return impression₋seek(node->right,target);
   }
} /* ⬷ returns the found node alternatively an empty pointer. */

struct w₋node * impression₋store(void ᶿ﹡ opaque, __uint128_t fineprint, 
 void * material, ALLOC alloc)
{ struct w₋node * node = (struct w₋node *)opaque;
   if (opaque == ΨΛΩ) { return new₋node(fineprint,material,alloc); }
   else {
     if (fineprint <= node->key) {
       node->left = impression₋store(node->left,fineprint,material,alloc);
     } else { node->right=impression₋store(node->right,fineprint,material,alloc); }
     return node;
   }
} /* ⬷ returns a reference to a newly created 'w₋node' in-case formerly 
 empty tree else returns unchanged pointer to opaque which is a w-node. */

notepointer jot(struct Unicodes token, void ᶿ﹡* opaque, __builtin_int_t 
 notebytes, ALLOC alloc, INIT init)
{ __uint128_t fineprint=FNV1b(token.tetras*4,token.unicodes);
  struct w₋node * node = impression₋seek(*opaque,fineprint);
  if (node == ΨΛΩ) {
    void * note = alloc(notebytes);
    if (init(note)) { return ΨΛΩ; }
    *opaque = impression₋store(*opaque,fineprint,note,alloc);
    return (notepointer)note;
  }
  return node->note;
}

