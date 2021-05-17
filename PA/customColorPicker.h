#ifndef CUSTOMOLORPICKER_H
#define CUSTOMOLORPICKER_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"

/**
 * customColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a gradient pattern.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new customColorPicker.
     *
     * @param freq_ Frequency at which to cycle colors/ Hue for starting hue point
     */
    customColorPicker(double hue, PNG & im);

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel nextColor();
    long double freq;
    PNG im;
    double h;
};

#endif
