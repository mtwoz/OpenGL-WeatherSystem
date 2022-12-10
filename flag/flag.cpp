#include "flag.h"

Cloth cloth(15, 10, 10, 5);

Particle::Particle(Vec3 po) {
    this->pos = po;
    this->old_pos = po;
    this->acceleration = Vec3(0, 0, 0);
    this->mass = 1;
    this->movable = true;
    this->accumulated_normal = Vec3(0, 0, 0);
}

void Particle::addForce(Vec3 f) {
    this->acceleration += f / this->mass;
}

void Particle::timeStep() {
    if (this->movable) {
        Vec3 temp = this->pos;
        this->pos = this->pos + (this->pos - this->old_pos) * (1.0 - DAMPING) + this->acceleration * TIME_STEPSIZE2;
        this->old_pos = temp;
        this->acceleration = Vec3(0, 0, 0); // Reseting acceleration for each time step
    }
}

Vec3 &Particle::getPos() {
    return this->pos;
}

void Particle::offsetPos(const Vec3 v) {
    if (this->movable) pos += v;
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

Spring::Spring(Particle *pi, Particle *pj) {
    this->p1 = pi;
    this->p2 = pj;
    Vec3 vec = p1->getPos() - p2->getPos();
    this->rest_distance = vec.length();
}

void Spring::satisfySpring() const {
    Vec3 p1_to_p2 = this->p2->getPos() - this->p1->getPos();
    float current_distance = p1_to_p2.length();
    Vec3 correctionVector = p1_to_p2 * (1 - this->rest_distance / current_distance) *
                            0.5; // The offset vector that moves p1 into a distance of rest_distance to p2
    Vec3 correctionVectorHalf = correctionVector * 0.5;
    this->p1->offsetPos(correctionVectorHalf);
    this->p2->offsetPos(-correctionVectorHalf);
}

Cloth::Cloth(float w, float h, int num_particles_w, int num_particles_h) {
    this->num_particles_width = num_particles_w;
    this->num_particles_height = num_particles_h;

    this->particles.resize(this->num_particles_width * this->num_particles_height);

    // creating particles in a grid of particles from (0,0,0) to (w,-h,0)
    for (int x = 0; x < this->num_particles_width; x++) {
        for (int y = 0; y < this->num_particles_height; y++) {
            Vec3 pos = Vec3(w * ((float) x / (float) this->num_particles_width),
                            -h * ((float) y / (float) this->num_particles_height),
                            0);
            this->particles[y * this->num_particles_width + x] = Particle(
                    pos); // insert particle in column x at y'th row
        }
    }

    // Connecting immediate neighbor particles with springs (distance 1 )
    for (int x = 0; x < this->num_particles_width; x++) {
        for (int y = 0; y < this->num_particles_height; y++) {
            if (x < this->num_particles_width - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 1, y));
            if (y < this->num_particles_height - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x, y + 1));
            if (x < this->num_particles_width - 1 && y < this->num_particles_height - 1)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 1, y + 1));
            if (x < this->num_particles_width - 1 && y < this->num_particles_height - 1)
                this->makeSpring(this->getParticle(x + 1, y), this->getParticle(x, y + 1));
        }
    }

    // Connecting 2nd neighbors with springs (distance 2 )
    for (int x = 0; x < this->num_particles_width; x++) {
        for (int y = 0; y < this->num_particles_height; y++) {
            if (x < this->num_particles_width - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 2, y));
            if (y < this->num_particles_height - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x, y + 2));
            if (x < this->num_particles_width - 2 && y < this->num_particles_height - 2)
                this->makeSpring(this->getParticle(x, y), this->getParticle(x + 2, y + 2));
            if (x < this->num_particles_width - 2 && y < this->num_particles_height - 2)
                this->makeSpring(this->getParticle(x + 2, y), this->getParticle(x, y + 2));
        }
    }

    // making the upper left most three and bottom most three particles unmovable
    for (int i = 0; i < 3; i++) {
        this->getParticle(0 + i, 0)->offsetPos(
                Vec3(0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural
        this->getParticle(0 + i, 0)->makeUnmovable();

        this->getParticle(0 + i, 0)->offsetPos(
                Vec3(-0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural
        this->getParticle(0, this->num_particles_height - 1 - i)->makeUnmovable();
    }
}

void Cloth::drawShaded() {
    // reset normals (which where written to last frame)
    std::vector<Particle>::iterator particle;
    for (particle = this->particles.begin(); particle != this->particles.end(); particle++) {
        (*particle).resetNormal();
    }

    //create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
    for (int x = 0; x < this->num_particles_width - 1; x++) {
        for (int y = 0; y < this->num_particles_height - 1; y++) {
            //Calculating triangle normal for triangle and adding to all particles
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

    //Drawing the flag
    for (int y = 0; y < this->num_particles_height - 1; y++) {
        for (int x = 0; x < this->num_particles_width - 1; x++) {
            Vec3 color(1, 1, 1);

            glBegin(GL_TRIANGLES);
            drawTriangle(this->getParticle(x, y + 1), this->getParticle(x, y), this->getParticle(x + 1, y), color);
            drawTriangle(this->getParticle(x + 1, y + 1), this->getParticle(x, y + 1), this->getParticle(x + 1, y),
                         color);
            glEnd();
        }
    }
}

void Cloth::timeStep() {
    std::vector<Spring>::iterator ic;
    // iterate over all springs several times
    for (int i = 0; i < SPRING_ITERATIONS; i++) {
        for (ic = this->springs.begin(); ic != this->springs.end(); ic++) {
            (*ic).satisfySpring(); // satisfy constraint.
        }
    }

    std::vector<Particle>::iterator particle;
    for (particle = this->particles.begin(); particle != this->particles.end(); particle++) {
        (*particle).timeStep(); // calculate the position of each particle at the next time step.
    }
}

void Cloth::addForce(const Vec3 direction) {
    std::vector<Particle>::iterator particle;
    for (particle = this->particles.begin(); particle != this->particles.end(); particle++) {
        (*particle).addForce(direction); // add the forces to each particle
    }
}

void Cloth::windForce(const Vec3 direction) {
    for (int x = 0; x < this->num_particles_width - 1; x++) {
        for (int y = 0; y < this->num_particles_height - 1; y++) {
            addForces3D(this->getParticle(x + 1, y), this->getParticle(x, y), this->getParticle(x, y + 1), direction);
            addForces3D(this->getParticle(x + 1, y + 1), this->getParticle(x + 1, y), this->getParticle(x, y + 1),
                        direction);
        }
    }
}

Particle *Cloth::getParticle(int x, int y) {
    return &particles[y * this->num_particles_width + x];
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
    cloth.windForce(Vec3(0.5, 0.1, 0.2) * TIME_STEPSIZE2);
    cloth.timeStep();

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(22.52, 10, 12.955); // move camera out and center on the cloth
    glScaled(0.2, 0.2, 0.2);
    cloth.drawShaded(); // finally draw the cloth with smooth shading

    glColor3f(0.875, 0.875, 0.875);
    glutSolidSphere(0.3, 50, 50);
    GLUquadricObj *quadratic;
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.1f, 0.1f, 19.0f, 32, 32);
    glPopMatrix();
}