#pragma once

#include "vec3.h"
#include "texture.h"
#include "utilities.h"

#define Resistance 0.02
#define TIME2 (0.5*0.5)
#define SPRING_ITERATIONS 15

class Particle {
public:
    explicit Particle(Vec3 pos_);

    Particle() = default;

    void addForce(Vec3 force);

    void update();

    Vec3 &getPos();

    void offsetPos(Vec3 vec);

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
    float rest_distance;
};

class Cloth {
public:

    Cloth(float w, float h, int particles_w, int particles_h);

    void draw();

    void update();

    void addForce(Vec3 direction);

    void addWindForce(Vec3 direction);

private:
    int num_particles_w;
    int num_particles_h;

    std::vector<Particle> particles;
    std::vector<Spring> springs;

    Particle *getParticle(int x, int y);

    void makeSpring(Particle *p1, Particle *p2);

    static Vec3 calcNormal(Particle *p1, Particle *p2, Particle *p3);

    static void addForces3D(Particle *p1, Particle *p2, Particle *p3, Vec3 direction);

    static void drawTriangle(Particle *p1, Particle *p2, Particle *p3, Vec3 color);
};

class Flag {
public:
    Flag() = default;

    ~Flag() = default;

    static void draw();
};