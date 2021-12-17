/*  ᛟ-test-timeserie.cpp | inner code in bank. (DOES₋NOT₋REQUIRE₋LIBC⁺⁺.) */

import ClibTwinbeam;

union historypod two₋real₋addition(union historypod x₁, union historypod x₂)
{
   simd_tᵦ inner = __builtin_simd_addᵦ(x₁.two₋real,x₂.two₋real);
   union historypod sum = { .two₋real=inner };
   return sum;
}

UNITTEST(Timeserie₋1)
{
   struct timeserie serie1;
   version₋ts revision;
   if (timeserie₋init(&revision,101,5,&serie1)) { return; }
   
   struct Unicodes key1 = { 5, U"intox" };
   union historypod pod1 = { .two₋real=simd_initᵦ(1.0) };
   struct 𝟽bit₋text₋reference reference1 = { 9, "LNG 49º17'15'' N and LON 13º3'5'' E" };
   struct timeserie₋entry entry₋absolute1 = { key1, pod1, reference1 };
   if (timeserie₋create(&entry₋absolute1,&timeserie1)) { return; }
   
   struct Unicode key2 = { 6, U"weight" };
   union historypod pod2 = { .two₋real=simd_tᵦ(100.0) }, after₋commit;
   struct 𝟽bit₋text₋reference reference2 = { 9, "LNG 49º17'15'' N and LON 13º3'5'' E" };
   struct timeserie₋entry entry₋relative1 = { key2, pod2, reference2 };
   if (timeserie₋delta(&entry₋relative1,&after₋commit,&serie1,two₋real₋addition)) { return; }
   
   if (timeserie₋commit(&revision,entry₋row,&serie1,two₋real₋addition)) { return; }
   
   version₋ts ordin = 102;
   struct Unicodes interesting₋keys = { { 5, U"intox" }, { 6, U"weight" }, { 6, U"milage" } };
   state₋before(3,interesting₋keys,ordin, 
     ^(int count, struct timeserie₋entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) {
        if (permanent[i]) { print("⬚: ⬚\n", ﹟S₁(row.key.tetras,row.key.unicodes), 
         ﹟λ(Argᴾ₋output scalar, void * context)); }
      }
     }, &serie1,two₋real₋addition);
   print("\n"); state₋after(3,interesting₋keys,ordin, 
    ^(int count, struct timeserie₋entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) {
        if (permanent[i]) { print("⬚: ⬚\n", ﹟S₁(row.key.tetras,row.key.unicodes), 
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
   Present₋timeserie₋transacts(&serie1,incl₋tables, 
    ^(char8₋t * u8s, __builtin_int_t bytes) {
      print("⬚", ﹟s8(u8s));
    }
   );
   
   timeserie₋uninit(serie1);
}


