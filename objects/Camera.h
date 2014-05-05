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

class Camera {
public:
    BulletPatternGroup *group;
    vector<GameObject*> objects;
    ofVec2f scroll_direction;
    
    Camera();
    void setGroupReference(BulletPatternGroup *group);
    void update(float deltatime);
    void startScrolling(ofVec2f dir);
    void stopScrolling();
    bool isScrolling();
};

#endif /* defined(__emptyExample__Camera__) */
