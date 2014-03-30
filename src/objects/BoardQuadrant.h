//
//  BoardQuadrant.h
//  emptyExample
//
//  Created by Emmett Butler on 3/30/14.
//
//

#ifndef __emptyExample__BoardQuadrant__
#define __emptyExample__BoardQuadrant__

#include <iostream>
#include "ofMain.h"
#include "GameObject.h"

#endif /* defined(__emptyExample__BoardQuadrant__) */

class Player;
class BulletPatternGroup;

class BoardQuadrantCollisionDelegate {
public:
    virtual void collided(GameObject *obj) = 0;
};

class BoardQuadrant : public GameObject {
public:
    ofRectangle rect;
    ofColor color;
    vector<Player*>* players;
    BoardQuadrantCollisionDelegate *delegate;
    BulletPatternGroup* pattern_group;
    bool contains_player;
    
    BoardQuadrant();
    BoardQuadrant(ofRectangle rect);
    
    void draw();
    void update(float deltatime);
    void setPlayersReference(vector<Player*>* players);
    void setGroupReference(BulletPatternGroup *pattern_group);
};