//
//  GameObject.h
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//
#pragma once

#ifndef __emptyExample__GameObject__
#define __emptyExample__GameObject__

#include "ofMain.h"
#include <iostream>

#endif /* defined(__emptyExample__GameObject__) */

#define MIN_DELTA .03

struct pressedKeys {
    bool up;
    bool down;
    bool left;
    bool right;
    bool _1;
    bool _2;
    bool _3;
    bool _4;
    bool _5;
    bool _6;
};

class GameObject{
public:
    ofVec2f pos, dir;
    float frame_lifetime;

    virtual void draw() = 0;
    virtual void update(float deltatime);
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseMoved(int x, int y);
    bool is_onscreen();
};
