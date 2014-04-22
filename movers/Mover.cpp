#include "Mover.h"
#include "BulletPattern.h"

Mover::Mover()
{
    this->init(NULL, ofVec2f(0, 0), -1);
}

Mover::Mover(ofVec2f direction, float wavelength)
{
    this->init(NULL, direction, wavelength);
}

Mover::Mover(BulletPattern *attached, ofVec2f direction, float wavelength) {
    this->init(attached, direction, wavelength);
}

void Mover::init(BulletPattern *attached, ofVec2f direction, float wavelength) {
    this->duration = -1;
    this->length = -1;
    this->direction = direction;
    this->wavelength = wavelength;
    this->paused = false;
    this->step = 0;
    this->next = NULL;
    this->attach(attached);
}

void Mover::attach(BulletPattern *host) {
    this->attached = host;
    if (this->attached != NULL) {
        this->origin = this->attached->origin;
    }
}

void Mover::update(float timedelta) {
    this->step++;
    if (this->step == this->length) {
        this->paused = true;
    }
    if (!this->paused) {
        this->move(timedelta);
    }
}

string Mover::_describe(string slug) {
    ostringstream stream;
    stream << slug << ":" << this->origin.x << "," << this->origin.y;
    stream << ":" << this->direction.x << "," << this->direction.y;
    stream << ":" << this->wavelength;
    return stream.str();
}
