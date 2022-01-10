/*  test-chrono.cpp | calender and computations. */

import ClibTwinbeam;

typedef chronology₋instant Instant;

UNITTEST(chronology₋backward)
{ int incl₋frac=true, wd; int32_t yMdhms[6]={ 2021,12,25,12,00,00 }; 
   chronology₋UQ32 frac=0, deduct₋frac=0; uint32_t seconds=100;
   Instant instant=chronology₋timestamp(yMdhms,frac), 
    earlier=subtract₋seconds(instant,seconds,deduct₋frac);
   Present₋instant(earlier,incl₋frac, ^(char digitHyphenColonPeriodOrSpace) {
    print("⬚", ﹟c7(digitHyphenColonPeriodOrSpace)); });
   if (chronology₋dayofweek(earlier,&wd)) { return; }
}

UNITTEST(chronology₋forward)
{ int incl₋frac=true, wd; int32_t yMdhms[6]={ 2021,12,25,12,00,00 }; 
   chronology₋UQ32 frac=0, amend₋frac=0; uint32_t seconds=100;
   Instant instant=chronology₋timestamp(yMdhms,frac), 
    later=add₋seconds(instant,seconds,amend₋frac);
   Present₋instant(later,incl₋frac, ^(char digitHyphenColonPeriodOrSpace) {
    print("⬚", ﹟c7(digitHyphenColonPeriodOrSpace)); });
   if (chronology₋dayofweek(later,&wd)) { return; }
}


