#include "utilities.h"

using namespace std;

// random number generators with type int
int randomInt(int min, int max) {
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// random number generators with type float
float randomFloat(float min, float max) {
    random_device device;
    mt19937 generator(device());
    uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

// random number generators with type bool
bool randomBool() {
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator);
}

// reset coordination system
void resetCoordinationSystem() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
}