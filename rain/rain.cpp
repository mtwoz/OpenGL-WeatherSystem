#include "rain.h"

Rain::Rain() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};

    this->color[0] = 0.5;
    this->color[1] = 0.5;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->radius = 0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->vel = randomFloat(-0.2, 0.0);
    this->fade = randomFloat(0.001, 0.05);
    this->motion_x = randomFloat(-0.01, 0.01);
    this->motion_z = randomFloat(-0.01, 0.01);
    this->on_ground = false;
}

void Rain::reset() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};
    this->color[0] = 0.5;
    this->color[1] = 0.5;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->radius = 0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->on_ground = false;

    this->vel = randomFloat(-0.2, 0.0);
    this->fade = randomFloat(0.001, 0.05);
    this->motion_x = randomFloat(-0.005, 0.005) + wind_velocity_x;
    this->motion_z = randomFloat(-0.005, 0.005) + wind_velocity_z;

}

void Rain::draw() {
    if (this->on_ground) {
        this->draw_ripple();
        this->update_ground();
    } else {
        this->draw_drop();
        this->update_sky();
    }
}

void Rain::draw_drop() {
    glPushMatrix();
    glLineWidth(1);
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);
    glBegin(GL_LINES);
    glVertex3f(this->position.x, this->position.y, this->position.z);
    glVertex3f(this->position.x, this->position.y + 0.25f, this->position.z);
    glEnd();

    glLineWidth(0.5);
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3] - 0.5f);
    glBegin(GL_LINES);
    glVertex3f(this->position.x, this->position.y + 0.25f, this->position.z);
    glVertex3f(this->position.x, this->position.y + 0.5f, this->position.z);
    glEnd();
    glPopMatrix();
}

void Rain::draw_ripple() {
    if (this->position.x >= 20 && this->position.x <= 25 && this->position.z >= 9 && this->position.z <= 16) {
        return;
    }

    glPushMatrix();

    glTranslatef(this->position.x, this->position.y, this->position.z);
    glRotated(90, 1, 0, 0);
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);

    if (this->radius <= 1.2) {
        glBegin(GL_POINTS);
        for (float i = 0; i <= TWO_PI; i += 0.05)
            glVertex2f((sinf(i) * this->radius), (cosf(i) * this->radius));
        glEnd();
    }

    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3] + 0.5f);
    if (this->radius >= 0.8 && this->radius <= 2.0) {
        glBegin(GL_POINTS);
        for (float i = 0; i <= TWO_PI; i += 0.05)
            glVertex2f((sinf(i) * (this->radius - 1)), (cosf(i) * (this->radius - 1)));
        glEnd();
    }

    glPopMatrix();
}

void Rain::update_sky() {
    if (this->position.y <= -10) {
        this->on_ground = true;
    }

    this->position.y += this->vel;
    this->position.x += this->motion_x;
    this->position.z += this->motion_z;
    this->vel += this->gravity;
    this->life -= this->fade;

    if (this->life < 0.0) {
        this->reset();
    }
}

void Rain::update_ground() {
    this->radius += 0.01;
    this->color[3] -= 0.005;

    if (this->radius >= 2.0 || this->color[3] <= -0.5) {
        this->reset();
    }
}
