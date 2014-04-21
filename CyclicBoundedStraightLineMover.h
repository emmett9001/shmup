#ifndef CYCLICBOUNDEDSTRAIGHTLINEMOVER_H
#define CYCLICBOUNDEDSTRAIGHTLINEMOVER_H

#include "StraightLineMover.h"
#include "ofMain.h"

class BulletPattern;

class CyclicBoundedStraightLineMover : public StraightLineMover
{
    public:
        static const string SLUG;
        float wavelength;
        CyclicBoundedStraightLineMover();
        CyclicBoundedStraightLineMover(ofVec2f direction, float wavelength);
        CyclicBoundedStraightLineMover(BulletPattern *attached, ofVec2f direction, float wavelength);

        void move(float deltatime);
        string describe();
    protected:
    private:
};

#endif // CYCLICBOUNDEDSTRAIGHTLINEMOVER_H
