#include "flag.h"

Cloth cloth(15, 10, 10, 5);

Particle::Particle(Vec3 pos_) {
    this->pos = pos_;
    this->pre_pos = pos_;
    this->mass = 1;
    this->movable = true;
    this->acceleration = Vec3(0, 0, 0);
    this->accumulated_normal = Vec3(0, 0, 0);
}

void Particle::addForce(Vec3 force) {
    this->acceleration += force / this->mass;
}

void Particle::update() {
    if (this->movable) {
        Vec3 pos_ = this->pos;
        this->pos = this->pos + (this->pos - this->pre_pos) * (1.0 - Resistance) + this->acceleration * TIME2;
        this->pre_pos = pos_;
        this->acceleration = Vec3(0, 0, 0);
    }
}

Vec3 &Particle::getPos() {
    return this->pos;
}

void Particle::offsetPos(const Vec3 vec) {
    if (this->movable) {
        this->pos += vec;
    }
}

void Particle::makeUnmovable() {
    this->movable = false;
}

void Particle::addToNormal(Vec3 normal) {
    this->accumulated_normal += normal.normalized();
}

Vec3 &Particle::getNormal() {
    return this->accumulated_normal;
}

void Particle::resetNormal() {
    this->accumulated_normal = Vec3(0, 0, 0);
}

Spring::Spring(Particle *p1_, Particle *p2_) {
    this->p1 = p1_;
    this->p2 = p2_;
    Vec3 vec = p1->getPos() - p2->getPos();
    this->rest_distance = vec.length();
}

void Spring::satisfySpring() const {
    Vec3 p1_to_p2 = this->p2->getPos() - this->p1->getPos();
    float current_distance = p1_to_p2.length();
    Vec3 correction_vec = p1_to_p2 * (1 - this->rest_distance / current_distance) * 0.5;
    Vec3 correction_vec_half = correction_vec * 0.5;
    this->p1->offsetPos(correction_vec_half);
    this->p2->offsetPos(-correction_vec_half);
}

Cloth::Cloth(float w, float h, int particles_w, int particles_h) {
    this->num_particles_w = particles_w;
    this->num_particles_h = particles_h;

    this->particles.resize(this->num_particles_w * this->num_particles_h);

    // creating particles
    for (int x = 0; x < this->num_particles_w; x++) {
        for (int y = 0; y < this->num_particles_h; y++) {
            Vec3 pos = Vec3(w * ((float) x / (float) this->num_particles_w),
                            -h * ((float) y / (float) this->num_particles_h),
                            0);
            this->particles[y * this->num_particles_w + x] = Particle(pos);
        }
    }

    for (int x = 0; x < this->num_particles_w; x++) {
        for (int y = 0; y < this->num_particles_h; y++) {
            if (x < this->num_particles_w - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 1, y));
            if (y < this->num_particles_h - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x, y + 1));
            if (x < this->num_particles_w - 1 && y < this->num_particles_h - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 1, y + 1));
            if (x < this->num_particles_w - 1 && y < this->num_particles_h - 1)
                this->makeSpring(this->getParticle(x + 1, y), this->getParticle(x, y + 1));
        }
    }

    for (int x = 0; x < this->num_particles_w; x++) {
        for (int y = 0; y < this->num_particles_h; y++) {
            if (x < this->num_particles_w - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 2, y));
            if (y < this->num_particles_h - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x, y + 2));
            if (x < this->num_particles_w - 2 && y < this->num_particles_h - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 2, y + 2));
            if (x < this->num_particles_w - 2 && y < this->num_particles_h - 2)
                this->makeSpring(this->getParticle(x + 2, y), this->getParticle(x, y + 2));
        }
    }

    // fix some corners
    for (int i = 0; i < 3; i++) {
        this->getParticle(0 + i, 0)->offsetPos(Vec3(0.5, 0.0, 0.0));
        this->getParticle(0 + i, 0)->makeUnmovable();

        this->getParticle(0 + i, 0)->offsetPos(Vec3(-0.5, 0.0, 0.0));
        this->getParticle(0, this->num_particles_h - 1 - i)->makeUnmovable();
    }
}

void Cloth::draw() {
    for (auto &particle: this->particles) {
        particle.resetNormal();
    }

    // initial particle normals
    for (int x = 0; x < this->num_particles_w - 1; x++) {
        for (int y = 0; y < this->num_particles_h - 1; y++) {
            Vec3 normal = calcNormal(this->getParticle(x + 1, y), this->getParticle(x, y), this->getParticle(x, y + 1));
            this->getParticle(x + 1, y)->addToNormal(normal);
            this->getParticle(x, y)->addToNormal(normal);
            this->getParticle(x, y + 1)->addToNormal(normal);

            normal = calcNormal(this->getParticle(x + 1, y + 1), this->getParticle(x + 1, y),
                                this->getParticle(x, y + 1));
            this->getParticle(x + 1, y + 1)->addToNormal(normal);
            this->getParticle(x + 1, y)->addToNormal(normal);
            this->getParticle(x, y + 1)->addToNormal(normal);
        }
    }

    // draw the flag
    for (int y = 0; y < this->num_particles_h - 1; y++) {
        for (int x = 0; x < this->num_particles_w - 1; x++) {
            Vec3 color(1, 1, 1);

            glBegin(GL_TRIANGLES);
            drawTriangle(this->getParticle(x, y + 1), this->getParticle(x, y), this->getParticle(x + 1, y), color);
            drawTriangle(this->getParticle(x + 1, y + 1), this->getParticle(x, y + 1), this->getParticle(x + 1, y),
                         color);
            glEnd();
        }
    }
}

void Cloth::update() {
    // iterate over all springs several times
    for (int i = 0; i < SPRING_ITERATIONS; i++) {
        for (auto &spring: this->springs) {
            spring.satisfySpring();
        }
    }

    for (auto &particle: this->particles) {
        particle.update();
    }
}

void Cloth::addForce(const Vec3 direction) {
    for (auto &particle: this->particles) {
        particle.addForce(direction);
    }
}

void Cloth::addWindForce(Vec3 direction) {
    for (int x = 0; x < this->num_particles_w - 1; x++) {
        for (int y = 0; y < this->num_particles_h - 1; y++) {
            addForces3D(this->getParticle(x + 1, y), this->getParticle(x, y), this->getParticle(x, y + 1), direction);
            addForces3D(this->getParticle(x + 1, y + 1), this->getParticle(x + 1, y), this->getParticle(x, y + 1),
                        direction);
        }
    }
}

Particle *Cloth::getParticle(int x, int y) {
    return &particles[y * this->num_particles_w + x];
}

void Cloth::makeSpring(Particle *p1, Particle *p2) {
    this->springs.emplace_back(p1, p2);
}

Vec3 Cloth::calcNormal(Particle *p1, Particle *p2, Particle *p3) {
    Vec3 pos1 = p1->getPos();
    Vec3 pos2 = p2->getPos();
    Vec3 pos3 = p3->getPos();

    Vec3 v1 = pos2 - pos1;
    Vec3 v2 = pos3 - pos1;

    return v1.cross(v2);
}

void Cloth::addForces3D(Particle *p1, Particle *p2, Particle *p3, const Vec3 direction) {
    Vec3 normal = calcNormal(p1, p2, p3);
    Vec3 d = normal.normalized();
    Vec3 force = normal * (d.dot(direction));
    p1->addForce(force);
    p2->addForce(force);
    p3->addForce(force);
}

void Cloth::drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vec3 color) {
    glColor3fv((float *) &color);

    Vec3 normal1 = p1->getNormal().normalized();
    Vec3 normal2 = p2->getNormal().normalized();
    Vec3 normal3 = p3->getNormal().normalized();

    glNormal3fv((float *) &(normal1));
    glVertex3fv((float *) &(p1->getPos()));

    glNormal3fv((float *) &(normal2));
    glVertex3fv((float *) &(p2->getPos()));

    glNormal3fv((float *) &(normal3));
    glVertex3fv((float *) &(p3->getPos()));
}

void Flag::draw() {
    cloth.addWindForce(Vec3(0.01, 0.01, 0.01) * TIME2);
    cloth.update();

    glPushMatrix();
    glTranslatef(22.52, 10, 12.955);
    glRotatef((float)flag_angle, 0.0f, 1.0f, 0.0f);
    glScaled(0.2, 0.2, 0.2);
    cloth.draw();

    glColor3f(0.875, 0.875, 0.875);
    glutSolidSphere(0.3, 50, 50);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 0.1f, 0.1f, 19.0f, 32, 32);
    glPopMatrix();
}