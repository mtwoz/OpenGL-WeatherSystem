#include "snow.h"

Snow::Snow() {
    this->position = Point{(float) (rand() % 21) - 10,
                           10.0,
                           (float) (rand() % 21) - 10};

    this->color[0] = 1;
    this->color[1] = 1;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.5, 1.0);

    this->vel = 0.0;
    this->gravity = -0.8;

    this->alive = true;
    this->life = 1.0;
    this->fade = float(rand() % 100) / 1000.0f + 0.003f;
}

void Snow::reset() {
    this->position = Point{(float) (rand() % 21) - 10,
                           10.0,
                           (float) (rand() % 21) - 10};

    this->vel = 0.0;
    this->gravity = -0.8;
    this->alive = true;
    this->life = 1.0;
    this->fade = float(rand() % 100) / 1000.0f + 0.003f;
}

void Snow::draw() {
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, this->position.z - 40);
    glutSolidSphere(0.2, 16, 16);
    glPopMatrix();
}

void Snow::update() {
    this->position.y += this->vel / 100;
    this->vel += this->gravity;
    this->life -= this->fade;

    if (this->life < 0.0) {
        this->reset();
    }
}
