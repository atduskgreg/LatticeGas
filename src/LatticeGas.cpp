//
//  LatticeGas.cpp
//  LatticeGas
//
//  Created by Greg Borenstein on 4/1/14.
//
//

#include "LatticeGas.h"

LatticeGas::LatticeGas(){}

LatticeGas::LatticeGas(ofPixels& pix) {
    this->pix = &pix;
}

void LatticeGas::setStartingState(int squareSize, bool addNoise){
    int centerX = pix->getWidth()/2;
    int centerY = pix->getHeight()/2;
    
    for(int row = 0; row < pix->getHeight(); row++ ){
        for(int col = 0; col < pix->getWidth(); col++){
            int i = col + row*pix->getWidth();
            // within bounds of square
            if((col > centerX-squareSize/2) && (col < centerX+squareSize/2) &&
               (row > centerY-squareSize/2) && (row < centerY+squareSize/2)){
                lattice1[i] = 63;
            } else { // outside of square
                lattice1[i] = 0;
                if(addNoise){
                    // randomly turn on some entries
                    int n = rand() % 100;
                    if(n >85){
                        lattice1[i] = 63;
                    }
                }
            }
        }
    }
}

void LatticeGas::update(){
    processCollisions();
    processTransits();
    updateImage();
}

void LatticeGas::processCollisions(){
    for(int row = 0; row < pix->getHeight(); row+=2){
        for(int col = 0; col < pix->getWidth(); col++){
            int i = col + row*pix->getWidth();
            int j = col + (row+1)*pix->getWidth();

            lattice2[i] = collisionTable1[lattice1[i]];
            lattice2[j] = collisionTable2[lattice1[j]];
        }
    }
}

void LatticeGas::processTransits(){
    int size = pix->getWidth();
    for(int col = 1 ; col < size-1; col+=2){
        for(int row = 1; row < size-1; row++){
            lattice1[col+size*row] =
                (lattice2[col+size*(row-1)] & 1) +
                (lattice2[(col-1) + size*(row+1)] & 2) +
                (lattice2[(col-1) + size*row] & 4) +
                (lattice2[col+size*(row-1)] & 8) +
                (lattice2[(col+1)+size*row] & 16) +
                (lattice2[(col+1)+size*(row+1)] & 32);
            
            lattice1[(col+1)+size*row] =
                (lattice2[(col+1)+size*(row+1)] & 1) +
                (lattice2[col+size*row] & 2) +
                (lattice2[col+size*(row-1)] & 4) +
                (lattice2[(col+1) + size*(row-1)] & 8) +
                (lattice2[(col+2) + size*(row-1)] & 16) +
                (lattice2[(col+2) + size*row] & 32);
        }
    }
    
    // deal with edge glitches
    for(int i = 1; i < size-1;i+=2){
       
       // top
        lattice1[i] = 0;
        lattice1[i+1] = 0;
        
        // bottom
        lattice1[i+size * (size-1)]= 0;
        lattice1[i+1 +size*(size-1)] = 0;
    }
    
    for(int j = 1; j< size-1; j++){
        // left
        lattice1[size*j] = 0;
        
        // right
        lattice1[size-1+size*j] = 0;
    }

}

void LatticeGas::updateImage(){
    // scale lattice values up to pixel values
    // and use them to update the pixel array
    for(int i = pix->getWidth()+1; i < pix->size(); i++){
        pix->getPixels()[i] = lattice1[i]*255;
    }
}
