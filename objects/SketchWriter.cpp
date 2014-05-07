//
//  SketchWriter.cpp
//  emptyExample
//
//  Created by Emmett Butler on 4/21/14.
//
//

#include "SketchWriter.h"

#include "BulletPattern.h"
#include "Mover.h"
#include "BulletPatternGroup.h"
#include "CyclicBoundedStraightLineMover.h"

SketchWriter::SketchWriter() {

}

void SketchWriter::writeOut(std::string filename, BulletPatternGroup *group) {
    ofstream out(filename.c_str());
    for(vector<BulletPattern*>::iterator it = group->patterns.begin(); it != group->patterns.end(); ++it) {
        cout << "#" << endl;
        out << "#" << endl;
        BulletPattern* current = (BulletPattern *)*it;
        out << current->describe();
        cout << current->describe();
    }
    out.close();
}

void SketchWriter::loadSketch(std::string filename, BulletPatternGroup *group) {
    string line, slug, token, delimiter = ":";
    int i = 0, count;
    float wavelength, volley_timeout;
    ifstream myfile (filename.c_str());
    bool inPattern = false;
    ofVec2f origin, direction;
    BulletPattern *pattern = NULL;
    Mover *mover = NULL;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            i = 0;
            size_t pos = 0;
            if (line.find("#") == 0) {
                // separator line
                if (pattern != NULL) {
                    group->addPattern(pattern);
                    pattern = NULL;
                    mover = NULL;
                }
                inPattern = false;
            } else {
                if (inPattern) {
                    // mover line
                    while (i != 4) {
                        pos = line.find(delimiter);
                        token = line.substr(0, pos);
                        if (i == 0) {
                            slug = token;
                        } else if (i == 1) {
                            origin = this->parseCoordinates(token);
                        } else if (i == 2) {
                            direction = this->parseCoordinates(token);
                        } else if (i == 3) {
                            wavelength = ::atof(token.substr(0, token.length()).c_str());
                        }
                        line.erase(0, pos + delimiter.length());
                        ++i;
                    }
                    mover = (Mover *)(*SerializableFactory::creator_map)[slug]();
                    mover->origin = origin;
                    mover->direction = direction;
                    mover->wavelength = wavelength;
                    if (pattern != NULL) {
                        pattern->addMover(mover);
                    }
                } else {
                    // pattern line
                    inPattern = true;
                    while (i != 4) {
                        pos = line.find(delimiter);
                        token = line.substr(0, pos);
                        if (i == 0) {
                            slug = token;
                        } else if (i == 1) {
                            origin = this->parseCoordinates(token);
                        } else if (i == 2) {
                            count = ::atof(token.c_str());
                        } else if (i == 3) {
                            volley_timeout = ::atof(token.c_str());
                        }
                        line.erase(0, pos + delimiter.length());
                        ++i;
                    }
                    pattern = (BulletPattern *)(*SerializableFactory::creator_map)[slug]();
                    pattern->count = count;
                    pattern->origin = origin;
                    pattern->volley_timeout = volley_timeout;
                }
            }
        }
        if (pattern != NULL) {
            group->addPattern(pattern);
        }
        group->prepare();
        pattern = NULL;
        mover = NULL;
        myfile.close();
    }
}

ofVec2f SketchWriter::parseCoordinates(std::string token) {
    float _x = ::atof(token.substr(0, token.find(",")).c_str());
    float _y = ::atof(token.substr(token.find(",") + 1, token.length()).c_str());
    return ofVec2f(_x, _y);
}
