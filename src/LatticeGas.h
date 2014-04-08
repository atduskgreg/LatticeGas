//
//  LatticeGas.h
//  LatticeGas
//
//  Created by Greg Borenstein on 4/1/14.
//
//

#ifndef __LatticeGas__LatticeGas__
#define __LatticeGas__LatticeGas__

#include <iostream>
#include "ofPixels.h"

class LatticeGas {
public:
    LatticeGas();
    LatticeGas(ofPixels& pix);
    void setStartingState(int squareSize, bool addNoise);
    void update();

private:
    ofPixels* pix;
    void processCollisions();
    void processTransits();
    void updateImage();
    // double-buffered lattice
    unsigned char lattice1[500*500];
    unsigned char lattice2[500*500];
    unsigned char collisionTable1[64]  = {
        0,1,2,3,4,5,
        6,7,8,36,10,
        11,12,13,14,15,
        16,17,9,19,20,
        42,22,23,24,25,
        26,27,28,29,30,
        31,32,33,34,35,
        9,37,38,39,40,
        41,21,43,44,45,
        46,47,48,49,50,
        51,52,53,54,55,
        56,57,58,59,60,
        61,62,63
    };
    // see table derivation here: https://www.flickr.com/photos/unavoidablegrain/13647870725/
    unsigned char collisionTable2[64]  = {
        0,1,2,3,4,5,
        6,7,8,18,10,
        11,12,13,14,15,
        16,17,36,19,20,
        42,22,23,24,25,
        26,27,28,29,30,
        31,32,33,34,35,
        9,37,38,39,40,
        41,21,43,44,45,
        46,47,48,49,50,
        51,52,53,54,55,
        56,57,58,59,60,
        61,62,63};
};

#endif /* defined(__LatticeGas__LatticeGas__) */
