//
//  ScrollSpeedMarker.h
//  emptyExample
//
//  Created by Emmett Butler on 5/13/14.
//
//

#ifndef __emptyExample__ScrollSpeedMarker__
#define __emptyExample__ScrollSpeedMarker__

#include <iostream>
#include "Marker.h"
#include "ofMain.h"

class Camera;

class ScrollSpeedMarker : public StageMarker {
public:
    static const string SLUG;
    ofVec2f scroll_direction;
    float y_delta;

    ScrollSpeedMarker();
    ScrollSpeedMarker(ofVec2f origin, ofVec2f scroll_direction);
    ScrollSpeedMarker(ofVec2f origin, float delta);
    virtual void do_activation();
    virtual void do_active_update();
    string describe();
private:
    REGISTER_DEC_TYPE(ScrollSpeedMarker);
};

#endif /* defined(__emptyExample__ScrollSpeedMarker__) */
