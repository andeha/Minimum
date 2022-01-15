/* 􀙢 amend-tape.c | equal-size tiles and often quickly wrapped in after-9 templates. */

import ClibTwinbeam;

EXT₋C int structa₋init(unsigned bytes₋per₋item, unsigned 
 bytes₋per₋tile, struct structa * 🅰, ALLOC alloc)
{
  🅰->bytes₋per₋item = bytes₋per₋item;
  🅰->bytes₋per₋tile = bytes₋per₋tile;
  🅰->item₋count=0; 🅰->tile₋count=0;
  return 0;
} /* ⬷ stored objects must be smaller than 'bytes₋per₋tile'. */

inexorable int find₋tile(__builtin_int_t idx, uint8_t **tile, 
 __builtin_int_t * byte₋offset, struct structa * 🅐)
{
   __builtin_int_t byte₋idx = idx*🅐->bytes₋per₋item, 
    tile₋idx = byte₋idx/🅐->bytes₋per₋tile, middle₋idx = tile₋idx/8192;
   struct middle₋index * middle = 🅐->middles[middle₋idx];
   __builtin_int_t local₋idx = tile₋idx % 8192;
   uint8_t * tile₋start = middle->tilerefs[local₋idx];
   *byte₋offset = byte₋idx % 🅐->bytes₋per₋tile;
   *tile = tile₋start;
   return 0;
}

EXT₋C uint8_t * structa₋at(__builtin_int_t idx, struct structa * 🅐)
{ __builtin_int_t offset; uint8_t * tile;
  if (find₋tile(idx,&tile,&offset,🅐)) { return ΨΛΩ; }
  return offset + tile;
}

inexorable void prepare₋middle(__builtin_int_t local, 
 struct structa * 🅐, ALLOC alloc) {
   struct middle₋index * newmiddle = (struct middle₋index *)
     alloc(sizeof(struct middle₋index));
   🅐->middles[local] = newmiddle;
}

inexorable void prepare₋tile(struct middle₋index * middle, 
 __builtin_int_t local, struct structa * 🅐, ALLOC alloc)
{
   uint8_t * newtile = (uint8_t *)alloc(🅐->bytes₋per₋tile);
   middle->tilerefs[local] = newtile;
}

inexorable int prepare₋middle₋and₋tile(__builtin_int_t tiles₋extra, 
 struct structa * 🅐, ALLOC alloc)
{ __builtin_int_t i=0, local₋tile₋idx = 🅐->tile₋count % 8192;
  __builtin_int_t middle₋idx = 🅐->tile₋count / 8192;
  if (🅐->tile₋count == 0) { prepare₋middle(0,🅐,alloc); }
again:
   if (i >= tiles₋extra) { return 0; }
   if (i % 8192 == 8191) { middle₋idx += 1; prepare₋middle(middle₋idx,🅐,alloc); }
   struct middle₋index * middle = 🅐->middles[middle₋idx];
   prepare₋tile(middle,local₋tile₋idx,🅐,alloc);
   local₋tile₋idx = (local₋tile₋idx + 1) % 8192;
   i += 1;
   goto again;
}

inexorable int optionally₋inflate(__builtin_int_t requires₋bytes, 
  struct structa * 🅐, ALLOC alloc)
{
   __builtin_int_t total₋bytes = 🅐->bytes₋per₋tile*🅐->tile₋count;
   __builtin_int_t used₋bytes = 🅐->bytes₋per₋item*🅐->item₋count;
   __builtin_int_t free₋bytes = total₋bytes - used₋bytes;
   if (free₋bytes >= requires₋bytes) { return 0; }
   __builtin_int_t bytes₋to₋allocate = requires₋bytes - free₋bytes;
   __builtin_int_t tiles₋extra = 1 + (bytes₋to₋allocate - 1)/🅐->bytes₋per₋tile;
   if (prepare₋middle₋and₋tile(tiles₋extra,🅐,alloc)) { return -1; }
   return 0;
}

inexorable int copy₋append₋one₋object(void * start, struct structa * 🅐)
{ uint8_t * tile; __builtin_int_t byte₋offset;
  if (find₋tile(🅐->item₋count,&tile,&byte₋offset,🅐)) { return -1; }
  ByteAlignedRef dst = byte₋offset + tile;
  Copy8Memory(dst,(ByteAlignedRef)start,🅐->bytes₋per₋item);
  🅐->item₋count += 1;
  return 0;
}

EXT₋C int copy₋append₋items(__builtin_int_t count, void * bytes₋objects, 
 struct structa * 🅐, ALLOC alloc)
{
  if (optionally₋inflate(count*🅐->bytes₋per₋item,🅐,alloc)) { return -1; }
  for (__builtin_int_t i=0; i<count; i += 1) {
    __builtin_int_t byte₋offset = i*🅐->bytes₋per₋item;
    void * start = byte₋offset + (uint8_t *)bytes₋objects;
    if (copy₋append₋one₋object(start,🅐)) { return -2; }
  }
  return 0;
}

EXT₋C __builtin_int_t structa₋count(struct structa * 🅐)
{
  return 🅐->item₋count;
}

EXT₋C int deinit₋structa(struct structa * 🅰, FALLOW fallow)
{ __builtin_int_t idx=🅰->item₋count-1,byte₋idx₁,tile₋idx₁, 
  middle₋idx₁, byte₋idx₂,tile₋idx₂,middle₋idx₂;
again:
   if (idx < 0) { return 0; }
   byte₋idx₁ = idx*🅰->bytes₋per₋item;
   tile₋idx₁ = byte₋idx₁/🅰->bytes₋per₋tile;
   middle₋idx₁ = tile₋idx₁/8192;
   struct middle₋index * middle = 🅰->middles[middle₋idx₁];
   uint8_t * tile = middle->tilerefs[tile₋idx₁];
   idx -= 1;
   byte₋idx₂ = idx*🅰->bytes₋per₋item;
   tile₋idx₂ = byte₋idx₂/🅰->bytes₋per₋tile;
   middle₋idx₂ = tile₋idx₂/8192;
   if (tile₋idx₁ > tile₋idx₂) { fallow(tile); }
   if (middle₋idx₁ > middle₋idx₂) { fallow(middle); }
   goto again;
}


