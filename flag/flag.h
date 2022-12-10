#pragma once

#include "vec3.h"
#include "utilities.h"

#define DAMPING 0.02
#define TIME2 (0.5*0.5)
#define SPRING_ITERATIONS 15

class Particle {
public:
    explicit Particle(Vec3 pos_);

    Particle() = default;

    void addForce(Vec3 force);

    //Verlet integration
    void update();

    Vec3 &getPos();


    void offsetPos(Vec3 v);

    void makeUnmovable();

    void addToNormal(Vec3 normal);

    Vec3 &getNormal();

    void resetNormal();

private:
    bool movable{};

    float mass{};
    Vec3 pos;
    Vec3 pre_pos;
    Vec3 acceleration;
    Vec3 accumulated_normal;
};

class Spring {
public:
    Particle *p1, *p2;

    Spring(Particle *p1_, Particle *p2_);

    void satisfySpring() const;

private:
    float rest_distance; // rest length of spring
};

class Cloth {
public:

    Cloth(float w, float h, int particles_w, int particles_h);

    //Colored in the form of a triangular mesh
    void draw();

    //Function that progresses timestep
    void update();

    //Add gravitational force
    void addForce(Vec3 direction);

    void addWindForce(Vec3 direction);

private:
    int num_particles_w;
    int num_particles_h;

    std::vector<Particle> particles;
    std::vector<Spring> springs;

    Particle *getParticle(int x, int y);

    void makeSpring(Particle *p1, Particle *p2);

    //Calculate normal for forces acting on a triangle formed by p1, p2 and p3
    static Vec3 calcNormal(Particle *p1, Particle *p2, Particle *p3);

    //Calc wind force acting a triangle of particles
    static void addForces3D(Particle *p1, Particle *p2, Particle *p3, Vec3 direction);

    //Draw the triangle. Called in drawShade() function
    static void drawTriangle(Particle *p1, Particle *p2, Particle *p3, Vec3 color);
};

class Flag {
public:
    Flag() = default;

    ~Flag() = default;

    static void draw();
};