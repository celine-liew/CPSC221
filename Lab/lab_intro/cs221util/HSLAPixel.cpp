#include "HSLAPixel.h"

#include <iostream>

namespace cs221util{

HSLAPixel:: HSLAPixel()
{
        s = 0;
        l = 1.0;
        a = 1.0;
}

// HSLAPixel:: HSLAPixel(HSL): h(), s(), l() {}
// HSLAPixel:: HSLAPixel(HSLA): h(), s(), l(), a() {}
HSLAPixel::HSLAPixel(double h, double s, double l) {
    this->h = h;
    this->s = s;
    this->l = l;
}

HSLAPixel::HSLAPixel(double h, double s, double l, double a) {
   this->h = h;
   this->s = s;
   this->l = l;
   this->a = a;
}
}