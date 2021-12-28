/*  test-timeserie.cpp | inner code in bank. (DOES₋NOT₋REQUIRE₋LIBC⁺⁺.) */

import ClibTwinbeam;

union historypod two₋real₋addition(union historypod x₁, union historypod x₂)
{
   simd_tᵦ inner = __builtin_simd_addᵦ(x₁.two₋real,x₂.two₋real);
   union historypod sum = { .two₋real=inner };
   return sum;
}

typedef struct timeserie₋entry Entry;

void Present(Entry row)
{ int format=1; 
   double starboard=row.entry.two₋real[1], port=row.entry.two₋real[0];
   print("⬚ ",﹟s7(row.reference.count,(const /* signed */ char *)row.reference.keyputs));
   print("⬚,⬚", ﹟F(port,format), ﹟F(starboard,format));
   print(" ⬚\n",﹟S(row.key.tetras,row.key.unicodes));
}

Argᴾ₋output double₋double = ^(struct Unicodes set, void * context) { 
   union historypod * entry = (union historypod *)context;
};

typedef struct timeserie Timeserie;

UNITTEST(timeserie₋1)
{
   Timeserie serie1; version₋ts revision;
   if (timeserie₋init(&revision,101,5,&serie1)) { return; }
   
   struct Unicodes key1 = { 5, UC("intox") };
   union historypod pod1 = { .two₋real=simd_initᵦ(1.0) };
   struct 𝟽bit₋text reference1 = { 9, KEYPUTS("LNG 49º17'15'' N and LON 13º3'5'' E") };
   Entry absolute1 = { key1, pod1, reference1 };
   if (timeserie₋create(&absolute1,&serie1)) { return; }
   
   struct Unicodes key2 = { 6, UC("weight") };
   union historypod pod2 = { .two₋real=simd_initᵦ(100.0) }, after₋commit;
   struct 𝟽bit₋text reference2 = { 9, KEYPUTS("LNG 49º17'15'' N and LON 13º3'5'' E") };
   Entry relative1 = { key2, pod2, reference2 };
   if (timeserie₋delta(&relative1,&after₋commit,&serie1,two₋real₋addition)) { return; }
   
   Row₋completed completed = ^(version₋ts revison, Entry row, int * bye) { Present(row); };
   if (timeserie₋commit(&revision,completed,&serie1,two₋real₋addition)) { return; }
   
   version₋ts ordin = 102;
   struct Unicodes keys[] = { { 5, UC("intox") }, { 6, UC("weight") }, 
    { 6, UC("milage") } };
   
   state₋before(3,keys,ordin, ^(int count, Entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) { void * ctxt = (void *)&(row[i].entry);
        if (permanent[i]) { print("⬚: ⬚\n", ﹟S(row[i].key.tetras,row[i].key.unicodes), 
         ﹟λ(double₋double,ctxt)); }
      }
     },&serie1,two₋real₋addition);
   
   print("\n");
   
   state₋after(3,keys,ordin, ^(int count, Entry row[], int permanent[]) {
      for (int i=0; i<count; ++i) { void * ctxt = (void *)&(row[i].entry);
        if (permanent[i]) { print("⬚: ⬚\n", ﹟S(row[i].key.tetras,row[i].key.unicodes), 
         ﹟λ(double₋double,ctxt)); }
      }
    },&serie1,two₋real₋addition);
   
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
   
   timeserie₋uninit(&serie1);
}


