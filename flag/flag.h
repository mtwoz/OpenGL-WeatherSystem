#pragma once

#include "vec3.h"
#include "utilities.h"

#define DAMPING 0.01
#define TIME_STEPSIZE2 (0.5*0.5)
#define SPRING_ITERATIONS 15

class Particle {
public:
    explicit Particle(Vec3 po);

    Particle() = default;

    void addForce(Vec3 f);

    //Verlet integration
    void timeStep();

    Vec3 &getPos();


    void offsetPos(Vec3 v);

    void makeUnmovable();

    void addToNormal(Vec3 normal);

    Vec3 &getNormal();

    void resetNormal();

private:
    bool movable{}; //Used to fix points on the cloth

    float mass{};   // Particle of each particle
    Vec3 pos;     // Current position
    Vec3 old_pos; // Previous position
    Vec3 acceleration; // Acceleration due to forces acting
    Vec3 accumulated_normal; // Non-normalized
};

class Spring {
public:
    Particle *p1, *p2;

    Spring(Particle *pi, Particle *pj);

    //Calculating constraint between 2 particles, and offset
    void satisfySpring() const;

private:
    float rest_distance; // rest length of spring
};

class Cloth {
public:

    Cloth(float w, float h, int num_particles_w, int num_particles_h);

    //Colored in the form of a triangular mesh
    void drawShaded();

    //Function that progresses timestep
    void timeStep();

    //Add gravitational force
    void addForce(Vec3 direction);

    void windForce(Vec3 direction);

private:
    int num_particles_width;
    int num_particles_height;

    std::vector<Particle> particles;
    std::vector<Spring> springs;

    Particle *getParticle(int x, int y);

    void makeSpring(Particle *p1, Particle *p2);

    //Calculate normal for forces acting on a triangle formed by p1, p2 and p3
    static Vec3 calcNormal(Particle *p1, Particle *p2, Particle *p3);

    //Calc wind force acting a triangle of particles
    static void addForces3D(Particle *p1, Particle *p2, Particle *p3, const Vec3 direction);

    //Draw the triangle. Called in drawShade() function
    static void drawTriangle(Particle *p1, Particle *p2, Particle *p3, Vec3 color);
};

class Flag {
public:
    Flag() = default;

    ~Flag() = default;

    static void draw();

private:
};