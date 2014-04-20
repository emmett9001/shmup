#ifndef STRAIGHTLINEMOVER_H
#define STRAIGHTLINEMOVER_H

#include "Mover.h"
#include "ofMain.h"

class BulletPattern;

class StraightLineMover : public Mover
{
    public:
        ofVec2f direction;
        StraightLineMover();
        StraightLineMover(BulletPattern *attached, ofVec2f direction);

        void move(float deltatime);
    protected:
    private:
};

#endif // STRAIGHTLINEMOVER_H
