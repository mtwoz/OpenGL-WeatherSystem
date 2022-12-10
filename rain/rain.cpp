#include "rain.h"

Rain::Rain() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           25.0,
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};

    this->color[0] = 0.5;
    this->color[1] = 0.5;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->fade = randomFloat(0.001, 0.05);
    this->radius = 0;
    this->on_ground = false;
}

void Rain::reset() {
    this->position = Point{randomFloat(0, 44),
                           25.0,
                           randomFloat(0, 28)};
    this->color[0] = 0.5;
    this->color[1] = 0.5;
    this->color[2] = 1.0;
    this->color[3] = randomFloat(0.1, 1.0);

    this->vel = 0.0;
    this->life = 1.0;
    this->gravity = -0.0005;
    this->fade = randomFloat(0.001, 0.05);
    this->radius = 0;
    this->on_ground = false;
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
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);
    glBegin(GL_LINES);
    glVertex3f(this->position.x, this->position.y, this->position.z);
    glVertex3f(this->position.x, this->position.y + 0.25f, this->position.z);
    glEnd();

    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3] - 0.5f);
    glBegin(GL_LINES);
    glVertex3f(this->position.x, this->position.y + 0.25, this->position.z);
    glVertex3f(this->position.x, this->position.y + 0.5f, this->position.z);
    glEnd();
}

void Rain::draw_ripple() {
    glPushMatrix();

    glTranslatef(this->position.x, this->position.y, this->position.z);
    glRotated(90, 1, 0, 0);
    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3]);

    if (this->radius <= 1.2) {
        glBegin(GL_POINTS);
        for (float i = -M_PI; i <= M_PI; i += 0.001)
            glVertex2f((sinf(i) * this->radius), (cosf(i) * this->radius));
        glEnd();
    }

    glColor4f(this->color[0], this->color[1], this->color[2], this->color[3] + 0.5f);
    if (this->radius >= 0.8 && this->radius <= 2.0) {
        glBegin(GL_POINTS);
        for (float i = -M_PI; i <= M_PI; i += 0.001)
            glVertex2f((sinf(i) * (this->radius - 1)), (cosf(i) * (this->radius - 1)));
        glEnd();
    }

    glLoadIdentity();
    glPopMatrix();
}

void Rain::update_sky() {
    if (this->position.y <= -10) {
        this->on_ground = true;
    }

    this->position.y += this->vel;
    this->vel += this->gravity;
    this->life -= this->fade;

    if (this->life < 0.0) {
        this->reset();
    }
}

void Rain::update_ground() {
    this->radius += 0.01;
    this->color[3] -= 0.005;

    if (this->radius >= 2.0) {
        this->reset();
    }
}
