/*  account-italian.h | non-contractuals. (REQUIRED₋AFTER₋COMPILATION.) */

struct timeserie₋temporal₋row { struct Unicodes key; union historypod entry; 
 version₋ts from,to; };
struct timeserie₋event₋row { __builtin_int_t temporal₋idx₋first,temporal₋idx₋last; };
/* ⬷ a․𝘬․a 'rowid' and 'value' in addCheckpoint. */
struct timeserie₋version₋row { version₋ts version; __builtin_int_t event₋idx; };
struct timeserie₋checkpoint₋row { version₋ts version; void * bitmap; };
/* ⬷ structs of sizes larger than 64-bits are passed as pointers. */

struct pending₋change { enum timeserie₋operation op; 
  struct Unicodes key; union historypod entry; struct 𝟽bit₋text reference;
};


