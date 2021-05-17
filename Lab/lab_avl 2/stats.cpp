
#include "stats.h"

stats::stats(PNG & im){
    double sumHueXacc = 0;
    double sumHueYacc = 0;
    double sumSatacc = 0;
    double sumLumAcc = 0;

    hist.resize(im.width(), vector<vector<int>> (im.height(), vector<int>(36)));
    sumHueX.resize(im.width(), vector< double >(im.height()));
    sumHueY.resize(im.width(), vector< double >(im.height()));
    sumSat.resize(im.width(), vector< double >(im.height()));
    sumLum.resize(im.width(), vector< double >(im.height()));
    for (int y = 0; y < im.height();  y++) {
        for (int x = 0; x < im.width(); x++){
            HSLAPixel *pixel = im.getPixel(x,y);
            if (x == 0 && y == 0){
                sumHueX[x][y] = (pixel->s)*cos(PI*pixel->h/180);
                sumHueY[x][y] = 1*sin(PI*pixel->h/180);
                sumSat[x][y] = pixel->s;
                sumLum[x][y] = pixel->l;
            }
            if (x != 0 &&  y == 0){
                sumHueX[x][y] = sumHueX[x-1][y]+ (pixel->s)*cos(PI*pixel->h/180);
                sumHueY[x][y] = sumHueY[x-1][y]+ 1*sin(PI*pixel->h/180);
                sumSat[x][y] = sumSat[x-1][y] + pixel->s;
                sumLum[x][y] = sumLum[x-1][y]+ pixel->l;
            } if (y!= 0 && x == 0) {
                sumHueX[x][y] = sumHueX[x][y-1]+ (pixel->s)*cos(PI*pixel->h/180);
                sumHueY[x][y] = sumHueY[x][y-1]+ 1*sin(PI*pixel->h/180);
                sumSat[x][y] = sumSat[x][y-1] + pixel->s;
                sumLum[x][y] = sumLum[x][y-1]+ pixel->l;
            } if (x !=0 && y !=0){
                sumHueX[x][y] = sumHueX[x-1][y] + sumHueX[x][y-1] - sumHueX[x-1][y-1]  + (pixel->s)*cos(PI*pixel->h/180);
                sumHueY[x][y] = sumHueY[x-1][y] + sumHueY[x][y-1] - sumHueY[x-1][y-1]+ 1*sin(PI*pixel->h/180);
                sumSat[x][y] = sumSat[x-1][y] - sumSat[x-1][y-1] + sumSat[x][y-1] + pixel->s;
                sumLum[x][y] = sumLum[x-1][y] + sumLum[x][y-1] - sumLum[x-1][y-1]  + pixel->l;
            }   
    //         sumHueXacc += (pixel->s)*cos(PI*pixel->h/180);
    //         sumHueX[x][y] = sumHueXacc;
    //         sumHueYacc += 1*sin(PI*pixel->h/180);
    //         sumHueY[x][y] = sumHueYacc;
    //         sumSatacc += pixel->s;
    //         sumSat[x][y] = sumSatacc;
    //         sumLumAcc += pixel->l;
    //         sumLum[x][y] = sumLumAcc;
            int bin = floor(pixel->h / 10);
            
            for (int k = 0; k < 36; k++){
                if (x == 0 && y == 0){
                    hist[x][y][k] = 0;
                } else if (x!=0 && y==0){
                    // follow the number on the left pixel of it.
                    hist[x][y][k] = hist[x-1][y][k];
                } else if (y!=0 && x == 0){
                    //follow the top pixel
                    hist[x][y][k] = hist[x][y-1][k];
                } else if (y!=0 && x!=0){
                    hist[x][y][k] = hist[x-1][y][k] + hist[x][y-1][k] - hist[x-1][y-1][k];
                } if (k == bin){
                    hist[x][y][k]++; 
                }
            }
        
        }
    }
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

    long recArea = (lr.first-ul.first+1)*(lr.second-ul.second+1);
    return recArea;
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
    int X1 = ul.first;
    int Y1 = ul.second;
    int getX = lr.first;
    int getY = lr.second; 
    double sumL = 0.0;
    double area = rectArea(ul, lr);
    double avgHueX;
    double avgHueY;

    HSLAPixel pixel;
    if (X1 == 0 && Y1 == 0){
        avgHueX = (sumHueX[getX][getY] / area);
        avgHueY = (sumHueY[getX][getY] / area);
        pixel.s = (sumSat[getX][getY])/ area;
        pixel.l = (sumLum[getX][getY] / area);
        std::cout <<  sumLum[getX][getY] << endl;
    } if (X1 > 0 && Y1 > 0) { //TODO
        avgHueX = ((sumHueX[getX][getY] - sumHueX[X1-1][getY] - sumHueX[getX][Y1-1]+ sumHueX[0][0])/ area);
        avgHueY = ((sumHueY[getX][getY] - sumHueY[X1-1][getY] - sumHueY[getX][Y1-1]+ sumHueY[0][0])/ area);
        pixel.s = ((sumSat[getX][getY]- sumSat[X1-1][getY] - sumSat[getX][Y1-1]+ sumSat[0][0]) / area);
        pixel.l = ((sumLum[getX][getY] - sumLum[X1][getY] - sumLum[getX][Y1-1]+ sumLum[0][0]) / area);
        // std::cout <<  sumLum[getX][getY] << "and" << sumLum[X1][getY]<< "and" << sumLum[getX][Y1-1] << endl;
    }  
    pixel.a = 1.0;
    pixel.h = atan2(avgHueY,avgHueX)*180/PI;
    if (pixel.h < 0){
          pixel.h += 180;
    }
    
    return pixel;
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
int x1 = ul.first;
int x2 = lr.first;
int y1 = ul.first;
int y2 = lr.first;

vector<int> toReturn = hist[x2][y2];

for (int i = 0; i < 36 ; i ++){
int bin = 0;
//if x1 and y1 ==0
    if (x1 !=0  && y1 == 0) {
        bin = hist[x2][y2][i] - hist[x2-1][y1][i];
    } else if (x1 == 0 && y1 !=0 ){
        bin = hist[x2][y2][i] - hist[x1][y2-1][i];
    } else if (x1 !=0  && y1 != 0){
        bin = hist[x2][y2][i] - hist[x2-1][y1][i] - hist[x1][y2-1][i] + hist[x2-1][y2-1][i];
    }
    hist[x2][y2][i] = bin;
}


// for (int x = x1; x < x2; x++){
//     for (int y = y1; y <y2; y++){
//         pair <int,int> newpair;
//         newpair.first = x;
//         newpair.second = y;
//         // HSLAPixel pixel = getAvg(ul, newpair)
//         int bin = floor(pixel.h / 10);
//         toReturn[bin]++;
//     }
// }

return toReturn;
/* your code here */
}

// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0.;

/* your code here */

    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }

    return  -1 * entropy;
\
}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

/* your code here */

}

