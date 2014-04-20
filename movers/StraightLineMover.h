#ifndef STRAIGHTLINEMOVER_H
#define STRAIGHTLINEMOVER_H

#include "Mover.h"
#include "ofMain.h"

class BulletPattern;

class StraightLineMover : public Mover
{
    public:
        static const string SLUG;
        ofVec2f direction;
        StraightLineMover();
        StraightLineMover(ofVec2f direction);
        StraightLineMover(BulletPattern *attached, ofVec2f direction);

        void move(float deltatime);
        string describe();
    protected:
    private:
};

#endif // STRAIGHTLINEMOVER_H
