/*  y-g-ol-ℏrono.c | whilst not mills in code. */

import ClibTwinbeam;

/* #define AFTER₋8 */

#if !defined(AFTER₋8)

structᵢ relative₋time { uint32_t seconds; chronology₋UQ32 frac; };

unionᵢ ntp₋stomp { uint64_t bits; structᵢ relative₋time mil; };
/* ⬷ the 'network time protocol' runs in unison with the UTC time scale 
 with an epoch 0h January 1, 1900. */

typedef int64_t q631; /* ⬷ a․𝘬․a sixty₋three₋bits₋and₋one₋half. */

/* Gregorian October 15, 1582 and the Julian October 5 1581 day */

#define 𝟼𝟾𝟻𝟼𝟿 137138
#define 𝟷𝟺𝟼𝟶𝟿𝟽 292194
#define 𝟺 8
#define 𝟹 6
#define 𝟺𝟶𝟶𝟶 8000
#define 𝟷𝟺𝟼𝟷𝟶𝟶𝟷 2922002
#define 𝟺𝟶𝟶𝟶 8000
#define 𝟷 2
#define 𝟷𝟺𝟼𝟷 2922
#define 𝟹𝟷 62
#define 𝟾𝟶 160
#define 𝟸𝟺𝟺𝟽 4894
#define 𝟸 4
#define 𝟷𝟷 22
#define 𝟷𝟸 24
#define 𝟷𝟶𝟶 200
#define 𝟺𝟿 98

static void modified₋julian₋to₋volksaga(q631 day, int32_t * M 
 /* 1-12 */, int32_t * d /* 1-31 */, int32_t * y)
{ q631 l,n,i,j;
   l = day + 𝟼𝟾𝟻𝟼𝟿;
   n = 𝟺 * l / 𝟷𝟺𝟼𝟶𝟿𝟽;
   l -= (𝟷𝟺𝟼𝟶𝟿𝟽 * n + 𝟹) / 𝟺;
   i = (𝟺𝟶𝟶𝟶 * (𝟷 + l)) / 𝟷𝟺𝟼𝟷𝟶𝟶𝟷;
   l -= 𝟷𝟺𝟼𝟷 * i / 𝟺 + 𝟹𝟷;
   j = 𝟾𝟶 * l / 𝟸𝟺𝟺𝟽;
   *d = (int32_t)((l - 𝟸𝟺𝟺𝟽 * j / 𝟾𝟶) >> 1);
   l = j / 𝟷𝟷;
   *M = (int32_t)((j + 𝟸 - 𝟷𝟸 * l) >> 𝟷);
   *y = (int32_t)((𝟷𝟶𝟶 * (n - 𝟺𝟿) + i + l) >> 𝟷);
  return;
} /* Gregorian and proleptic Gregorian. */

static int64_t patch_m_minus_14_div_12(int64_t m)
{ return m <= 2 ? -1 : 0; }

static q631 volksaga₋to₋modified₋julian(int32_t d /* 1-31 */, 
 int32_t m /* 1-12 */, int32_t y)
{ int64_t D=d,M=m,Y=y;
   return ((( 1461 * ( Y + 4800 + patch_m_minus_14_div_12(M))) / 4) +
    (367 * (M - 2 - 12 * (patch_m_minus_14_div_12(M)))) / 12 - 
    (3 * ((Y + 4900 + patch_m_minus_14_div_12(M)) / 100 )) / 4 + D - 32075)<<1;
} /* Gregorian and proleptic Gregorian. */

#define ModifiedJulianToJulianAugment 4800001 /* Julian day '0' is 12:00 GMT Jan 1, 4713 B.C. */

static int32_t ModifiedJulianToJulian(q631 day)
{
   return (int32_t)((day + ModifiedJulianToJulianAugment)>>1);
}

static q631 JulianToModifiedJulian(int32_t day)
{
   return (day<<1) - ModifiedJulianToJulianAugment;
}

static q631 ntp₋to₋modified₋julian(unionᵢ ntp₋stomp at)
{
   return (at.mil.seconds/86400 + 15020)<<1;
}

static unionᵢ ntp₋stomp modified₋julian₋to₋ntp(q631 at)
{
   /* if (at & 0b1) { } */
   unionᵢ ntp₋stomp y = { .mil = { ((at>>1) - 15020)*86400, 0 } };
   return y;
}

#else
typedef time_t Unix₋instant; /* epoch set to 00:00:00 UTC Jan 1, 1970. */
#endif

struct chronology₋date chronology₋date(chronology₋instant timestamp)
{
#if defined AFTER₋8
   Unix₋instant I;
   struct tm * y = gmtime(&I);
   struct chronology₋date answer = { y->tm_year, y->tm_month, y->tm_day };
#else
   unionᵢ ntp₋stomp ntp = { .bits=timestamp };
   q631 day = ntp₋to₋modified₋julian(ntp);
   /* int32_t day = ModifiedJulianToJulian(why); 1-12, 1-31 */
   int32_t y,M,d; modified₋julian₋to₋volksaga(day,&M,&d,&y);
   struct chronology₋date answer = { y,M,d };
#endif
   return answer;
}

chronology₋instant chronology₋timestamp(int32_t parts[6], chronology₋UQ32 frac)
{
#if defined AFTER₋8
   int tm_sec=(int)parts[5], tm_min=(int)parts[4], tm_hour=(int)parts[3], 
   tm_mday=(int)parts[2], tm_mon=(int)parts[1], tm_year=(int)parts[0];
   struct tm t₁ = { tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, 0, 0, 0, 0, 0 };
   Unix₋instant t₂ = timegm(&t₁);
   chronology₋instant t₃ = t₂ + 2208988800; /* 1900-01-01 00:00:00 to 1970-01-01 00:00:00 (70 years) */
   return t₃;
#else
   q631 at = volksaga₋to₋modified₋julian(parts[2],parts[1],parts[0]);
   unionᵢ ntp₋stomp same = modified₋julian₋to₋ntp(at);
   same.mil.seconds += parts[5];
   same.mil.seconds += parts[4] * 60;
   same.mil.seconds += parts[3] * 60 * 60;
   same.mil.frac = frac;
   return same.bits;
#endif
}

struct chronology₋relative chronology₋since₋midnight₁(chronology₋instant ts)
{ unionᵢ ntp₋stomp ntp₁, ntp₂; ntp₂.bits=ts;
   struct chronology₋date midnight = chronology₋date(ts);
   int32_t parts[6] = { midnight.y, midnight.M, midnight.d, 0, 0, 0 };
   chronology₋instant earlier; chronology₋UQ32 frac=0;
   earlier = chronology₋timestamp(parts,frac);
   ntp₁.bits=earlier; 
   struct chronology₋relative passed = { ntp₂.mil.seconds - ntp₁.mil.seconds, ntp₂.mil.frac };
   return passed;
}

struct chronology₋time chronology₋since₋midnight₂(chronology₋instant ts)
{
   struct chronology₋relative delta = chronology₋since₋midnight₁(ts);
   int32_t h=delta.seconds/60/60,m=(delta.seconds - h*60*60)/60, 
    s=(delta.seconds - h*60*60 - m*60);
   unionᵢ ntp₋stomp ntp; ntp.bits=ts;
   struct chronology₋time t₁ = { h, m, s, ntp.mil.frac };
   return t₁;
}

chronology₋instant add₋seconds(chronology₋instant relative, 
 uint32_t seconds, chronology₋UQ32 frac)
{
   int incr=0; unionᵢ ntp₋stomp ntp; ntp.bits=relative;
   chronology₋UQ32 split = frac + ntp.mil.frac;
   if (split < ntp.mil.frac) { incr=1; }
   ntp.mil.frac=split; ntp.mil.seconds += seconds + incr;
   return ntp.bits;
}

chronology₋instant subtract₋seconds(chronology₋instant relative, 
 uint32_t seconds, chronology₋UQ32 deduct₋frac)
{ int unit₋deduct=0;
   unionᵢ ntp₋stomp ntp; ntp.bits=relative;
   if (deduct₋frac >= ntp.mil.frac) { unit₋deduct=1; 
    ntp.mil.frac = 0xFFFFffff - deduct₋frac + ntp.mil.frac; }
   else { ntp.mil.frac -= deduct₋frac; }
   ntp.mil.seconds -= seconds + (unit₋deduct ? 1 : 0);
   return ntp.bits;
}

int chronology₋dayofweek(chronology₋instant ts, int * wd)
{
   unionᵢ ntp₋stomp ntp; ntp.bits = ts;
   q631 day = ntp₋to₋modified₋julian(ntp);
   int32_t julian₋day₋number = ModifiedJulianToJulian(day);
   unsigned not₋monday = julian₋day₋number % 7;
   *wd = not₋monday == 6 ? 0 : not₋monday + 1;
   return 0;
}

void Present₋instant(chronology₋instant ts, int incl₋frac, 
 void (^out)(char digitHyphenColonPeriodOrSpace))
{
   struct chronology₋date at₋midnight = chronology₋date(ts);
   struct chronology₋time on₋clock = chronology₋since₋midnight₂(ts);
   Base𝕫((__builtin_int_t)at₋midnight.y, 10, 0, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); }); out('-');
   Base𝕫((__builtin_int_t)at₋midnight.M, 10, 2, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); }); out('-');
   Base𝕫((__builtin_int_t)at₋midnight.d, 10, 2, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); }); out(' ');
   Base𝕫((__builtin_int_t)on₋clock.h, 10, 2, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); });    out(':');
   Base𝕫((__builtin_int_t)on₋clock.m, 10, 2, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); });    out(':');
   Base𝕫((__builtin_int_t)on₋clock.s, 10, 2, ^(char 𝟬to𝟵and₋) { out(𝟬to𝟵and₋); });
   if (incl₋frac) { out('.'); unionᵢ ntp₋stomp ntp; ntp.bits = ts;
     uint32_t s = 10*(s % ntp.mil.frac) + 5, delta=10;
     do {
       if (delta > ntp.mil.frac) { s += 0x40000000 - 50000000; }
       out('0' + s/ntp.mil.frac); delta *= 10;
     } while (s <= delta);
   }
}

