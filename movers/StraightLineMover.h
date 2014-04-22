#ifndef STRAIGHTLINEMOVER_H
#define STRAIGHTLINEMOVER_H

#include "Mover.h"
#include "ofMain.h"

class BulletPattern;

class StraightLineMover : public Mover
{
    public:
        static const string SLUG;
        StraightLineMover();
        StraightLineMover(ofVec2f direction);
        StraightLineMover(ofVec2f direction, float wavelength);
        StraightLineMover(BulletPattern *attached, ofVec2f direction, float wavelength);

        void move(float deltatime);
        string describe();
private:
    REGISTER_DEC_TYPE(StraightLineMover);
};

#endif // STRAIGHTLINEMOVER_H
