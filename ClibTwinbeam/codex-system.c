/*  codex-system.c |  material on terminal. */

import ClibTwinbeam;

/* Current values left=1, right, center, justified, italic, bold, ... */

int format₋system(int count, char32̄_t * text, Attributes attrs)
{
   char32̄_t * header = UC("The header"); int offset₁=0; int count₁=5; int attribute₁=1;
   char32̄_t * copy = UC("Here we may want to present additional details"); int offset₂=0; int count₂=30; int attribute₂=2;
   attrs(header,offset₁,count₁,attribute₁);
   attrs(copy,offset₂,count₂,attribute₂);
   return 0;
}

int parse₋art₋system(int count, char32̄_t * text, int * width, int * height)
{
   *width=512; *height=256;
   return 0;
}

int draw₋art₋system(int count, char32̄_t * text, Color color, Linewidth linewidth, 
 Begin begin, Move move, Addcurve curve, Addstraight straight, 
 Closepath closepath, Stroke stroke)
{
   print("⬚\n", ﹟S(text));
   linewidth(0.5);
   color(0.0, 0.0, 0.0, 1.0, 1.0);
   begin(); move(100.0, 100.0); straight(150.0, 120.0); straight(120.0, 130.0); closepath(); stroke();
   return 0;
}

int regional₋system(unsigned retrospect₋rows)
{
   return 0;
}

