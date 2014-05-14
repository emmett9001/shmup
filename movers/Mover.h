#ifndef MOVER_H
#define MOVER_H

#include "ofMain.h"
#include "GameObject.h"
#include "Serializable.h"

class BulletPattern;
class Stage;

class Mover : public Serializable
{
    public:
        BulletPattern *attached;
        bool paused;
        int step, length;
        Stage *stage;
        float duration, wavelength;
        ofVec2f origin, direction;
        Mover *next;
        static const string SLUG;

        void init(BulletPattern *attached, ofVec2f direction, float wavelength);
        Mover();
        Mover(ofVec2f direction, float wavelength);
        Mover(BulletPattern *attached, ofVec2f direction, float wavelength);
        void update(float deltatime);
        void attach(BulletPattern *host);
        virtual void move(float deltatime) = 0;
        ofVec2f originRelativeToStage(Stage *stage);
        virtual string describe() = 0;
        string _describe(string slug);
};

#endif // MOVER_H
