#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, 
double tolerance, HSLAPixel center)
{
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
    HSLAPixel * pixelofXY = (this->im).getPixel(x, y);
    bool toReturn = false;
    int diameter = 3*3;
    for (int i = -3; i <= 3; i++ ){
        for (int j = -3; j <= 3; j++){
            int xtoUse = x + i;
            if (xtoUse < 0 || xtoUse >= (this->im).width()){
                toReturn = true;
                break;
            }
            int ytoUse = y + j;
            if (ytoUse < 0 || ytoUse > (this->im).height() -1){
                toReturn = true;
                break;
            }
            else {
                HSLAPixel* pixeltoCheck =  (this->im).getPixel(xtoUse, ytoUse);
                double compareTol = pixeltoCheck->dist(this->ctr);
                int compareRad = (x - xtoUse) * (x - xtoUse) + (y - ytoUse) * (y - ytoUse);
                if (( compareRad <= diameter) && compareTol >= this->tol) {
                    toReturn = true;
                    break;
                }
            }
        }
    }
    if (toReturn) {
        return this->color;
    } else {
        return * pixelofXY;
    }
    
/* Your code here! */
}
