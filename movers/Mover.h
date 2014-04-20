#ifndef MOVER_H
#define MOVER_H

#include "ofMain.h"

class BulletPattern;

class Mover
{
    public:
        BulletPattern *attached;
        bool paused;
        int step, length;
        float duration;
        ofVec2f origin;
        Mover *next;
        static const string SLUG;

        void init(BulletPattern *attached);
        Mover();
        Mover(BulletPattern *attached);
        void update(float deltatime);
        void attach(BulletPattern *host);
        virtual void move(float deltatime) = 0;
        virtual string describe() = 0;
    protected:
    private:
};

#endif // MOVER_H
