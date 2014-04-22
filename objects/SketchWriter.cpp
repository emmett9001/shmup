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

SketchWriter::SketchWriter() {
    
}

void SketchWriter::writeOut(std::string filename, BulletPatternGroup *group) {
    ofstream out(filename.c_str());
    for(vector<BulletPattern*>::iterator it = group->patterns.begin(); it != group->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        out << current->describe() << endl;
        cout << current->describe() << endl;
        for(vector<Mover *>::iterator it = current->movers.begin(); it != current->movers.end(); it++){
            Mover *mover = (Mover *)*it;
            cout << mover->describe() << endl;
        }
    }
    out.close();
}

void SketchWriter::loadSketch(std::string filename, BulletPatternGroup *group) {
    string line, slug, token, delimiter = ":";
    int i = 0, count, x, y;
    ifstream myfile (filename.c_str());
    ofVec2f origin;
    BulletPattern *pattern;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            i = 0;
            size_t pos = 0;
            while (i != 3) {
                pos = line.find(delimiter);
                token = line.substr(0, pos);
                if (i == 0) {
                    slug = token;
                } else if (i == 1) {
                    istringstream(token.substr(0, token.find(","))) >> x;
                    istringstream(token.substr(token.find(",") + 1, token.length())) >> y;
                    origin = ofVec2f(x, y);
                } else if (i == 2) {
                    istringstream(token) >> count;
                }
                line.erase(0, pos + delimiter.length());
                ++i;
            }
            pattern = (*BulletPatternFactory::creator_map)[slug]();
            pattern->count = count;
            pattern->origin = origin;
            group->addPattern(pattern);
        }
        myfile.close();
    }
}