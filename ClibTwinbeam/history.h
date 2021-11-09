/* history.h | . */

typedef struct timeserie Timeserie;
struct timeserie { struct structa pendingchanges; void * currents, 
 *noncommits; struct structa checkpoints, versions, events, temporals; 
 version₋ts version, earliest; };
enum timeserie₋operation { ts₋create, ts₋update, ts₋delta, ts₋remove };
union historypod { __uint128_t machineunsigned; simd_tᵦ two₋real; union 
 Q6463 fixed; };
typedef __builtin_int_t version₋ts;

struct timeserie₋checkpoint { version₋ts version; struct structa bitmap; };
struct timeserie₋verevtidx₋pair { version₋ts version; __builtin_int_t idx; };
struct timeserie₋event { __builtin_int_t cp₋idx,veip₋idx; };
struct timeserie₋temporal { struct Unicodes key; union historypod value; };

EXT₋C int append₋checkpoint(struct timeserie₋checkpoint last, struct structa * 🅢);
EXT₋C int append₋version(struct timeserie₋verevtidx₋pair last, struct structa * 🅢);
EXT₋C int append₋event(struct timeserie₋event last, struct structa * 🅢);
EXT₋C int append₋temporal(struct timeserie₋temporal last, struct structa * 🅢);

EXT₋C int timeserie₋init(version₋ts * revision, struct timeserie * 🆃);
EXT₋C int timeserie₋uninit(struct timeserie * 🆃);
EXT₋C int timeserie₋create(struct Unicodes key, union historypod value, struct
 𝟽bit₋text valueId, struct timeserie * 🅣);
EXT₋C int timeserie₋update(struct Unicodes key, union historypod value, struct 
 𝟽bit₋text valueId, struct timeserie * 🅣);
EXT₋C int timeserie₋delta(struct Unicodes key, union historypod value, struct 
 𝟽bit₋text valueId, union historypod * relative, struct timeserie * 🅣);
EXT₋C int timeserie₋remove(struct Unicodes key, struct timeserie * 🅣);
EXT₋C int timeserie₋commit(version₋ts * revision, void (^nonePossiblyMany)(
 struct 𝟽bit₋text ref, union historypod value, version₋ts revision, int * bye), 
 struct timeserie * 🅣);
EXT₋C void timeserie₋rollback(struct timeserie * 🅣);
EXT₋C int timeserie₋uumph(Chronology::relative latency, Chronology::instant 
 focal, void (^delta₋sew)(union historypod estimate, Chronology::instant t₋actu, 
 struct timeserie * answer, Chronology::relative * nextOrΨΛΩ₋to₋stop), 
 struct timeserie * 🅣);
EXT₋C Opt<version₋ts> timeserie₋first(struct timeserie * 🅣);
EXT₋C Opt<version₋ts> timeserie₋last(struct timeserie * 🅣);
EXT₋C Opt<version₋ts> timeserie₋end(struct timeserie * 🅣);
EXT₋C void state₋before(int count, struct Unicodes keys[], version₋ts ordin, void 
 (eventually)(struct Unicodes key[], struct timeserie value[], int permanent), 
 struct timeserie * 🅣);
EXT₋C void state₋after(int count, struct Unicodes keys[], version₋ts ordin, void 
 (^eventually)(struct Unicodes key[], struct timeserie value[], int permanent), 
 struct timeserie * 🅣);
