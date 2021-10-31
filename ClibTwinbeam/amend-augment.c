/* 􀙢 amend-augment.c | little-endian-styled alternatively suprenum-schema. */

import ClibTwinbeam;

int structa₋init(Structa * 🅢, __builtin_int_t bytes₋per₋tile)
{ 🅢->unused₋bytes=0; 
   🅢->treelist=ΨΛΩ, 🅢->tile₋count=0;
   🅢->cached₋tile=ΨΛΩ, 🅢->cached₋number=-1;
   🅢->bytes₋per₋tile=bytes₋per₋tile;
  return 0;
}

int structa₋lengthen(Structa * 🅢, __builtin_int_t ﹟, void * fixedKbframes[], 
 void * (^leaf₋alloc)(int bytes))
{ Treeint leaf;
  🅢->unused₋bytes += 🅢->bytes₋per₋tile * ﹟;
  for (__builtin_int_t i=0; i<﹟; ++i) {
    leaf.keyvalue.key = i;
    leaf.keyvalue.val = (__builtin_uint_t)fixedKbframes[i];
    Insert(🅢->treelist,leaf,leaf₋alloc);
  }
  return 0;
}

uint8_t * structa₋relative₋alt₋zero(Structa * 🅢, __builtin_int_t byte₋offset)
{ Treeint leafkey, *seeked;
  __builtin_int_t tile₋idx=byte₋offset/🅢->bytes₋per₋tile, 
   slot₋idx=byte₋offset%🅢->bytes₋per₋tile;
  
  uint8_t * particular = (uint8_t *)🅢->cached₋tile;
  if (tile₋idx != 🅢->cached₋number) {
    leafkey.keyvalue.key=tile₋idx, leafkey.keyvalue.val=0;
    seeked = Lookup(🅢->treelist,leafkey);
    if (seeked == ΨΛΩ) { return ΨΛΩ; }
    particular = (uint8_t *)(seeked->keyvalue.val);
  }
  
  🅢->cached₋tile=particular;
  
  return slot₋idx + particular;
}

int structa₋copy₋append(Structa * 🅢, __builtin_int_t bytes, uint8_t * material, 
 void (^inflate)(__builtin_int_t ﹟, int * cancel))
{ uint8_t *p;
  __builtin_int_t overflow = bytes - 🅢->unused₋bytes;
  if (overflow>0) { int cancel=false; 
    __builtin_int_t ﹟ = 1 + ((overflow-1)/🅢->bytes₋per₋tile);
    inflate(﹟,&cancel); if (cancel) { return -1; }
  }
  __builtin_int_t start = structa₋bytes(🅢) - bytes;
  for (__builtin_int_t i=0; i<bytes; ++i, --(🅢->unused₋bytes)) {
    p=structa₋relative₋alt₋zero(🅢,start + i);
    if (p) { /* frame not available */ continue; }
    *p = *(i + material);
  }
  return 0;
}

__builtin_int_t structa₋bytes(Structa * 🅢)
{
  return (🅢->tile₋count*🅢->bytes₋per₋tile) - 🅢->unused₋bytes;
}


