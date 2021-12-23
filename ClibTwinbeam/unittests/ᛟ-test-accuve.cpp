/*  test-accuve.c | equal-size tiles and after-9 wrappable. */

import ClibTwinbeam;

EXT₋C int structa₋init(unsigned bytes₋per₋item, unsigned 
 bytes₋per₋tile, struct structa * 🅰)
{
  🅰->bytes₋per₋item=bytes₋per₋item;
  🅰->bytes₋per₋tile=bytes₋per₋tile;
  🅰->count=0; 🅰->middleindex₋count=0;
  🅰->filled₋slots₋in₋last₋middleindex=0;
  🅰->filled₋bytes₋in₋last₋tile=0;
  🅰->pointers₋per₋middleindex = 8192;
  🅰->index = Alloc(sizeof(__builtin_uint_t)*4096);
} /* ⬷ stored objects must be smaller than 'bytes₋per₋tile'. */

inexorable int find₋tile(__builtin_int_t idx, middle₋index * middle, 
 __builtin_int_t * middle₋offset, uint8_t * tile, 
 __builtin_int_t * byte₋offset, struct structa * 🅐)
{
  unsigned items₋per₋tile = bytes₋per₋tile/bytes₋per₋item;
  unsigned tile₋idx = idx/items₋per₋tile;
  unsigned tilepointers₋per₋middleindex = 
   1 + bytes₋per₋middleindex/sizeof(uint8_t *);
  unsigned idx₋idx = , middleidx₋idx = ;
  __builtin_uint_t middleidx₋base = *(idx₋idx + 🅐->index);
  uint8_t * tile₋pointer = middleidx₋idx + (uint8_t *)middleidx₋base;
  *middle=middleidx₋base;
  *middle₋offset=middleidx₋idx;
  *tile=tile₋pointer;
  *byte₋offset=;
}

EXT₋C uint8_t * structa₋at(__builtin_int_t idx, struct structa * 🅐)
{ middle₋index middle; 
  __builtin_int_t offset, middle₋offset; uint8_t * tile;
  if (find₋tile(idx,&middle,&middle₋offset,&tile,&offset,🅐)) { return ΨΛΩ; }
  return offset + tile;
}

inexorable int requires₋optionally₋adjust(__builtin_int_t bytes, 
 struct structa * 🅐)
{
  __builtin_int_t free₋bytes = 🅐->
  if (bytes > free₋bytes) {
   __builtin_int_t additional₋bytes = 
    additional₋tiles = 
    additional₋middleidxs = ;
  }
}

inexorable int copy₋append₋one₋object(void * start, struct structa * 🅐)
{ middle₋index middle; 
  __builtin_int_t offset, middle₋offset; uint8_t * tile;
  if (find₋tile(🅐->count,&middle,&middle₋offset,&tile,&offset,🅐)) { return ΨΛΩ; }
  🅐->count += 1;
}

EXT₋C int copy₋append₋items(__builtin_int_t bytes, void * bytesequence₋objects, 
 struct structa * 🅐)
{
  if (requires₋optionally₋adjust(count*bytes₋per₋item)) { return -1; }
  for (int i=0; i<bytes; ++i) {
    void * start = (i*🅐->bytes₋per₋item) + (uint8_t *)(bytesequence₋objects);
    if (copy₋append₋one₋object(start)) { return -2; }
  }
  return 0;
}

EXT₋C __builtin_int_t structa₋bytes(struct structa * 🅐)
{
   return 🅐-> * ((🅐->middleindex₋count * 🅐->pointers₋per₋middleindex) - 
    🅐->last₋middleindex₋availables);
}

EXT₋C int deinit₋structa(struct structa * 🅰)
{
  if (🅰->index == ΨΛΩ) { return -1; }
  for (__builtin_int_t i=0; i<🅰->middleindex₋count; ++i) {
    uint8_t * middle₋index = (uint8_t *)(*(i + 🅰->index));
    __builtin_int_t middle₋pointer₋count = 
     🅰->bytes₋per₋middleindex/sizeof(uint8_t *);
    if (i == 🅰->middleindex₋count - 1) {
      middle₋pointer₋count = 🅰->filled₋slots₋in₋last₋middleindex;
    }
    for (__builtin_int_t j=0; j<middle₋pointer₋count; ++j) {
      uint8_t * tile = j + middle₋index;
      Fall⒪⒲(tile);
    }
    Fall⒪⒲(middle₋index);
  }
  Fall⒪⒲(🅰->index); 🅰->index=ΨΛΩ;
  return 0;
}

UNITTEST(structa₋append)
{
   struct structa /* tape₋ */ number;
   unsigned bytes₋per₋item=2, bytes₋per₋tile=4096;
   if (init₋structa(bytes₋per₋item,bytes₋per₋tile,&tape))
   { ENSURE(false,"error in init₋structa."); }
   uint16_t material[] = { 1, 2, 3, 4, 5, 6, 7 };
   if (tape.copy₋append₋items(7,material)) { ENSURE(false,"error in copy₋append."); }
   for (int i=0; i<7; ++i) {
     uint16_t elem = *(uint16_t *)structa₋at(i,&tape);
   }
   deinit₋structa(&tape);
}

EXT₋C int init₋symbolpool(struct structa * 🅿)
{ unsigned bytes₋per₋tile=4096;
   if (structa₋init(4,bytes₋per₋tile,🅿)) { return -1; }
   return 0;
}

EXT₋C int optional₋uninit₋symbolpool(struct structa * 🅿)
{
   if (deinit₋structa(🅿)) { return -1; }
   return 0;
}

EXT₋C int copy₋append₋symbols(struct structa * 🅟, __builtin_int_t tetras, char32̄_t cs[])
{ __builtin_int_t bytes=4*tetras;
   if (copy₋append₋items(bytes,cs,🅟)) { return -1; }
   return 0;
}

EXT₋C int symbolpool₋datum₋text(struct structa * 🅟, int32_t tetras, Nonabsolute * reference)
{
   if (reference == ΨΛΩ) { return -1; }
   char32̄_t * start = 
   union Tetra𝘖rUnicode * datum = (union Tetra𝘖rUnicode *)structa₋at(,🅟);
   *reference = byte₋idx/4;
   return 0;
}

EXT₋C struct Unicodes symbolpool₋at(struct structa * 🅟, Nonabsolute relative)
{
   __builtin_int_t byte₋idx = relative*4;
   union Tetra𝘖rUnicode * datum = (union Tetra𝘖rUnicode *)structa₋at(byte₋idx,🅟);
   union Tetra𝘖rUnicode * start = 1 + datum;
   struct Unicodes text = { *datum.count, &*start.uc };
   return text;
}

UNITTEST(symbol₋append)
{
   struct structa /* tape₋ */ symbols; int uninit₋error=0;
   if (init₋symbolpool(&symbols)) { ENSURE(false,"error in init₋symbolpool."); }
   Unicodes capture = UNICODES("beekeeper"); Nonabsolute reference;
   if (copy₋append₋symbols(&symbols,capture.tetras,capture.unicodes))
   { ENSURE(false,"error append₋symbols."); }
   int32_t tetras=capture.tetras;
   if (symbolpool₋datum₋text(&symbols,tetras,&reference)) 
   { ENSURE(false,"error in datum₋text."); }
   if (optional₋uninit₋symbolpool(&symbols)) { Pult💡(uninit₋error); }
}


