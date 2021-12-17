/*  ᛟ-test-timeserie.cpp | inner code in bank. (DOES₋NOT₋REQUIRE₋LIBC⁺⁺.) */

import ClibTwinbeam;

union historypod two₋real₋addition(union historypod x₁, union historypod x₂)
{
   simd_tᵦ onesum = __builtin_simd_addᵦ(x₁.two₋real,x₂.two₋real);
   union historypod sum = { .two₋real=onesum };
   return sum;
}

UNITTEST(Timeserie₋1)
{
   struct timeserie serie1;
   version₋ts revision;
   if (timeserie₋init(&revision,101,5,&serie1)) { return; }
   
   struct Unicodes key1 = { 4, U"abcd" };
   union historypod pod1 = { .two₋real=simd_initᵦ(1.0) };
   struct 𝟽bit₋text₋reference reference1 = { 9, "123456789" };
   struct timeserie₋entry entry₋absolute1 = { key1, pod1, reference1 };
   if (timeserie₋create(&entry₋absolute1,&timeserie1)) { return; }
   
   struct Unicode key2 = { 5, U"dcba" };
   union historypod pod2 = { .two₋real=simd_tᵦ(100.0) }, after₋commit;
   struct 𝟽bit₋text₋reference reference2 = { 9, "987654321" };
   struct timeserie₋entry entry₋relative1 = { key2, pod2, reference2 };
   if (timeserie₋delta(&entry₋relative1,&after₋commit,&serie1,two₋real₋addition)) { return; }
   
   if (timeserie₋commit(&revision,entry₋row,&serie1,two₋real₋addition)) { return; }
   
   version₋ts ordin = 102;
   struct Unicodes interesting₋keys = { { 2, U"12" }, { 2, U"ab" }, { 5, U"bcdef" } };
   state₋before(3,interesting₋keys,ordin, 
     ^(int count, struct Unicodes key[], struct timeserie₋entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) {
        if (permanent[i]) { print("⬚: ⬚", ﹟S₁(key.tetras,key.unicodes), 
         ﹟λ(Argᴾ₋output scalar, void * context)); }
      }
     }, &serie1,two₋real₋addition);
   print("\n"); state₋after(3,interesting₋keys,ordin, 
    ^(int count, struct Unicodes key[], struct timeserie₋entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) {
        if (permanent[i]) { print("⬚: ⬚", ﹟S₁(key.tetras,key.unicodes), 
         ﹟λ(Argᴾ₋output scalar, void * context)); }
      }
    }, &serie1,two₋real₋addition);
   
   unsigned columns=3;
   Present₋timeserie₋overview(columns, &serie1, 
    ^(char8₋t * u8s, __builtin_int_t bytes) {
      print("⬚", ﹟s8(u8s));
    }
   );
   
   int incl₋tables=1;
   Present₋timeserie₋details(&serie1,incl₋tables, 
    ^(char8₋t * u8s, __builtin_int_t bytes) {
      print("⬚", ﹟s8(u8s));
    }
   );
   
   timeserie₋uninit(serie1);
}


