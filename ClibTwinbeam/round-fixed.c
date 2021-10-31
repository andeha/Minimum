/* 􀘽 round-fixed.c | base-2 and neither Ieee754 nor Ieee 754-2008. */

import ClibTwinbeam;

#define 𝟶ᐧ𝟶 { .detail.frac=0, 1 }
#define 𝟷𝟶ᐧ𝟶 { .detail.frac = (__int128_t)0x00000110 | 0x00000000, 1 }
#define 𝟷ᐧ𝟶 { .detail.frac = (__int128_t)0x00000000<<64 | 0x80000000, 1 }
#define 𝟸ᐧ𝟶 { .detail.frac = (__int128_t)0x00000001<<64 | 0x00000000, 1 }
#define ₋𝟷ᐧ𝟶 { .detail.frac = (__int128_t)0xFFFFFFFF<<64 | 0x80000000, 1 }

void int₋to₋sequent(int64_t ℤ, struct sequent * ℝ)
{ int neg=0;
   if (ℤ < 0) { ℤ = -ℤ; neg = 1; }
   __uint128_t shift = ℤ; shift <<= 64;
   if (neg) { shift = ~shift; shift += 1; }
   /* ⬷ twos-complement above. */
   ℝ->detail.bits = shift;
   if (neg) { ℝ->detail.frac = -ℝ->detail.frac; }
}

void rounded₋fraction(int count₋upto𝟼𝟺, short 𝟶to𝟿s[], struct sequent * ℝ)
{ const struct sequent two=𝟸ᐧ𝟶, ten=𝟷𝟶ᐧ𝟶, one=𝟷ᐧ𝟶;
   struct sequent digit₋in₋text, product, sum, quotient, 
    a=accumulative₋zero(); int64_t down₋digit;
   for (int k=count₋upto𝟼𝟺-1; k>=0; --k) {
     down₋digit = 𝟶to𝟿s[k];
     int₋to₋sequent(down₋digit,&digit₋in₋text);
     product = mult_sequent(digit₋in₋text,two);
     sum = add_sequent(a,product);
     quotient = div_sequent(sum,ten,true);
     a = quotient; /* ⬷ a = (a + digits₁₀[k] * two) / 10 */
   }
   *ℝ = div_sequent(add_sequent(a,one),two,true); /* ⬷ (a + 1) div 2 */
} /* ⬷ 𝟶to𝟿s contains decimal fractions .d₀d₁..dk₋1. */

struct sequent add_sequent(struct sequent x₁, struct sequent x₂)
{
  struct sequent sum = { .detail.frac = x₁.detail.frac + x₂.detail.frac, .valid=1 };
  return sum;
}

struct sequent minus_sequent(struct sequent x₁, struct sequent x₂)
{
  struct sequent diff = { .detail.frac = x₁.detail.frac - x₂.detail.frac , .valid=1 };
  return diff;
}

void multiply(__uint128_t x₁, __uint128_t x₂, __uint128_t * std, uint64_t * int₋hi, uint64_t * hi₋prec)
{
   /* __uint256_t sum₋times₋2¹²⁶ = x₁ * x₂;
   *std = (__uint128_t)(sum₋times₋2¹²⁶>>63);
   *int₋hi=0;
   *hi₋prec=0; */
}
/*__uint128_t int₋mask = (__uint128_t)0xFFFFFFFF<<64 | 0x80000000; */
/* __uint128_t fract₋mask = 0x7fffffff; */

struct sequent mult_sequent(struct sequent x₁, struct sequent x₂)
{ int lneg=0, rneg=0; __uint128_t std; uint64_t int₋hi, hi₋prec; struct sequent y;
   if (x₁.detail.frac < 0) { lneg = 1; x₁.detail.frac = -x₁.detail.frac; }
   if (x₂.detail.frac < 0) { rneg = 1; x₂.detail.frac = -x₂.detail.frac; }
   multiply(x₁.detail.bits,x₂.detail.bits,&std,&int₋hi,&hi₋prec);
   if (lneg ^ rneg) { std = -std; }
   y.detail.bits = std;
   y.valid = 1;
  return y;
}

struct sequent div_sequent(struct sequent x₁, struct sequent x₂, int integer₋division)
{ struct sequent x₀=x₁, x₃=reciproc_sequent(x₁), y=mult_sequent(x₃,x₂);
  if (integer₋division) { y = sequent₋floor(y); } /* ⬷ not equal to Pascals definition. */
  return y;
}

struct sequent product₋abelian() { const struct sequent one = 𝟷ᐧ𝟶; return one; }
struct sequent accumulative₋zero() { const struct sequent zero = 𝟶ᐧ𝟶; return zero; }
struct sequent piano₋ten() { const struct sequent ten = 𝟷𝟶ᐧ𝟶; return ten; }
struct sequent negative₋infinity() {
  struct sequent y = accumulative₋zero();
  y.valid = 0; return y; }

struct sequent sequent₋floor(struct sequent x)
{ int neg=0; const struct sequent zero=𝟶ᐧ𝟶;
   if (x.detail.frac < zero.detail.frac) { x = operator_minus(x); neg=1; }
   __uint128_t const mask = (__int128_t)0xFFFFFFFF<<64 | 0x80000000;
   __uint128_t unmasked = x.detail.bits & mask;
   struct sequent y = { .detail.bits = unmasked, 1 };
   if (neg) { y = operator_minus(y); }
   return y;
}

struct sequent operator_minus(struct sequent x)
{
  struct sequent y = x;
  y.detail.frac = -y.detail.frac;
  return y;
}

struct sequent mod_sequent(struct sequent x₁, struct sequent x₂)
{
   struct sequent divisor, multiplicand, difference;
   divisor = div_sequent(x₁,x₂,true);
   multiplicand = mult_sequent(x₂,divisor);
   difference = minus_sequent(x₁,multiplicand);
   return difference;
} /* x1 - x2*floor(x1/x2) */

struct sequent reciproc_sequent(struct sequent bd)
{ struct sequent focus, xn=𝟷ᐧ𝟶, two=𝟸ᐧ𝟶; int n=0;
again:
  if (n > 28) { return xn; }
  focus = minus_sequent(two, mult_sequent(xn,bd));
  xn = mult_sequent(focus,xn); /* start with x₀=1, x_n+1 = x_n*(2 - b*x_n). */
  n += 1;
  goto again;
} /* knipa 𝘦․𝘨 al-coda alt. ː ⤪ and the text '⬷ non-subscript actually correct'. */
/*
   computational f = ^(struct sequent x) { return 1/x; }, 
    f₋prim = ^(struct sequent x) { return -1/x^2; };
   / * enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done }; * /
   void (^ping)(enum Newtoncontrol * ctrl) = ^(enum Newtoncontrol * ctrl) { *ctrl = Newton₋done; };
  if (Newton(f,f₋prim,&x₀,ping)) { return accumulative₋zero(); }
*/

void print₋positive₋integer₋sequent(__int128_t 𝕏, void (^out)(char 𝟬to𝟵))
{ __builtin_uint_t ℕ = 𝕏>>62;
   Base𝕟(ℕ,10,0,out);
}

void print₋sequent(struct sequent 𝕏, 
 void (^digits)(int neg, struct 𝟽bit₋text integers, struct 𝟽bit₋text fracts), 
 void (^zero₋alt₋nonused)(), void (^nonvalid)())
{ int neg=0; __int128_t s=𝕏.detail.frac, delta;
   const struct sequent zero=𝟶ᐧ𝟶, ten=𝟷𝟶ᐧ𝟶, unity=𝟷ᐧ𝟶;
   signed char ints[128], fts[128], *is=ints, *fs=fts;
   int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 i=0, 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 j=0;
   struct 𝟽bit₋text integers, fracts;
   if (!𝕏.valid) { nonvalid(); return; }
   if (s == zero.detail.frac) { zero₋alt₋nonused(); return; }
   if (s < zero.detail.frac) { neg=1; s=-s; }
   print₋positive₋integer₋sequent(s, ^(char 𝟶to𝟿) { *(is + i) = 𝟶to𝟿; ++i; });
   /* print_char(".") alt. print_char(","); */
   s = 10*(s % unity.detail.frac) + 5; delta=10;
   do {
    if (delta > unity.detail.frac) {
      s = s + 0x40000000 - 5000000000; } /* ⬷ round last digit. */
    *(fs + j) = '0' + s/unity.detail.frac;
    s = 10*(s % unity.detail.frac);
    delta *= 10;
   } while (s <= delta);
   integers.bytes=i, integers.start=ints, fracts.bytes=j, fracts.start=fts;
   digits(neg,integers,fracts);
} /* #define EN₋TVÅ₋SUCCESSION₋AUTO₋OCH₋API / * b7874fba */

/* 5 * 1/2 (tenth) + 25 * 1/4 (hundreth) + 1/8 25*5 (thousend) + 1/16 *25*5*5 (ten thousend) */

/* int CastTˣᵗToSequent(
  enum CastToSequentOpinion (^feeder)(unsigned short * l₋to₋r₋digit), 
  struct sequent * value
)
{ struct sequent val=𝟶ᐧ𝟶, sgn=𝟷ᐧ𝟶, onedigit; unsigned short zero₋to₋nine;
   const struct sequent ten = 𝟷𝟶ᐧ𝟶;
   const struct sequent negator = ₋𝟷ᐧ𝟶;
   while (1) {
     enum CastToSequentOpinion opinion = feeder(&zero₋to₋nine);
     switch (opinion) {
      case accept: val=mult_sequent(ten,val);
       int₋to₋sequent((int64_t)zero₋to₋nine,&onedigit);
       val=add_sequent(val,mult_sequent(sgn,onedigit)); break;
      case rejecting: continue;
      case negate: sgn=mult_sequent(sgn,negator); break;
      case complete: *value=val; return 0;
      case annul: return -1;
     }
   }
} */

/* typedef struct sequent (^computational)(struct sequent x);
enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done };
int Newton(computational f, computational f₋prim, struct sequent * x₀, 
 void (^ping)(enum Newtoncontrol * ctrl)) { }
 struct sequent 𝟷𝟸𝟹𝟺₋atan(struct sequent y, struct sequent x) { }
int trapezoid(struct sequent (^f)(struct sequent), struct sequent delta₋t, 
 struct sequent min, void (^memory)(struct sequent integrale, 
 struct sequent t₋acc, int * stop)) { } */

