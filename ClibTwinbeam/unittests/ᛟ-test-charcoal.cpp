/*  test-artistic.cpp | art drawing language. */

import ClibTwinbeam;

UNITTEST(charcoal₋grammar₋1)
{
   struct Unicodes program = UC("width 10 cm, height 10 cm; "); int width, height;
   if (parse₋art₋system(program,&width,&height)) 
   { ENSURE(false, "error in parse-art-system."); }
   Linewidth linewidth = ^(double width) { mfprint("linewidth "); };
   Color color = ^(double c, double m, double y, double blk, double a) { mfprint("color "); };
   Begin begin = ^() { mfprint("begin "); };
   Move move = ^(double x, double y) { mfprint("move "); };
   Addcurve addcurve = ^(double x[], double y[]) { mfprint("addcurve "); };
   Addstraight addstraight = ^(double x, double y) { mfprint("addstraight "); };
   Closepath closepath = ^() { mfprint("closepath "); };
   Stroke stroke = ^() { mfprint("stroke "); };
   if (draw₋art₋system(program,color,linewidth,begin,move,addcurve,addstraight,closepath,stroke)) 
   { ENSURE(false,"error in draw-art-system."); }
}

