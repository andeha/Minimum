/*  account-italian-2.c | helpers to bookkeeping functions. */

import ClibTwinbeam;

inexorable int lookup₋unicode₋to₋historypod(struct Unicodes key, 
 union historypod ** found₋entry, void * opaque)
{
   __uint128_t fineprint = FNV1b(4*key.tetras,&(key.unicodes));
   struct w₋node * node = impression₋seek(opaque,fineprint);
   **found₋entry = *((union historypod *)(node->note));
   return 0;
} /* ⬷ for uncommits and for currents. */

inexorable int include₋alt₋update₋unicode₋to₋historypod(struct Unicodes key, 
 union historypod entry, void ** opaque, ALLOC alloc)
{
   __uint128_t fineprint = FNV1b(4*key.tetras,&(key.unicodes));
   struct w₋node * node = impression₋store(*opaque,fineprint,alloc);
   node->note = alloc(sizeof(union historypod));
   *((union historypod *)(node->note)) = entry;
   if (*opaque == ΨΛΩ) { *opaque = node; }
   return 0;
}

inexorable int exists₋in₋unicode₋to₋historypod(struct Unicodes key, void * opaque)
{
   union historypod * found₋entry;
   if (lookup₋unicode₋to₋historypod(key,&found₋entry,opaque)) { return 0; }
   return found₋entry != ΨΛΩ;
}

int exists₋in₋currents(struct Unicodes key, void * currents)
{ return exists₋in₋unicode₋to₋historypod(key,currents); }
int exists₋in₋uncommits(struct Unicodes key, void * uncommits)
{ return exists₋in₋unicode₋to₋historypod(key,uncommits); }

union historypod * lookup₋in₋currents(struct Unicodes key, void * currents) {
  union historypod * found₋entry;
  if (lookup₋unicode₋to₋historypod(key,&found₋entry,currents)) { return 0; }
  return found₋entry;
}

union historypod * lookup₋in₋uncommits(struct Unicodes key, void * uncommits) {
  union historypod * found₋entry;
  if (lookup₋unicode₋to₋historypod(key,&found₋entry,uncommits)) { return 0; }
  return found₋entry;
}

int include₋in₋currents(struct Unicodes key, union historypod entry, void ** 
 currents, ALLOC alloc) { return include₋alt₋update₋unicode₋to₋historypod(
 key,entry,currents,alloc); }

int include₋in₋uncommits(struct Unicodes key, union historypod entry, void ** 
 uncommits, ALLOC alloc) { return include₋alt₋update₋unicode₋to₋historypod(
 key,entry,uncommits,alloc); }

int append₋version(struct timeserie₋version₋row entry, struct structa * 
 casette, ALLOC alloc) { return copy₋append₋items(1,&entry,casette,alloc); }

int append₋temporal(struct timeserie₋temporal₋row entry, struct structa * 
 casette, ALLOC alloc) { return copy₋append₋items(1,&entry,casette,alloc); }

int append₋event(struct timeserie₋event₋row entry, struct structa * 
 casette, ALLOC alloc) { return copy₋append₋items(1,&entry,casette,alloc); }

int append₋checkpoint(struct timeserie₋checkpoint₋row entry, struct structa * 
 casette, ALLOC alloc) { return copy₋append₋items(1,&entry,casette,alloc); }

int append₋pending₋changes(struct pending₋change entry, struct structa * 
 casette, ALLOC alloc) { return copy₋append₋items(1,&entry,casette,alloc); }

