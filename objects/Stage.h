#ifndef STAGE_H
#define STAGE_H

#include "ofMain.h"

class Background;
class BulletPatternGroup;
class BulletPattern;
class Camera;
class StageMarker;
class Player;

class Stage
{
public:
    ofVec2f screen_dimensions, zero_point;
    Background *background;
    Camera *camera;
    vector<Player *> *players;
    BulletPatternGroup *group;
    vector<StageMarker *> markers;
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
    void addMarker(StageMarker *marker);
};

#endif // STAGE_H
