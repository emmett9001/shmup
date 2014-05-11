#ifndef STAGE_H
#define STAGE_H

#include "ofMain.h"

class Background;
class BulletPatternGroup;
class BulletPattern;
class Camera;

class Stage
{
public:
    ofVec2f screen_dimensions, zero_point;
    Background *background;
    Camera *camera;
    BulletPatternGroup *group;
    bool edit_mode;

    Stage();
    void update(float deltatime);
    void draw();
    void drawLetterbox();
    void pause();
    void addPattern(BulletPattern *pattern);
    void prepare();
    void setGroupReference(BulletPatternGroup *group);
    bool isScrolling();
    void stopScrolling();
    void startScrolling(ofVec2f direction);
    void toggleEditMode();
};

#endif // STAGE_H
