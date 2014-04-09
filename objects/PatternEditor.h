#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include "ofMain.h"
#include "GameObject.h"

class BulletPatternGroup;

class PatternEditor
{
    public:
        BulletPatternGroup *group;
        pressedKeys keys;

        void mouseReleased(int x, int y, int button);
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);
        PatternEditor(BulletPatternGroup *group);
        virtual ~PatternEditor();
};

#endif // PATTERNEDITOR_H
