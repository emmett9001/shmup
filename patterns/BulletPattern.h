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

#endif /* defined(__emptyExample__BulletPattern__) */

class Player;

class BulletPattern{
public:
    vector<Bullet> bullets;
    vector<Player*>* players;
    ofVec2f origin;
    float volley_timeout, bulletspeed, period, duty;
    bool isrunning;
    int count;
    static const string SLUG;

    BulletPattern();
    BulletPattern(int count);
    BulletPattern(int count, ofVec2f origin);
    BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout);
    BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty);
    virtual string describe() = 0;
    void init(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty);
    void draw();
    void update(float deltatime);
    void start();
    void setPlayersReference(vector<Player*>* players);

private:
    float frame_lifetime, last_volley, period_switch;
    virtual void volley() = 0;
};
