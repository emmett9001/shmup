#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ofMain.h"
#include "GameObject.h"

class BulletPatternGroup;
class BulletPattern;
class Player;
class SketchWriter;

enum kEditMode {
    kPattern, kMover, kCountPending, kNormal
};

class PatternEditor
{
    public:
        BulletPatternGroup *group;
        pressedKeys keys;
        vector<int> pendingCount;
        kEditMode editMode, mainMode;
        BulletPattern *highlightedPattern;
        string typeString;
        vector<Player*>* players;
        ofVec2f mouseDownPos;
        bool paused;
        SketchWriter *writer;

        void mouseReleased(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseDragged(int x, int y, int button);
        void loadSketch();
        void pause();
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);
        int parseBufferedNumber();
        void mouseMoved(int x, int y);
        void setPlayersReference(vector<Player*>* players);
        PatternEditor(BulletPatternGroup *group);
};

#endif // PATTERNEDITOR_H
