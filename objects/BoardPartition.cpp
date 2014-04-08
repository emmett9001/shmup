//
//  BoardPartition.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/30/14.
//
//

#include "BoardPartition.h"
#include "Player.h"
#include "BoardQuadrant.h"

BoardPartition::BoardPartition() {
    this->quads = vector<BoardQuadrant *>();
    this->quads.push_back(new BoardQuadrant(ofRectangle(0, 0, ofGetWidth()/2, ofGetHeight()/2)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2)));
}

void BoardPartition::draw() {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->draw();
    }
}

void BoardPartition::update(float deltatime) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->update(deltatime);
    }
}

void BoardPartition::setPlayersReference(vector<Player*>* players) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->setPlayersReference(players);
    }
}

void BoardPartition::setGroupReference(BulletPatternGroup *pattern_group) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->setGroupReference(pattern_group);
    }
}

void BoardPartition::setDelegate(BoardQuadrantCollisionDelegate *delegate) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->collisionSubscribers.push_back(delegate);
    }
}