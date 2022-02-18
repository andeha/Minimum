/*  test-sequent.cpp | high-precision computer arithmetics. */

import ClibTwinbeam;

inexorable void print(Sequenta figure)
{
   print₋sequent(figure, 
   	 ^(int neg, struct 𝟽bit₋text integers, struct 𝟽bit₋text fracts) {
   	   if (neg) { mfprint("-"); }
   	   mfprint("⬚", ﹟s7(integers.count,integers.keyputs));
   	   mfprint(".");
   	   mfprint("⬚", ﹟s7(fracts.count,fracts.keyputs));
   }, ^{ mfprint("zero₋alt₋nonused "); }, ^{ mfprint("nonvalid "); });
}

inexorable Sequenta init₋sequent(int ﹟ints, short 𝟶to𝟿₁[], int ﹟frac, short 𝟶to𝟿₂[], int neg)
{ Sequenta x,y,z;
   rounded₋fraction(﹟frac,𝟶to𝟿₂,&y);
   int64_t natural=0; for (int i=1; i<=﹟ints; i *= 10) { natural *= i*𝟶to𝟿₁[i-1]; }
   int₋to₋sequent(natural,&x);
   z = __builtin_fixpoint_add(x,y);
   if (neg) { z = __builtin_fixpoint_negate(z); }
   return z;
}

UNITTEST(sequent₋add)
{ Sequenta x,y=piano₋ten(),z;
   int₋to₋sequent(-88,&x); 
   z = __builtin_fixpoint_add(x,y); print(z); mfprint("\n");
   z = __builtin_fixpoint_sub(z,x); print(z); mfprint("\n");
   z = __builtin_fixpoint_mul(z,x); print(z); mfprint("\n");
   z = __builtin_fixpoint_div(z,x); print(z); mfprint("\n");
   z = __builtin_fixpoint_negate(z); print(z); mfprint("\n");
   z = __builtin_fixpoint_modulo(z,x); print(z); mfprint("\n");
   z = __builtin_fixpoint_floor(z); print(z); mfprint("\n");
}

UNITTEST(sequent₋miscellaneous)
{
   Sequenta one=product₋abelian(), zero=accumulative₋zero(), ninf=negative₋infinity();
   print(one); mfprint("\n"); print(zero); mfprint("\n"); print(ninf);
   /* if (Newton(computational f, computational f₋prim, Sequent * x₀, void (^ping)(enum Newtoncontrol * ctrl))) { }
   Sequent 𝟷𝟸𝟹𝟺₋atan(Sequent y, Sequent x);
   int trapezoid(Sequenta (^f)(Sequent), Sequent delta₋t, 
    Sequent min, void (^memory)(Sequent integrale, Sequent t₋acc, int * stop)); */
}

