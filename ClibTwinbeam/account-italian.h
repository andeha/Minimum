/*  account-italian.h | non-contractuals. (REQUIRED₋AFTER₋COMPILATION.) */

struct timeserie₋temporal₋row {
 struct Unicodes key; union historypod entry; version₋ts from,to; 
};

struct timeserie₋event₋row {
 __builtin_int_t temporal₋idx₋first,temporal₋idx₋last;
};
/* ⬷ a․𝘬․a 'rowid' and 'value' in addCheckpoint. */
struct timeserie₋version₋row { version₋ts version; __builtin_int_t event₋idx; };
struct timeserie₋checkpoint₋row { version₋ts version; void * bitmap; };
/* ⬷ structs of sizes larger than 64-bits are passed as pointers. */

struct pending₋change { enum timeserie₋operation op; 
  struct Unicodes key; union historypod entry; 
  struct 𝟽bit₋text reference;
};

#define versions₋count structa₋count
#define events₋count structa₋count
#define temporals₋count structa₋count
#define pending₋changes₋count structa₋count
#define checkpoints₋count structa₋count

int append₋version(struct timeserie₋version₋row entry, struct structa * casette);
int append₋temporal(struct timeserie₋temporal₋row entry, struct structa * casette);
int append₋event(struct timeserie₋event₋row entry, struct structa * casette);
int append₋checkpoint(struct timeserie₋checkpoint₋row entry, struct structa * casette);
int append₋pending₋changes(struct pending₋change entry, struct structa * casette);

#define events₋at (struct timeserie₋event₋row *)structa₋at
#define pending₋changes₋at (struct pending₋change *)structa₋at
#define versions₋at (struct timeserie₋version₋row *)structa₋at

/* structures are normally passed by pushing the values of the structure on
 the stack. */

/* structures are normally returned by arranging for the caller to pass the
 address of a memory area as a hidden first argument. The function then 
 stores the return value into that memory area. */

