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
//    lattice1 = new unsigned char[pix.getWidth()*pix.getHeight()];
//    lattice2 = new unsigned char[pix.getWidth()*pix.getHeight()];
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
//                    // randomly turn on some entries
//                    lattice1[i] = rand() % 63;
                    int n = rand() % 100;
                    if(n >85){
                        lattice1[i] = 63;
                    }
//
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
    
//    for(int row = 1; row < pix->getHeight()-1; row++){
//        for(int col = 1; col < pix->getWidth()-1; col+=2){
//            int right = col+1;
//            int left = col-1;
//            int up = (row-1)*pix->getWidth();
//            int down = (row+1)*pix->getWidth();
//            int thisRow = row*pix->getWidth();
//            
//            int i = col + thisRow;
//            int i1 = col + down;
//            int i2 = left + down;
//            int i3 = left + thisRow;
//            int i4 = col + up;
//            int i5 = right + thisRow;
//            int i6 = right + down;
//            int i7 = right + up;
//            int i8 = right + 1 + up;
//            int i9 = right + 1 + thisRow;
//            
//            int j = right + down;
//            
//            
//            
//            lattice1[i] = (lattice2[i1] & 1) +
//                          (lattice2[i2] & 2) +
//                          (lattice2[i3] & 4) +
//                          (lattice2[i4] & 8) +
//                          (lattice2[i5] & 16) +
//                          (lattice2[i6] & 32);
////            
//            lattice1[j] = (lattice2[i6] & 1) +
//                          (lattice2[i] & 2) +
//                          (lattice2[i4] & 4) +
//                          (lattice2[i7] & 8) +
//                          (lattice2[i8] & 16) +
//                          (lattice2[i9] & 32);
//        }
//    }
    
    //boundary conditions
     size = pix->getWidth();
    for(int i = 1; i < size-1;i+=2){
       
        // top
        lattice1[i] = 0;
        lattice1[i+1] = 0;
        
        // bottom
        lattice1[i+size * (size-1)]= 0;
        lattice1[i+1 +size*(size-1)] = 0;
        

//
        
//        lattice1[i] = (lattice2[i] & 2) + (lattice2[i] & 32);
        
//        lattice1[i+size*0] =
//            (lattice2[i+size*(0+1)] & 1)+
//            (lattice2[(i-1)+ size*(0+1)] & 2) +
//            (lattice2[(i-1)+size*0] & 4) +
//            (lattice2[i+size*(size-1)] & 8) +
//            (lattice2[(i+1)+size*0] & 16) +
//            (lattice2[(i+1+size*(0+1))] & 32);
////
//        lattice1[i+1] = (lattice2[i] & 1) +
//                                  (lattice2[(i+1) + size] & 2)+
//                                  (lattice2[i] & 4) +
//                                  (lattice2[i+1+size*(size-1)] & 8);
//                                  (lattice2[(i+2)+size*(size-1)] & 16) +
//                                  (lattice2[(i+2+size*0)] & 32);
//////
//        lattice1[i+size * (size-1)] = (lattice2[i] & 1) +
//                                      (lattice2[(i-1)] & 2)+
//                                      (lattice2[(i-1)+size*(size-1)] & 4) +
//                                      (lattice2[i+size*(size-2)] & 8);
//                                      (lattice2[(i+1)+size*(size-1)] & 16) +
//                                      (lattice2[i+1] & 32);
//////
//        lattice1[i+1+size * (size-1)] = (lattice2[i+1] & 1) +
//                                        (lattice2[i+size*(size-1)] & 2)+
//                                        (lattice2[i+size*(size-2)] & 4) +
//                                        (lattice2[(i+1)+size*(size-2)] & 8);
//                                        (lattice2[(i+1)+size*(size-2)] & 16) +
//                                        (lattice2[(i+2)+size*(size-1)] & 32);
    }
    
//    size = pix->getHeight();
    for(int j = 1; j< size-1; j++){
//        int e1 =lattice1[size*j];
        // left
        lattice1[size*j] = 0;
        
        // right
        lattice1[size-1+size*j] = 0;
//        lattice1[size*j] = (lattice2[size*(j+1)] & 1)+
//                           (lattice2[(size-1)+size*j] & 2) +
//                           (lattice2[size*(j-1)] & 4) +
//                           (lattice2[1+size*j] & 8);
//                           (lattice2[1+size*(j-1)] & 16);
//                           (lattice2[1+size*j] & 32);
////
////
//////        
//        lattice1[size-1+size*j] = (lattice2[size-1+size*(j+1)] & 1) +
//                                  (lattice2[size-2 + size*j] & 2) +
//                                  (lattice2[size-1+size*(j-1)] & 4) +
//                                  (lattice2[1+size*j] & 8) +
//                                  (lattice2[size*j] & 16) +
//                                  (lattice2[size*(j+1)] & 32);
    }
//
//    
    
    
    //    lattice1 = lattice2;
//    for(int i = 0; i < pix->getWidth()*pix->getHeight(); i++){
//        lattice1[i] = lattice2[i];
//    }
}

void LatticeGas::updateImage(){
    // scale lattice values up to pixel values
    // and use them to update the pixel array
    for(int i = pix->getWidth()+1; i < pix->size(); i++){
        pix->getPixels()[i] = lattice1[i]*255;
    }
}
