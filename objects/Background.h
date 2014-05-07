//
//  Background.h
//  emptyExample
//
//  Created by Emmett Butler on 5/5/14.
//
//

#ifndef __emptyExample__Background__
#define __emptyExample__Background__

#include <iostream>
#include "ofMain.h"
#include "GameObject.h"

class GameObject;

class Background : public GameObject {
public:
    bool infinite;
    float tile_height;
    ofVec2f size;

    Background(ofVec2f size);
    void draw();
    void update(float deltatime);
};

#endif /* defined(__emptyExample__Background__) */
