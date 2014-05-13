//
//  Marker.h
//  emptyExample
//
//  Created by Emmett Butler on 5/13/14.
//
//

#ifndef __emptyExample__Marker__
#define __emptyExample__Marker__

#include <iostream>
#include "GameObject.h"
#include "ofMain.h"

class Stage;

class StageMarker : public GameObject {
public:
    Stage *stage;
    bool is_active;
    
    StageMarker(ofVec2f origin);
    void update();
    void start();
    void stop();
    void draw();
};

#endif /* defined(__emptyExample__Marker__) */
