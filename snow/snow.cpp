#include "snow.h"

Snow::Snow() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};

    this->color[0] = 1.0;
    this->color[1] = 1.0;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->fade = randomFloat(0.001, 0.05);
    this->on_ground = false;

    if (randomBool())
        motion_x = -randomFloat(0, 0.05);
    else
        motion_x = randomFloat(0, 0.05);

    if (randomBool())
        motion_z = -randomFloat(0, 0.05);
    else
        motion_z = randomFloat(0, 0.05);
}

void Snow::reset() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};
    this->color[0] = 1.0;
    this->color[1] = 1.0;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->on_ground = false;

    this->fade = randomFloat(0.001, 0.05);
    this->motion_x = randomFloat(-0.05, 0.05) + wind_velocity_x;
    this->motion_z = randomFloat(-0.05, 0.05) + wind_velocity_z;
}

void Snow::draw() {
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glutSolidSphere(0.08, 16, 16);
    glPopMatrix();

    this->update();
}

void Snow::update() {
    if (this->position.y <= -10) {
        this->on_ground = true;
    }

    this->life -= this->fade;
    if (this->on_ground) {
        this->color[3] -= 0.002;
        if (this->color[3] <= 0.0) {
            this->reset();
        }
    } else {
        this->position.y += this->vel;
        this->position.x += this->motion_x;
        this->position.z += this->motion_z;
        this->vel += this->gravity;
        if (this->life <= 0.0) {
            this->reset();
        }
    }
}
