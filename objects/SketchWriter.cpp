//
//  SketchWriter.cpp
//  emptyExample
//
//  Created by Emmett Butler on 4/21/14.
//
//

#include "SketchWriter.h"

#include "BulletPattern.h"
#include "Stage.h"
#include "Mover.h"
#include "BulletPatternGroup.h"
#include "CyclicBoundedStraightLineMover.h"
#include "Marker.h"

SketchWriter::SketchWriter() {

}

void SketchWriter::writeOut(std::string filename, Stage *stage) {
    ofstream out(filename.c_str());
    for(vector<BulletPattern*>::iterator it = stage->group->patterns.begin(); it != stage->group->patterns.end(); ++it) {
        cout << "# pattern" << endl;
        out << "# pattern" << endl;
        BulletPattern* current = (BulletPattern *)*it;
        out << current->describe();
        cout << current->describe();
    }
    for(vector<StageMarker *>::iterator it = stage->markers.begin(); it != stage->markers.end(); ++it) {
        cout << "# marker" << endl;
        out << "# marker" << endl;
        StageMarker* current = (StageMarker *)*it;
        cout << current->describe();
        out << current->describe();
    }
    out.close();
}

void SketchWriter::loadSketch(std::string filename, Stage *stage) {
    string line, slug, token, delimiter = ":";
    int i = 0, count;
    float wavelength, volley_timeout;
    ifstream myfile (filename.c_str());
    bool inPattern = false, inMarker = false;
    bool patternStart = false, markerStart = false;
    ofVec2f origin, direction;
    BulletPattern *pattern = NULL;
    Mover *mover = NULL;
    StageMarker *marker = NULL;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            i = 0;
            size_t pos = 0;
            if (line.find("#") == 0) {
                // separator line
                if (pattern != NULL) {
                    stage->addPattern(pattern);
                    pattern = NULL;
                    mover = NULL;
                }
                if (marker != NULL) {
                    stage->addMarker(marker);
                    marker = NULL;
                }
                inPattern = false;
                inMarker = false;
                if (line.find("pattern") > 0 && line.find("pattern") < 200) {
                    patternStart = true;
                } else if (line.find("marker") > 0 && line.find("marker") < 200) {
                    markerStart = true;
                }
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
                } else if (inMarker) {
                    // any additions to markers will go here
                } else {
                    // pattern or marker line
                    if (patternStart) {
                        patternStart = false;
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
                    } else if (markerStart) {
                        markerStart = false;
                        inMarker = true;
                        while (i != 2) {
                            pos = line.find(delimiter);
                            token = line.substr(0, pos);
                            if (i == 0) {
                                slug = token;
                            } else if (i == 1) {
                                origin = this->parseCoordinates(token);
                            }
                            line.erase(0, pos + delimiter.length());
                            ++i;
                        }
                        marker = (StageMarker *)(*SerializableFactory::creator_map)[slug]();
                        marker->origin = origin;
                    }
                }
            }
        }
        if (pattern != NULL) {
            stage->addPattern(pattern);
        }
        if (marker != NULL) {
            stage->addMarker(marker);
        }
        stage->prepare();
        pattern = NULL;
        mover = NULL;
        marker = NULL;
        myfile.close();
    }
}

ofVec2f SketchWriter::parseCoordinates(std::string token) {
    float _x = ::atof(token.substr(0, token.find(",")).c_str());
    float _y = ::atof(token.substr(token.find(",") + 1, token.length()).c_str());
    return ofVec2f(_x, _y);
}
