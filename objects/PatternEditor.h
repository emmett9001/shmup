#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ofMain.h"
#include "GameObject.h"

class BulletPatternGroup;
class Player;

class PatternEditor
{
    public:
        BulletPatternGroup *group;
        pressedKeys keys;
        string typeString;
        vector<Player*>* players;

        void mouseReleased(int x, int y, int button);
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);
        void setPlayersReference(vector<Player*>* players);
        PatternEditor(BulletPatternGroup *group);
        virtual ~PatternEditor();
};

#endif // PATTERNEDITOR_H
