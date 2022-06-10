/* 􀴩 arrange-lock.c | blue, white and something to keep. */

import ClibTwinbeam;

FOCAL
EXT₋C
int
#if defined __x86_64__
__attribute__ ((target("rtm")))
#elif defined __arm64__
__attribute__ ((target("tme")))
#endif
OptimisticSwap(
  __builtin_int_t * p₁, __builtin_int_t * p₂,
  enum Impediment it
) TROKADERO SELDOM
{
#if defined __arm64__
   uint64_t cause = __builtin_arm_tstart();
   if (cause) { return -1; }
#elif defined __x86_64__
   unsigned status = __builtin_ia32_xbegin();
#define _XBEGIN_STARTED (~0u)
   if (status != _XBEGIN_STARTED) { return -1; }
#elif defined Kirkbridge
   uint32_t start = U₋begin();
#endif
   if (it == MustBeOrdered && *p₁ < *p₂) { return -1; }
   *p₁ = *p₁ ^ *p₂;
   *p₂ = *p₁ ^ *p₂;
   *p₁ = *p₁ ^ *p₂;
   if (it == MustBeOrdered && *p₁ > *p₂) {
#if defined __arm64__
    __builtin_arm_tcancel(0xfd); /* CANCELLATION₋REASON 0x8000u 0x7fffu */
#elif defined __x86_64__
    __builtin_ia32_xabort(0xfd);
#elif defined Kirkbridge
    U₋err();
#endif
     return -1;
   }
#if defined __arm64__
   __builtin_arm_tcommit();
#elif defined __x86_64__
   __builtin_ia32_xend(); /* ⬷ see [Twinbeam]--<Source>--<System.cpp>. */
#elif defined Kirkbridge
   U₋forward();
#endif
   return 0;
}

EXT₋C int momentary₋always₋swap(struct Peekey * p) LEAF TROKADERO SELDOM
{
  /* return __cxa_guard_release(p); */
  return OptimisticSwap(&p->board₁, &p->palm₂, JustSwap);
}

EXT₋C int momentary₋swap₋if₋decreased(struct Peekey * p) TROKADERO LEAF SELDOM
{
  /* return __cxa_guard_acquire(p); */
  return OptimisticSwap(&p->board₁, &p->palm₂, MustBeOrdered);
}

/* namespace __cxxabiv1 { */
EXT₋C int __cxa_guard_acquire(__builtin_uint_t * p) {
  __builtin_uint_t expected[1] = { 0 }, desired[1] = { 1 };
  const int relaxed=0;
  int success_order=relaxed, failure_order=relaxed;
  bool locked = __atomic_compare_exchange(p, expected, desired, 0, 
   success_order, failure_order);
  return locked; }
EXT₋C int __cxa_guard_release(__builtin_uint_t * p) {
  __builtin_uint_t desired[1] = { 0 }, expected[1] = { 1 };
  const int relaxed=0;
  int success_order=relaxed, failure_order=relaxed;
  bool unlocked = __atomic_compare_exchange(p, expected, desired, 0, 
   success_order, failure_order);
  return unlocked;
}
EXT₋C void __cxa_guard_abort(__builtin_uint_t * p) {
  __builtin_uint_t desired[1] = { 0 };
  const int relaxed=0;
  int ordering=relaxed;
  __atomic_store(p,desired,ordering);
}
/* } / * ⬷ a․𝘬․a coroutine and async 'yield'. */

