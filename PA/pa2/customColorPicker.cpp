#include "customColorPicker.h"
#include <math.h>


customColorPicker::customColorPicker(double hue, PNG & img)
{
    im = img;
    double h = hue;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    HSLAPixel * pixelofXY = (this->im).getPixel(x, y);
    this->h = h + 0.05;
    if (this->h >= 360){
        this->h -= 360;
    }
    pixelofXY->h = (this->h);
    pixelofXY->s = 1.0;
    pixelofXY->l = 0.8;     
    return *pixelofXY;
}
