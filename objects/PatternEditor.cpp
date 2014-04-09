#include "PatternEditor.h"

#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"

#include "BulletPatternGroup.h"

PatternEditor::PatternEditor(BulletPatternGroup *group)
{
    this->group = group;
}

PatternEditor::~PatternEditor()
{
    //dtor
}

void PatternEditor::draw() {
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("test", 100, 100, 0);
}

void PatternEditor::mouseReleased(int x, int y, int button){
    this->group->addPattern(new CyclicEllipseBulletPattern(30, ofVec2f(x, y), 7, .3));
}

void PatternEditor::keyPressed(int key) {
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
    }
}

void PatternEditor::keyReleased(int key) {
    if (key == 49) {
        this->keys._1 = false;
    } else if (key == 50) {
        this->keys._2 = false;
    } else if (key ==  51) {
        this->keys._3 = false;
    } else if (key == 52) {
        this->keys._4 = false;
    } else if (key == 53) {
        this->keys._5 = false;
    } else if (key == 54) {
        this->keys._6 = false;
    }
}
