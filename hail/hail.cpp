#include "hail.h"

Hail::Hail() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};

    this->color.r = 212 / 255.0;
    this->color.g = 241 / 255.0;
    this->color.b = 249 / 255.0;
    this->color.a = randomFloat(0.3, 0.8);

    this->gravity = -0.0005;
    this->vel = randomFloat(-0.2, 0.0);
    this->motion_x = randomFloat(-0.005, 0.005);
    this->motion_z = randomFloat(-0.005, 0.005);
    this->rotate_angle = randomInt(0, 360);
    this->rotate_x = randomInt(0, 1);
    this->rotate_y = randomInt(0, 1);
    this->rotate_z = randomInt(0, 1);
    this->shape = randomInt(1, 3) % 3;

    this->life = 1;
    this->fade = randomFloat(0.001, 0.05);

    this->hail_frag = HailFrag(this->color, this->position);
}

void Hail::reset() {
    this->position = Point{randomFloat(randomFloat(-5, 5), randomFloat(40, 50)),
                           randomFloat(25, 30),
                           randomFloat(randomFloat(-5, 5), randomFloat(25, 35))};
    this->color.r = 1.0;
    this->color.g = 1.0;
    this->color.b = 1.0;
    this->color.a = randomFloat(0.5, 1.0);

    this->gravity = -0.0005;
    this->vel = randomFloat(-0.2, 0.0);
    this->motion_x = randomFloat(-0.005, 0.005) + wind_velocity_x;
    this->motion_z = randomFloat(-0.005, 0.005) + wind_velocity_z;

    this->life = 1;
    this->fade = randomFloat(0.001, 0.05);
}

void Hail::draw() {
    if (this->hail_frag.frag_on) {
        this->hail_frag.draw();
    }

    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glRotated(this->rotate_angle, this->rotate_x, this->rotate_y, this->rotate_z);

    switch (this->shape) {
        case 0:
            glScaled(0.3, 0.3, 0.3);
            glutSolidOctahedron();  // 8
            break;
        case 1:
            glScaled(0.15, 0.15, 0.15);
            glutSolidDodecahedron(); // 12
            break;
        case 2:
            glScaled(0.3, 0.3, 0.3);
            glutSolidIcosahedron(); // 20
            break;
        default:
            break;
    }
    glPopMatrix();

    this->update();
}

void Hail::update() {
    this->position.y += this->vel;
    this->position.x += this->motion_x;
    this->position.z += this->motion_z;
    this->vel += this->gravity;

    if (this->position.y <= -10) {
        this->hail_frag.frag_on = true;
        this->hail_frag.frag_time = 1;
        this->hail_frag.position = this->position;
        this->reset();
    }

    this->life -= this->fade;
    if (this->life <= 0) {
        this->reset();
    }
}


HailFrag::HailFrag(Color color_, Point pos_) {
    this->position = pos_;
    this->position.y = -10;
    this->color = color_;

    this->frag_cnt = randomInt(4, 6);
    this->frag_shape = randomInt(1, 3) % 3;

    this->rotate_angle = randomInt(0, 360);
    this->rotate_x = randomInt(0, 1);
    this->rotate_y = randomInt(0, 1);
    this->rotate_z = randomInt(0, 1);

    for (int i = 1; i <= this->frag_cnt; i++) {
        this->frag_attr[i][0] = randomFloat(-0.5, 0.5);
        this->frag_attr[i][1] = randomFloat(-0.2, 0.2);
        this->frag_attr[i][2] = randomFloat(-0.5, 0.5);
        this->frag_attr[i][3] = randomFloat(-0.025, 0.025);
    }
    this->frag_time = 1;
    this->frag_on = false;
}

void HailFrag::draw() {
    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);

    for (int i = 1; i <= frag_cnt; i++) {
        glPushMatrix();
        glTranslatef(this->position.x + this->frag_attr[i][0] * this->frag_time,
                     this->position.y + this->frag_attr[i][1] - 1,
                     this->position.z + this->frag_attr[i][2] * this->frag_time);
        glRotated(this->rotate_angle, this->rotate_x, this->rotate_y, this->rotate_z);

        switch (this->frag_shape) {
            case 0:
                glScaled(0.15 + frag_attr[i][3], 0.15 + frag_attr[i][3], 0.15 + frag_attr[i][3]);
                glutSolidOctahedron();  // 8
                break;
            case 1:
                glScaled(0.075 + frag_attr[i][3], 0.075 + frag_attr[i][3], 0.075 + frag_attr[i][3]);
                glutSolidDodecahedron(); // 12
                break;
            case 2:
                glScaled(0.15 + frag_attr[i][3], 0.15 + frag_attr[i][3], 0.15 + frag_attr[i][3]);
                glutSolidIcosahedron(); // 20
                break;
            default:
                break;
        }
        glPopMatrix();
    }
    this->update();
}

void HailFrag::update() {
    if (this->frag_time < 3.0) {
        this->frag_time += 0.1;
    }
}
