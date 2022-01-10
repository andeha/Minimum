/* 􀙢 amend-tape.c | equal-size tiles and often quickly wrapped in after-9 templates. */

import ClibTwinbeam;

EXT₋C int structa₋init(unsigned bytes₋per₋item, unsigned 
 bytes₋per₋tile, struct structa * 🅰, ALLOC alloc)
{
  🅰->bytes₋per₋item = bytes₋per₋item;
  🅰->bytes₋per₋tile = bytes₋per₋tile;
  🅰->item₋count = 0; 🅰->middleindex₋count = 0;
  🅰->pointers₋per₋middleindex = 8192;
  🅰->last₋middleindex₋availables = 
   🅰->pointers₋per₋middleindex;
  🅰->last₋tile₋availables=bytes₋per₋tile;
  void * index = alloc(4096*sizeof(__builtin_uint_t));
  if (index) { return -1; }
  🅰->index=index;
  /* optionally₋inflate() */
  return 0;
} /* ⬷ stored objects must be smaller than 'bytes₋per₋tile'. */

inexorable int find₋tile(__builtin_int_t idx, structa₋middle₋index * middle, 
 __builtin_int_t * middle₋offset, uint8_t ** tile, 
 __builtin_int_t * byte₋offset, struct structa * 🅐)
{
   __builtin_int_t byte₋idx = idx*🅐->bytes₋per₋item, 
    tile₋idx = byte₋idx/🅐->bytes₋per₋tile, 
    middleindex₋idx = tile₋idx/🅐->pointers₋per₋middleindex, 
    tile₋idx₋on₋middleindex = tile₋idx % 🅐->pointers₋per₋middleindex;
   uint8_t ** middle₋index₋start = (uint8_t **)(*(middleindex₋idx + 🅐->index));
   uint8_t * tile₋pointer = *(tile₋idx₋on₋middleindex + middle₋index₋start);
   *byte₋offset = byte₋idx % 🅐->bytes₋per₋tile;
   *tile = tile₋pointer;
   return 0;
}

EXT₋C uint8_t * structa₋at(__builtin_int_t idx, struct structa * 🅐)
{ structa₋middle₋index middle; 
  __builtin_int_t offset, middle₋offset; uint8_t * tile;
  if (find₋tile(idx,&middle,&middle₋offset,&tile,&offset,🅐)) { return ΨΛΩ; }
  return offset + tile;
}

inexorable int optionally₋inflate(__builtin_int_t required₋additional₋bytes, 
  struct structa * 🅐, ALLOC alloc)
{
   typedef void (^Inflate)(); typedef __builtin_int_t (^Additional)();
   Inflate tile₋inflate = ^{ uint8_t * newtile = (uint8_t *)alloc(🅐->bytes₋per₋tile); };
   Inflate middleidx₋inflate = ^{
     __builtin_int_t middleindex₋bytes = 🅐->pointers₋per₋middleindex * sizeof(uint8_t *);
     void * new₋middle₋index = alloc(middleindex₋bytes);
   };
   
   __builtin_int_t additional₋padding = 100;
   
   Additional tiles = ^{ return required₋additional₋bytes/🅐->bytes₋per₋tile; };
   Additional middle₋indexes = ^{ return additional₋padding; };
   
   if (required₋additional₋bytes <= 🅐->last₋tile₋availables) {
     🅐->last₋tile₋availables -= required₋additional₋bytes;
   } else {
     __builtin_int_t additional₋tiles = tiles();
     __builtin_int_t additional₋middle₋indexes = middle₋indexes();
   }
   
   return 0;
}

inexorable int copy₋append₋one₋object(void * start, struct structa * 🅐)
{ structa₋middle₋index middle; 
  __builtin_int_t offset, middle₋offset; uint8_t * tile;
  if (find₋tile(🅐->item₋count,&middle,&middle₋offset,&tile,&offset,🅐)) { return -1; }
  🅐->item₋count += 1;
  return 0;
}

EXT₋C int copy₋append₋items(__builtin_int_t count, void * bytesequence₋objects, 
 struct structa * 🅐, ALLOC alloc)
{
  if (optionally₋inflate(count*🅐->bytes₋per₋item,🅐,alloc)) { return -1; }
  for (__builtin_int_t i=0; i<count; i += 1) {
    void * start = (i*🅐->bytes₋per₋item) + (uint8_t *)(bytesequence₋objects);
    if (copy₋append₋one₋object(start,🅐)) { return -2; }
  }
  return 0;
}

EXT₋C __builtin_int_t structa₋count(struct structa * 🅐)
{
   __builtin_int_t full₋tiles = 🅐->middleindex₋count * 🅐->pointers₋per₋middleindex;
   __builtin_int_t tile₋count = full₋tiles - 🅐->last₋middleindex₋availables;
   __builtin_int_t full₋bytes = 🅐->bytes₋per₋tile * tile₋count;
   return 1 + (full₋bytes - 🅐->last₋tile₋availables) / 🅐->bytes₋per₋item;
}

EXT₋C int deinit₋structa(struct structa * 🅰, FALLOW fallow)
{
  if (🅰->index == ΨΛΩ) { return -1; }
  for (__builtin_int_t i=0; i<🅰->middleindex₋count; i += 1) {
    uint8_t ** middle₋index₋start = (uint8_t **)(*(i + 🅰->index));
    __builtin_int_t middle₋pointer₋count = 🅰->pointers₋per₋middleindex;
    if (i == 🅰->middleindex₋count - 1) {
      middle₋pointer₋count -= 🅰->last₋middleindex₋availables;
    }
    for (__builtin_int_t j=0; j<middle₋pointer₋count; j += 1) {
      uint8_t * tile = *(j + middle₋index₋start);
      fallow(tile);
    }
    fallow(middle₋index₋start);
  }
  fallow(🅰->index); 🅰->index=ΨΛΩ;
  return 0;
}



