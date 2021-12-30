/* 􀈪 decalogue.cpp | facts examining the cross. (DO-NOT-PUBLISH) */

import ClibTwinbeam;
import Mapfile;

EXT₋C void * Heap₋alloc(__builtin_int_t bytes) { return malloc(bytes); }

EXT₋C __builtin_int_t Heap₋object₋size(void * p) { return malloc_size(p); }

EXT₋C void Heap₋unalloc(void * p) { free(p); }

EXT₋C void * Heap₋realloc(void * p, __builtin_int_t to₋bytes) { return realloc(p,to₋bytes); }

/* EXT₋C void * Heap₋realloc₂(void * p, __builtin_int_t to₋bytes)
{
  size_t old_bytes = malloc_size(p);
  uint8_t * new_words = (uint8_t *)malloc(to₋bytes);
  Copy8Memory((ByteAlignedRef)new_words, (ByteAlignedRef)p, old_bytes);
  Heap₋unalloc(p);
  return new_words;
} */

EXT₋C void * Heap₋valloc(__builtin_int_t bytes) { return valloc(bytes); }

FOCAL
int
Acquire𝟷ᵈ(__builtin_int_t ﹟, /* ⬷ a․𝘬․a '#shatters', '﹟skeletons' and '﹟turnstiles'. */
  𝟺kbframes& one₋set, void (^every)(uint8_t * 𝟸ⁿ₋frame, bool& stop)
) /* ⬷ given a transactional memory, reconsider acquire with and without rollback. */
{  __builtin_int_t 🥈 Bits=Wordbytes<<3;
   __builtin_int_t Idxs=(one₋set.page₋count/Wordbytes)>>3;
     if (﹟ <= 0) { return -1; } bool stop=false;
     for (int i=0; i<Idxs; i++) {
again:
       __builtin_int_t occupied = ~(one₋set.idx₋avails[i]);
       if (occupied == TriboolUnknown) { continue; }
#if defined __mips__ || defined __armv6__ || defined espressif
       __builtin_int_t onesUntilZero = __builtin_ctz(~occupied);
#elif defined __x86_64__ || defined __armv8a__
       __builtin_int_t onesUntilZero = __builtin_ctzll(~occupied);
#endif
       one₋set.idx₋avails[i] ^= 1<<onesUntilZero; /* ⬷ see note at --<Additions.h>{Bitsetˢᵘᵖ} for an 
 alternative interpretation of matters. */
       __builtin_int_t byteOffset = Syspagesize()*(Bits*i + onesUntilZero);
       every((uint8_t *)one₋set.pages₋base+byteOffset, stop);
       if (stop) { return -3; }
       if (--﹟ == 0) { return 0; } else { goto again; }
    }
    return -2;
} /* ⬷ similar to 'new' and 'malloc' but returns multiple same-sized and non-
  consecutive memory areas. */

FOCAL
int
Release𝟷ᵈ(void * 𝟸ⁿ₋frame, 𝟺kbframes& one₋set, bool secure)
{  __builtin_int_t Idxs=(one₋set.page₋count/Wordbytes)>>3, 
    ᵇoffset = 1 + (uint8_t *)(𝟸ⁿ₋frame)-(uint8_t *)one₋set.pages₋base, 
       ᵚidx = (__builtin_int_t)Frame(ᵇoffset,8*Wordbytes) - 1, 
       bitᵚ = ᵇoffset - ᵚidx*Wordbytes;
    __builtin_uint_t toggle = 0b1<<bitᵚ;
    if (one₋set.idx₋avails[ᵚidx] & toggle) { return -2; }
    one₋set.idx₋avails[ᵚidx] ^= toggle;
    if (secure) { Overwrite8Memory((ByteAlignedRef)𝟸ⁿ₋frame, 0x0, Syspagesize()); }
    return 0; /* See also --<Virtual.cxx>{Forget} for a frame-granular overwrite method. */
} /* ⬷ similar to 'Fallow' and 'free' but assumes same-sized areas. */

#pragma mark - grips for one realization:

void intel₋Reservoir(unsigned expeditionary, 𝟺kbframes * one₋set, 
 __builtin_int_t * pages₋in₋expedition)
{ 
   void * start = mmap(0, 4*1024*1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
}

void mips₋mzda₋Reservoir(unsigned expeditionary, 𝟺kbframes * one₋set, 
 __builtin_int_t * pages₋in₋expedition) { }

/* ⬷ defined in --<llvm-rt3.cpp>. */

int CoalescingAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
    struct 𝟺kbframes one₋set; __builtin_int_t pages₋in₋expedition;
#if !defined(__mips__)
    intel₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#else
    mips₋mzda₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#endif
    auto rollback = ^(__builtin_int_t count, void * frames[], struct 𝟺kbframes& one₋set) {
      for (__builtin_int_t i=0; i<count; ++i) {
        if (Release𝟷ᵈ(frames[i], one₋set, false)) { return -1; }
      } return 0;
    }; /* <- int. */
    __builtin_uint_t * frms = (__builtin_uint_t *)𝟺kbframes; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __builtin_int_t brk=0;
    if (Acquire𝟷ᵈ(﹟, one₋set, ^(uint8_t * 𝟸ⁿ₋frame, bool& stop) { 
      *(frms + brk++) = (__builtin_uint_t)𝟸ⁿ₋frame;
    })) { if (rollback(brk,𝟺kbframes,one₋set)) { return -2; } return -1; }
    return 0;
} /* ⬷ a․𝘬․a Wholly₋coalescing₋acquire and coalesce₋rollback₋acquire. */

int 🄕allo⒲(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
    struct 𝟺kbframes one₋set; __builtin_int_t pages₋in₋expedition;
#if !defined(__mips__)
    intel₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#else
    mips₋mzda₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#endif
    for (__builtin_int_t i=0; i<﹟; i++) {
      if (Release𝟷ᵈ(𝟺kbframes[i],one₋set,false)) { return -(i+1); }
    }
    return 0;
}

int ContiguousAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
   struct 𝟺kbframes one₋set; __builtin_int_t pages₋in₋expedition;
#if !defined(__mips__)
   intel₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#else
   mips₋mzda₋Reservoir(expeditionary,&one₋set,&pages₋in₋expedition);
#endif
   if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { return -1; }
   if (﹟ >= 2) { for (__builtin_int_t i=0; i<﹟; ++i) { 
     uint8_t * next = (uint8_t *)𝟺kbframes[i+1], *present = (uint8_t *)𝟺kbframes[i];
     if (next - present != 4096) { return -2; }
   } }
   return 0;
}

void Init₋frames(unsigned count, unsigned expeditionaries[])
{
   struct 𝟺kbframes one₋set; __builtin_int_t pages₋in₋expedition;
   for (unsigned i=0; i<count; ++i) {
#if !defined(__mips__)
     intel₋Reservoir(i,&one₋set,&pages₋in₋expedition);
#else
     mips₋mzda₋Reservoir(i,&one₋set,&pages₋in₋expedition);
#endif
     __builtin_int_t Idxs=(one₋set.page₋count/Wordbytes)>>3;
     for (__builtin_int_t i=0; i<Idxs; ++i) { one₋set.idx₋avails[i]=~0x0; }
   }
}


 
 
