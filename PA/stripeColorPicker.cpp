#include "stripeColorPicker.h"

stripeColorPicker::stripeColorPicker(HSLAPixel fillColor, int stripeSpacing)
{
    color = fillColor;
    spacing = stripeSpacing;

/* your code here! */
}

HSLAPixel stripeColorPicker::operator()(int x, int y)
{
    if (x % spacing == 0) {
        return color;
    } else { // to be filled with white
        HSLAPixel whiteColor = HSLAPixel();
        return whiteColor;
    }
/* your code here! */
}
