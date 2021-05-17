//HSLAPixel.h

//guards
#ifndef CS221UTIL_HSLAPIXEL_H
#define CS221UTIL_HSLAPIXEL_H

// struct HSL{};
// struct HSLA{}; 
namespace cs221util{

class HSLAPixel
{
    public: 
    double h,s,l,a; //hue, sat, luminance, alpha
    
    HSLAPixel(); //default constructor

    HSLAPixel(double h, double s, double l);
    HSLAPixel(double h, double s, double l, double a);
};
}

#endif //HSLAPIXEL_H