#ifndef STAGE_H
#define STAGE_H

#include "ofMain.h"

class Background;
class BulletPatternGroup;
class Camera;

class Stage
{
public:
    ofVec2f screen_dimensions;
    Background *background;
    Camera *camera;
    BulletPatternGroup *group;

    Stage();
    void update(float deltatime);
    void draw();
    void pause();
    void setGroupReference(BulletPatternGroup *group);
    bool isScrolling();
    void stopScrolling();
    void startScrolling(ofVec2f direction);
};

#endif // STAGE_H
