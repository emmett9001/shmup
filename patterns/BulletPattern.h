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

class Player;
class Mover;

class BulletPattern{
public:
    vector<Bullet> bullets;
    vector<Player*>* players;
    vector<Mover*> movers;
    ofVec2f origin;
    float volley_timeout, bulletspeed, period, duty;
    bool isrunning, paused;
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
    void setPlayersReference(vector<Player*>* players);

private:
    float frame_lifetime, last_volley, period_switch;
    virtual void volley() = 0;
};

template<typename T> BulletPattern * createT() { return new T; }
typedef std::map<std::string, BulletPattern*(*)()> map_type;
struct BulletPatternFactory {
    static map_type *creator_map;

    static BulletPattern * createInstance(std::string const& s) {
        map_type::iterator it = getMap()->find(s);
        if(it == getMap()->end())
            return 0;
        return it->second();
    }

protected:
    static map_type * getMap() {
        if(!creator_map) { creator_map = new map_type; }
        return creator_map;
    }
};

template<typename T>
struct DerivedRegister : BulletPatternFactory {
    DerivedRegister(std::string const& s) {
        getMap()->insert(std::make_pair(s, &createT<T>));
    }
};

#define REGISTER_DEC_TYPE(NAME) \
    static DerivedRegister<NAME> reg

#define REGISTER_DEF_TYPE(NAME) \
    DerivedRegister<NAME> NAME::reg(#NAME)

#endif /* defined(__emptyExample__BulletPattern__) */
