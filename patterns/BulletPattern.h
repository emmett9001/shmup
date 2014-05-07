//
//  BulletPattern.h
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//
#pragma once

#ifndef __emptyExample__BulletPattern__
#define __emptyExample__BulletPattern__

#include <iostream>
#include "Bullet.h"
#include "Serializable.h"
#include "GameObject.h"

class Player;
class Mover;

class BulletPattern : public Serializable, public GameObject {
public:
    vector<Bullet> bullets;
    vector<Player*>* players;
    vector<Mover*> movers;
    ofVec2f origin;
    float volley_timeout, bulletspeed, period, duty;
    bool isrunning, paused, highlighted;
    int count;
    static const string SLUG;

    BulletPattern();
    BulletPattern(int count);
    BulletPattern(int count, ofVec2f origin);
    BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout);
    BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty);
    virtual string describe() = 0;
    string _describe(string slug);
    void init(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty);
    void draw();
    void update(float deltatime);
    void start();
    void pause();
    void addMover(Mover *mover);
    void clearMovers();
    void destroyAllBullets();
    void setOrigin(ofVec2f origin);
    void setPlayersReference(vector<Player*>* players);
    void highlight();
    void unhighlight();

private:
    float frame_lifetime, last_volley, period_switch;
    virtual void volley() = 0;
};

#endif /* defined(__emptyExample__BulletPattern__) */
