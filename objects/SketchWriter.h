//
//  SketchWriter.h
//  emptyExample
//
//  Created by Emmett Butler on 4/21/14.
//
//

#ifndef __emptyExample__SketchWriter__
#define __emptyExample__SketchWriter__

#include <iostream>
#include "ofMain.h"

class Stage;

class SketchWriter
{
public:
    SketchWriter();

    void loadSketch(std::string filename, Stage *stage);
    void writeOut(std::string filename, Stage *stage);
    ofVec2f parseCoordinates(std::string token);
};

#endif /* defined(__emptyExample__SketchWriter__) */
