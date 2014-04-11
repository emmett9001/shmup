#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ofMain.h"
#include "GameObject.h"

class BulletPatternGroup;
class BulletPattern;
class Player;

enum kEditMode {
    kCountPending, kNormal
};

class PatternEditor
{
    public:
        BulletPatternGroup *group;
        pressedKeys keys;
        vector<int> pendingCount;
        kEditMode editMode;
        BulletPattern *highlightedPattern;
        string typeString;
        vector<Player*>* players;

        void mouseReleased(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseDragged(int x, int y, int button);
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void setPlayersReference(vector<Player*>* players);
        PatternEditor(BulletPatternGroup *group);
        virtual ~PatternEditor();
};

#endif // PATTERNEDITOR_H
