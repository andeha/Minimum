/*  built-altern.c | two-sided, builtin and manually tuned. */

import ClibTwinbeam;
import Mapfile;

EXT₋C void * Alloc(__builtin_int_t bytes) { return Heap₋alloc(bytes); }
EXT₋C void Fallow(void * p) { Heap₋unalloc(p); }
EXT₋C void * Realloc(void * p, __builtin_int_t to₋bytes) { return Heap₋realloc(p,to₋bytes); }

EXT₋C void * Heap₋alloc(__builtin_int_t bytes) { return malloc(bytes); }
EXT₋C __builtin_int_t Heap₋object₋size(void * p) { return malloc_size(p); }
EXT₋C void Heap₋unalloc(void * p) { free(p); }

/* #define EXISTS₋REALLOC */

EXT₋C void * Heap₋realloc(void * p, __builtin_int_t to₋bytes)
{
#if defined EXISTS₋REALLOC
   return realloc(p,to₋bytes);
#else
  size_t old₋bytes = malloc_size(p);
  uint8_t * new₋words = (uint8_t *)malloc(to₋bytes);
  Copy8Memory((ByteAlignedRef)new₋words, (ByteAlignedRef)p, old₋bytes);
  Heap₋unalloc(p);
  return new₋words;
#endif
}

EXT₋C void * Heap₋valloc(__builtin_int_t bytes) { return valloc(bytes); }

/* 
 *  and fast-checkout of equal-sized frames when the number of 
 *  frames required are á-priori known. (image-tiles and scrolling)
 *  
 *  similar to 'new' and 'malloc' but returns multiple same-sized 
 *  and non-consecutive memory areas a․𝘬․a 'shatters', 'skeletons' 
 *  and 'turnstiles'. The 'malloc' function is best-fit in 
 *  some implementation.
 */

inexorable __builtin_int_t Wordbytes() { return sizeof(__builtin_uint_t); }
inexorable __builtin_int_t Syspagesize() { return 4096; }

FOCAL
int
Acquire𝟷ᵈ(__builtin_int_t ﹟, struct 𝟺kbframes * one₋set, 
 void (^every)(uint8_t * 𝟸ⁿ₋frame, int * stop)
)
{ __builtin_int_t Bits=Wordbytes()<<3, Idxs=(one₋set->page₋count/Wordbytes())>>3, occupied;
    if (﹟ <= 0) { return -1; } int stop=false;
    for (int i=0; i<Idxs; i++) {
again:
      occupied = ~(one₋set->idx₋avails[i]);
      if (occupied == TriboolUnknown) { continue; }
#if defined __mips__ || defined __armv6__ || defined espressif
      __builtin_int_t onesUntilZero = __builtin_ctz(~occupied);
#elif defined __x86_64__ || defined __arm64__ || defined Kirkbridge
      __builtin_int_t onesUntilZero = __builtin_ctzll(~occupied);
#endif
      one₋set->idx₋avails[i] ^= 1<<onesUntilZero;
      __builtin_int_t byteOffset = Syspagesize()*(Bits*i + onesUntilZero);
      every((uint8_t *)one₋set->pages₋base+byteOffset,&stop);
      if (stop) { return -3; }
      if (--﹟ == 0) { return 0; } else { goto again; }
    }
    return -2;
} /* ⬷ given a transactional memory, reconsider Acquire𝟷ᵈ above with and without rollback. */

__builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize)
{ return (__builtin_int_t)((size + framesize - 1) & ~(framesize - 1)); }
/* ⬷ may be evaluated at compile-time a․𝘬․a 'constexpr'. */

FOCAL
int
Release𝟷ᵈ(void * 𝟸ⁿ₋frame, struct 𝟺kbframes * one₋set, int secure)
{  __builtin_int_t Idxs=(one₋set->page₋count/Wordbytes())>>3, 
   ᵇoffset = 1 + (uint8_t *)(𝟸ⁿ₋frame)-(uint8_t *)one₋set->pages₋base, 
      ᵚidx = (__builtin_int_t)Frame(ᵇoffset,8*Wordbytes()) - 1, 
      bitᵚ = ᵇoffset - ᵚidx*Wordbytes();
   __builtin_uint_t toggle = 0b1<<bitᵚ;
   if (one₋set->idx₋avails[ᵚidx] & toggle) { return -2; }
   one₋set->idx₋avails[ᵚidx] ^= toggle;
   if (secure) { Overwrite8Memory((ByteAlignedRef)𝟸ⁿ₋frame, 0x0, Syspagesize()); }
   return 0;
} /* ⬷ similar to 'Fallow' and 'free' but assumes same-sized areas. */

void Reservoir(unsigned expeditionary, struct 𝟺kbframes * one₋set, 
 __builtin_uint_t * pages₋in₋expedition)
{
#if defined __x86_64__ || __arm64__ || Kirkbridge
   void * start = mmap(0, 4*1024*1024, PROT_READ | PROT_WRITE, 
    MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#elif defined __mips__ || defined __armv6__ || defined espressif
   *pages₋in₋expedition = (__builtin_uint_t *)0xcafebabe;
#elif defined Kirkbridge
   *pages₋in₋expedition = valloc(); /* and the other method we not remember today. */
#endif
}

int CoalescingAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{ struct 𝟺kbframes one₋set; __builtin_uint_t pages₋in₋expedition;
   Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
   typedef int (^Rollback)(__builtin_int_t, void **,struct 𝟺kbframes *);
   Rollback rollback = ^(__builtin_int_t count, void * frames[], struct 𝟺kbframes * one₋set) {
     for (__builtin_int_t i=0; i<count; ++i) {
       if (Release𝟷ᵈ(frames[i],one₋set,false)) { return -1; }
     } return 0;
   };
   __builtin_uint_t * frms = (__builtin_uint_t *)𝟺kbframes; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __builtin_int_t brk=0;
   if (Acquire𝟷ᵈ(﹟, &one₋set, ^(uint8_t * 𝟸ⁿ₋frame, int * stop) { 
     *(frms + brk++) = (__builtin_uint_t)𝟸ⁿ₋frame;
   })) { if (rollback(brk,𝟺kbframes,&one₋set)) { return -2; } return -1; }
   return 0;
} /* ⬷ a․𝘬․a wholly₋coalescing₋acquire and coalesce₋rollback₋acquire. */

 int ContiguousAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{ struct 𝟺kbframes one₋set; __builtin_uint_t pages₋in₋expedition;
   Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
   if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { return -1; }
   if (﹟ >= 2) { for (__builtin_int_t i=0; i<﹟; ++i) {
     uint8_t * next = (uint8_t *)𝟺kbframes[i+1], *present = (uint8_t *)𝟺kbframes[i];
     if (next - present != 4096) { return -2; }
   } }
   return 0;
}

int 🄕allo⒲(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{ struct 𝟺kbframes one₋set; __builtin_uint_t pages₋in₋expedition;
   Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
   for (__builtin_int_t i=0; i<﹟; ++i) {
     if (Release𝟷ᵈ(𝟺kbframes[i],&one₋set,false)) { return -(i+1); }
   }
   return 0;
}

void Init₋frames(unsigned count, unsigned expeditionaries[])
{ struct 𝟺kbframes one₋set; __builtin_uint_t pages₋in₋expedition;
   for (unsigned i=0; i<count; ++i) {
     Reservoir(i,&one₋set,&pages₋in₋expedition);
     __builtin_int_t Idxs=(one₋set.page₋count/Wordbytes())>>3;
     for (__builtin_int_t i=0; i<Idxs; ++i) { one₋set.idx₋avails[i]=~0x0; }
   }
}


