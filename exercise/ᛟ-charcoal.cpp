/*  test-artistic.cpp | art drawing language. */

import ClibTwinbeam;

UNITTEST(charcoal₋grammar₋1)
{  struct Unicodes program = UC("width 10 cm, height 10 cm; ");
   int width, height; if (parse₋art₋system(program,&width,&height)) 
   { ENSURE(false, "error in parse-art-system."); }
   Linewidth linewidth = ^(double width) { mfprint("linewidth ⬚ ",﹟F(width,1)); };
   Color color = ^(double c, double m, double y, double blk, double a) { 
    mfprint("color ⬚,⬚,⬚,⬚,⬚",﹟F(c,1),﹟F(m,1),﹟F(y,1),﹟F(blk,1),﹟F(a,1)); };
   Begin begin = ^{ mfprint("begin "); };
   Move move = ^(double x, double y) { mfprint("move ⬚,⬚", ﹟F(x,1),﹟F(y,1)); };
   Addcurve addcurve = ^(double x[], double y[]) { mfprint("addcurve ["); 
    for (int i=0; i<3; i+=1) { print("⬚,⬚; ",﹟F(x[i],1),﹟F(y[i],1)); } 
    mfprint("] "); };
   Addstraight addstraight = ^(double x, double y) { 
    mfprint("addstraight ⬚,⬚", ﹟F(x,1),﹟F(y,1)); };
   Closepath closepath = ^{ mfprint("closepath "); };
   Stroke stroke = ^{ mfprint("stroke "); };
   if (draw₋art₋system(program,color,linewidth,begin,move,addcurve,addstraight,closepath,stroke)) 
   { ENSURE(false,"error in draw-art-system."); }
}

