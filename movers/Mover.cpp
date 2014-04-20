#include "Mover.h"
#include "BulletPattern.h"

Mover::Mover()
{
    this->init(NULL);
}

Mover::Mover(BulletPattern *attached) {
    this->init(attached);
}

void Mover::init(BulletPattern *attached) {
    this->duration = -1;
    this->length = -1;
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
