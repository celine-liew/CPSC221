#include "block.h"
#include <stdio.h>


/** 
 * Returns the width of the current block.
 */
int Block::width() const {
    return data.size();
}

/* Returns the height of the current block. */
int Block::height() const{
    return data[0].size();
}

/** 
 * From im, grabs the vertical strip of pixels whose upper left 
 * corner is at position (column,0), and whose width is width. 
 */
void Block::build(PNG & im, int column, int width){
if(column < 0 || width <= 0 || width > im.width() - column || column >= im.width()){
return;
}
   for (int i = column; i < column + width ; i++){
       vector<HSLAPixel> colPixel;
       for (int j = 0; j < im.height(); j++) {
        // cout << i << j << endl;
        colPixel.push_back(*im.getPixel(i, j));
        // TODO
        };
        data.push_back(colPixel);
        }
}

/**
 * Draws the current block at position (column,0) in im.
 */
void Block::render(PNG & im, int column ) const{
    if (column < 0 || column >= im.width()){return;}
    for (int i = column; i < column + width(); i++) {
        for (int j = 0; j < height(); j++){
            HSLAPixel *pos = im.getPixel(i, j);
            *pos = data[i-column][j];          
        }
    }
}

/**
 * This function changes the saturation of every pixel in the block to 0, which 
 * removes the color, leaving grey.
 */
void Block::greyscale() {
    for (int i = 0; i < width(); i++) {
        for (int j = 0; j < height(); j++){
            data[i][j].s = 0;
        }
    }
}

