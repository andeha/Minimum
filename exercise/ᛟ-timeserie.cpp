/*  test-timeserie.cpp | code to for instance finance. (DOES₋NOT₋REQUIRE₋LIBC⁺⁺.) */

import ClibTwinbeam;

typedef struct timeserie Timeserie;
union historypod piecewise₋addition(union historypod x₁, union historypod x₂);
void Present(struct timeserie₋entry row);
void Print(int count, struct timeserie₋entry row[], int permanent[]);
void Output(int count, union historypod val[], struct Unicodes key[]);
typedef void (^Out)(char8₋t * u8s, __builtin_int_t bytes);
EXT₋C void Present₋timeserie₋intestinals(struct timeserie * 🅙, Out out);

UNITTEST(timeserie₋1)
{
   Timeserie serie1; version₋ts revision;
   if (timeserie₋init(&revision,101,5,&serie1)) { return; }
   
   struct Unicodes key1 = UC("intox");
   union historypod pod1 = { .tworeal=simd_initᵦ(1.0) };
   struct 𝟽bit₋text referen1 = { 9, KEYPUTS("LNG 49º17'15'' N and LON 13º3'5'' E") };
   struct timeserie₋entry absolute1 = { key1, pod1, referen1 };
   if (timeserie₋create(&absolute1,&serie1)) { return; }
   
   struct Unicodes key2 = UC("weight");
   union historypod pod2 = { .tworeal=simd_initᵦ(100.0) }, after₋commit;
   struct 𝟽bit₋text referen2 = { 9, KEYPUTS("LNG 49º17'15'' N and LON 13º3'5'' E") };
   struct timeserie₋entry relative1 = { key2, pod2, referen2 };
   if (timeserie₋delta(&relative1,&after₋commit,&serie1,piecewise₋addition)) { return; }
   
   Row₋completed completed = ^(version₋ts revision, Entry row, int * bye) { Present(row); };
   if (timeserie₋commit(&revision,completed,&serie1,piecewise₋addition)) { return; }
   
   version₋ts ordin = 102;
   struct Unicodes keys[] = { key1, key2, { 6, UNICODES("milage") } };
   
   Outrow outrow = ^(int count, Entry row[], int permanent[]) {
    Print(count,row,permanent); };
   
   Outpod outpod =  ^(int count, union historypod artstate[], 
    struct Unicodes key[]) { Output(count,artstate,key); };
   
   state₋before(3,keys,ordin,outpod,&serie1);
   
   print("\n");
   
   state₋after(3,keys,ordin,outpod,&serie1);
   
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { print("⬚", ﹟s8(u8s)); };
   
   Present₋timeserie₋intestinals(&serie1,out);
   
   Present₋timeserie₋transacts(0,100,&serie1,outrow);
   
   Present₋timeserie₋overview(&serie1,outpod);
   
   timeserie₋uninit(&serie1);
}

union historypod piecewise₋addition(union historypod x₁, union historypod x₂)
{
   simd_tᵦ inner = __builtin_simd_addᵦ(x₁.tworeal,x₂.tworeal);
   union historypod sum = { .tworeal=inner };
   return sum;
}

void Present(struct timeserie₋entry row)
{ int format=1;
   double starboard=row.entry.tworeal[1], port=row.entry.tworeal[0];
   print("⬚ ",﹟s7(row.reference.count,row.reference.keyputs));
   print("⬚,⬚", ﹟F(port,format), ﹟F(starboard,format));
   print(" ⬚\n",﹟S(row.key.tetras,row.key.unicodes));
}

void double₋double(struct Unicodes set, void * context) {
  union historypod * entry = (union historypod *)context;
}

void Print(int count, struct timeserie₋entry row[], int permanent[])
{
  for (int i=0; i<count; i+=1) {
    if (permanent[i]) {
      Argᴾ key = ﹟S(row[i].key.tetras,row[i].key.unicodes);
      void * ctxt = (void *)&(row[i].entry);
      Argᴾ val = ﹟λ₋p(double₋double,ctxt);
      print("⬚: ⬚\n",key,val); }
  }
}

void Output(int count, union historypod val[], struct Unicodes key[])
{
  /* print("⬚ ⬚ ⬚\n", ﹟s8(u8s)); */
}
