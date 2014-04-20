#ifndef MOVER_H
#define MOVER_H

class BulletPattern;

class Mover
{
    public:
        BulletPattern *attached;
        bool paused;
        int step, length;
        float duration;
        Mover *next;

        void init(BulletPattern *attached);
        Mover();
        Mover(BulletPattern *attached);
        void update(float deltatime);
        virtual void move(float deltatime) = 0;
    protected:
    private:
};

#endif // MOVER_H
