#pragma once

#include "ofMain.h"
#include "GameObject.h"
#include "BoardQuadrant.h"
#include "ofxGamepadHandler.h"

class testApp : public ofBaseApp, public BoardQuadrantCollisionDelegate {
	public:
		void setup();
		void update();
		void draw();
        void collided(GameObject *obj);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void axisChanged(ofxGamepadAxisEvent &e);
        void buttonPressed(ofxGamepadButtonEvent &e);
        void buttonReleased(ofxGamepadButtonEvent &e);
};
