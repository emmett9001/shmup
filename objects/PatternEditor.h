#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ofMain.h"
#include "GameObject.h"

class BulletPatternGroup;
class BulletPattern;
class Player;
class SketchWriter;
class Camera;

enum kEditMode {
    kPattern, kMover, kCountPending, kVolleyTimeoutPending, kNormal
};

class PatternEditor
{
public:
    BulletPatternGroup *group;
    pressedKeys keys;
    vector<int> pendingCount;
    kEditMode editMode, mainMode;
    Camera *camera;
    BulletPattern *highlightedPattern;
    string typeString;
    vector<Player*>* players;
    ofVec2f mouseDownPos;
    bool paused;
    SketchWriter *writer;

    void mouseReleased(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void pause();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void pushDigit(int key);
    float parseBufferedNumber();
    void mouseMoved(int x, int y);
    void setPlayersReference(vector<Player*>* players);
    PatternEditor(BulletPatternGroup *group, Camera *camera);
};

#endif // PATTERNEDITOR_H
