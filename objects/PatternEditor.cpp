#include "PatternEditor.h"

#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"

#include "StraightLineMover.h"
#include "CyclicBoundedStraightLineMover.h"

#include "BulletPatternGroup.h"

#include "SketchWriter.h"

PatternEditor::PatternEditor(BulletPatternGroup *group)
{
    this->group = group;
    this->typeString =  "";
    this->highlightedPattern = NULL;
    this->mainMode = kPattern;
    this->editMode = kNormal;
    this->paused = false;
    writer = new SketchWriter();
    writer->loadSketch("dump.txt", this->group);
    this->keys = pressedKeys();
}

void PatternEditor::pause() {
    this->paused = !this->paused;
    this->group->pause();
}

void PatternEditor::loadSketch() {
    
}

void PatternEditor::draw() {
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(this->typeString, 100, 100, 0);

    if (this->mainMode == kMover) {
        ofDrawBitmapString("MOVER MODE", 100, 50, 0);
    } else if (this->mainMode == kPattern) {
        ofDrawBitmapString("PATTERN MODE", 100, 50, 0);
    }

    if (this->highlightedPattern != NULL) {
        if (this->mainMode == kMover) {
            ofSetColor(0, 0, 255, 50);
        } else if (this->mainMode == kPattern) {
            ofSetColor(255, 0, 0, 50);
        }
        ofRect(this->highlightedPattern->origin.x-25, this->highlightedPattern->origin.y-25, 50, 50);
    }
}

void PatternEditor::mousePressed(int x, int y, int button) {
    this->keys.mouse1 = true;
    this->mouseDownPos = ofVec2f(x, y);
}

void PatternEditor::mouseDragged(int x, int y, int button) {
    if (this->keys.z && this->keys.mouse1 && this->highlightedPattern != NULL) {
        this->highlightedPattern->origin = ofVec2f(x, y);
    }
}

void PatternEditor::mouseMoved(int x, int y){
    this->highlightedPattern = NULL;
    for(vector<BulletPattern*>::iterator it2 = this->group->patterns.begin(); it2 != this->group->patterns.end(); ++it2) {
        BulletPattern* currentPattern = (BulletPattern *)*it2;
        ofVec2f disp = currentPattern->origin - ofVec2f(x, y);
        if (disp.length() < 50) {
            this->highlightedPattern = currentPattern;
        }
    }
}

void PatternEditor::mouseReleased(int x, int y, int button){
    this->keys.mouse1 = false;
    ofVec2f pos = ofVec2f(x, y);
    ofVec2f mouseDragDisp = ofVec2f(x, y) - this->mouseDownPos;
    if (this->mainMode == kPattern) {
        if(this->keys._1) {
            this->group->addPattern(new CyclicEllipseBulletPattern(30, pos, 7, .3));
        }
        if(this->keys._2) {
            this->group->addPattern(new RadialBulletPattern(20, pos, 10, .085));
        }
        if(this->keys._3) {
            this->group->addPattern(new FanOutBulletPattern(10, pos, 5, .2, PI/2, ofVec2f(0, 1), 0, 1, .5));
        }
        if(this->keys._4) {
            this->group->addPattern(new TargetedBulletPattern(1, pos, 5, .1, 2, .5));
        }
        if(this->keys._5) {
            this->group->addPattern(new OscillatingFanOutBulletPattern(10, pos, 5, .2, ofVec2f(0, 1)));
        }
        if (!this->keys.z && this->highlightedPattern != NULL) {
            this->group->patterns.erase(std::remove(this->group->patterns.begin(), this->group->patterns.end(), this->highlightedPattern), this->group->patterns.end());
        }
    } else if (this->mainMode == kMover) {
        if (this->highlightedPattern != NULL) {
            if (this->keys._1) {
                this->highlightedPattern->addMover(new StraightLineMover(mouseDragDisp/100));
            } else if (this->keys._2) {
                this->highlightedPattern->addMover(new CyclicBoundedStraightLineMover(mouseDragDisp/100, mouseDragDisp.length()));
            } else {
                this->highlightedPattern->clearMovers();
            }
        }
    }
    for(vector<BulletPattern*>::iterator it2 = this->group->patterns.begin(); it2 != this->group->patterns.end(); ++it2) {
        BulletPattern* currentPattern = (BulletPattern *)*it2;
        currentPattern->setPlayersReference(this->players);
    }
}

void PatternEditor::setPlayersReference(vector<Player*>* players) {
    this->players = players;
}

void PatternEditor::keyPressed(int key) {
    cout << "key: " << key << endl;
    if (key == 49) {
        this->keys._1 = true;
    } else if (key == 50) {
        this->keys._2 = true;
    } else if (key ==  51) {
        this->keys._3 = true;
    } else if (key == 52) {
        this->keys._4 = true;
    } else if (key == 53) {
        this->keys._5 = true;
    } else if (key == 54) {
        this->keys._6 = true;
    } else if (key == 122) {
        this->keys.z = true;
    }
    if (this->mainMode == kPattern) {
        if (this->keys._1) {
            this->typeString = "Cyclic Ellipse";
        } else if (this->keys._2) {
            this->typeString = "Radial";
        } else if (this->keys._3) {
            this->typeString = "Fan Out";
        } else if (this->keys._4) {
            this->typeString = "Targeted";
        } else if (this->keys._5) {
            this->typeString = "Oscillating Fan Out";
        }
        if (this->editMode == kNormal) {
            if (key == 'c') {
                this->editMode = kCountPending;
            }
        } else if (this->editMode == kCountPending) {
            if (key == 'c') {
                this->editMode = kNormal;
                int count = this->parseBufferedNumber();
                if (this->highlightedPattern != NULL) {
                    this->highlightedPattern->count = count;
                }
            }
            if (key >= 48 && key <= 57) {
                int keyVal = key - 48;
                this->pendingCount.push_back(keyVal);
            }
        }
    } else if (this->mainMode) {
        if (this->keys._1) {
            this->typeString = "Straight Line";
        } else if (this->keys._2) {
            this->typeString = "Bounded Cyclic Straight Line";
        }
    }
    if (key == 'd') {
        this->group->patterns.clear();
    } else if (key == 'w') {
        writer->writeOut("dump.txt", this->group);
    } else if (key == 'm') {
        if (this->mainMode == kPattern) {
            this->mainMode = kMover;
        } else if (this->mainMode == kMover) {
            this->mainMode = kPattern;
        }
    } else if (key == 'p') {
        this->pause();
    }
}

void PatternEditor::keyReleased(int key) {
    if (key == 49) {
        this->keys._1 = false;
        this->typeString = "";
    } else if (key == 50) {
        this->keys._2 = false;
        this->typeString = "";
    } else if (key ==  51) {
        this->keys._3 = false;
        this->typeString = "";
    } else if (key == 52) {
        this->keys._4 = false;
        this->typeString = "";
    } else if (key == 53) {
        this->keys._5 = false;
        this->typeString = "";
    } else if (key == 54) {
        this->keys._6 = false;
        this->typeString = "";
    } else if (key == 122) {
        this->keys.z = false;
    }
}

int PatternEditor::parseBufferedNumber() {
    int count = 0;
    int length = this->pendingCount.size();
    int i = length;
    for(vector<int>::iterator it2 = this->pendingCount.begin(); it2 != this->pendingCount.end(); ++it2) {
        int digit = (int)*it2;
        int factor = pow((float)10, ((float)i-1));
        count += digit*factor;
        --i;
    }
    this->pendingCount.clear();
    return count;
}
