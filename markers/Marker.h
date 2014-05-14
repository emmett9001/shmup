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
#include "Serializable.h"

class Stage;

class StageMarker : public GameObject, public Serializable {
public:
    Stage *stage;
    bool is_active;
    static const string SLUG;

    StageMarker(ofVec2f origin);
    void update();
    void start();
    void stop();
    void draw();
    ofVec2f originRelativeToStage(Stage *stage);
    virtual void do_activation() = 0;
    virtual void do_active_update() = 0;
    virtual string describe() = 0;
    string _describe(string slug);
};

#endif /* defined(__emptyExample__Marker__) */
