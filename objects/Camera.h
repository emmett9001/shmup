//
//  Camera.h
//  emptyExample
//
//  Created by Emmett Butler on 5/5/14.
//
//

#ifndef __emptyExample__Camera__
#define __emptyExample__Camera__

#include <iostream>
#include "ofMain.h"

class BulletPatternGroup;
class GameObject;
class Background;

typedef struct _tick {
    int print_pos;
    int pos;
} tick;

class Camera {
public:
    BulletPatternGroup *group;
    Background *background;
    vector<GameObject*> objects;
    vector<tick*> ticks;
    int ticks_count;
    ofVec2f scroll_direction, last_scroll_direction, size, zero_point, origin;
    bool paused;
    
    Camera(ofVec2f size, ofVec2f zero_point);
    void setGroupReference(BulletPatternGroup *group);
    void setBackgroundReference(Background *background);
    void update(float deltatime);
    void startScrolling(ofVec2f dir);
    void stopScrolling();
    bool isScrolling();
    void move(ofVec2f dir);
    void pause();
    void draw();
    void unpause();
};

#endif /* defined(__emptyExample__Camera__) */
