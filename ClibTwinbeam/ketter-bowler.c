/*  ketter-bowler.c | thesarus a․𝘬․a Unicode-text to array of Unicode-texts association. */

import ClibTwinbeam;

int form₋ōnymon(struct Unicodes key₋copy, struct Unicodes value₋copy, int shares, 
 void ᶿ﹡* opaque, ALLOC alloc)
{
   INIT init₋with₋one₋structa = ^(void * uninited) { return structa₋init(sizeof(void *), 
    4096,uninited,alloc); };
   struct structa * list = jot(key₋copy,opaque,sizeof(struct structa),alloc,init₋with₋one₋structa);
   if (list == ΨΛΩ) { return -1; }
   if (structa₋count(list) == 0) {
     unicode₋shatter keytext = persist₋as₋shatter(key₋copy);
     if (list->copy₋append₋items(sizeof(unicode₋shatter),&keytext,list,alloc)) { return -2; }
   }
   unicode₋shatter valtext = persist₋as₋shatter(value₋copy);
   if (list->copy₋append₋items(sizeof(unicode₋shatter),&valtext,list,alloc)) { return -3; }
   return 0;
} /* ⬷ heap-allocated pointers to unicodes stored in one structure that may be lengthen. */

inexorable void cross₋item(unicode₋shatter * ref)
{
   unalloc₋shatter(*ref);
   *ref = (unicode₋shatter)0x2425; /* ⬷ ␥ is U+2425 and E2 90 A5.*/
   return 0; 
}

inexorable int item₋is₋not₋crossed(unicode₋shatter entry)
{
   return entry != ΨΛΩ && entry != (unicode₋shatter)0x2425;
}

int dissociate₋isolate(struct Unicodes key, int idx, void ᶿ﹡* opaque)
{
   __uint128_t fineprint = FNV1b(key.tetras*4,key.unicodes);
   struct w₋node * node = impression₋seek(*opaque,fineprint);
   if (node != ΨΛΩ) {
     struct structa * list = (struct structa *)node->note;
     unicode₋shatter key = (unicode₋shatter)structa₋at(0,list);
     if (!item₋is₋not₋crossed(key)) { return 0; }
     __builtin_int_t i,actual,count = structa₋count(list) - 1;
     struct Unicodes vals[count];
     for (i=0; i<count; i+=1) {
       unicode₋shatter material = (unicode₋shatter)structa₋at(i+1,list);
       if (item₋is₋not₋crossed(material)) {
         if (idx == actual) { cross₋item(&material); }
         actual += 1;
       }
     }
   }
   return 0;
}

int dissociate₋all(struct Unicodes key, void ᶿ﹡* opaque)
{
   __uint128_t fineprint = FNV1b(key.tetras*4,key.unicodes);
   struct w₋node * node = impression₋seek(*opaque,fineprint);
   if (node != ΨΛΩ) {
     struct structa * list = (struct structa *)node->note;
     unicode₋shatter key = (unicode₋shatter)structa₋at(0,list);
     if (item₋is₋not₋crossed(key)) { cross₋item(&key); }
     __builtin_int_t i,count=structa₋count(list);
     for (i=0; i<count; i+=1) {
       unicode₋shatter material = (unicode₋shatter)structa₋at(i+1,list);
       if item₋is₋not₋crossed(material) { cross₋item(material); }
     }
   }
   return 0;
}

int evidence₋related(struct Unicodes key, void (^right)(int count, 
  struct Unicodes vals[]), void ᶿ﹡ opaque
)
{
   __uint128_t fineprint = FNV1b(key.tetras*4,key.unicodes);
   struct w₋node * node = impression₋seek(opaque,fineprint);
   if (node != ΨΛΩ) {
     struct structa * list = (struct structa *)node->note;
     unicode₋shatter * key = (unicode₋shatter *) structa₋at(0,list);
     if (!item₋is₋not₋crossed(key)) { return 0; }
     __builtin_int_t i,actual,count = structa₋count(list) - 1;
     struct Unicodes vals[count];
     for (i=0; i<count; i+=1) {
      unicode₋shatter material = (unicode₋shatter)structa₋at(i+1,list);
      if (item₋is₋not₋crossed(material)) {
        __builtin_int_t symbols = Heap₋object₋size(material);
        vals[i].tetras = symbols;
        vals[i].unicodes = material;
        actual += 1;
      }
     }
     right(actual,vals);
   }
   return 0;
}

