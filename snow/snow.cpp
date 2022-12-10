#include "snow.h"

Snow::Snow() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           25.0,
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};

    this->color[0] = 1;
    this->color[1] = 1;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->fade = randomFloat(0.001, 0.05);
    this->on_ground = false;

    if (randomInt(0, 10) % 2 == 0)
        motion_x = -randomFloat(0, 1) / 20;
    else
        motion_x = randomFloat(0, 1) / 50;

    if (randomInt(0, 10) % 2 == 0)
        motion_z = -randomFloat(0, 1) / 20;
    else
        motion_z = randomFloat(0, 1) / 50;
}

void Snow::reset() {
    this->position = Point{randomFloat(0, 44),
                           25.0,
                           randomFloat(0, 28)};
    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->fade = randomFloat(0.001, 0.05);
    this->on_ground = false;
}

void Snow::draw() {
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glutSolidSphere(0.05, 16, 16);
    glPopMatrix();

    this->update();
}

void Snow::update() {
    if (this->position.y <= -10) {
        this->on_ground = true;
    }

    if (this->on_ground) {
        this->life -= this->fade;
        this->color[3] -= 0.005;
    } else {
        this->position.y += this->vel;
        this->position.x += this->motion_x;
        this->position.z += this->motion_z;
        this->vel += this->gravity;
        this->life -= this->fade;
    }

    if (this->life < 0.0 || this->color[3] <= 0.0) {
        this->reset();
    }
}
