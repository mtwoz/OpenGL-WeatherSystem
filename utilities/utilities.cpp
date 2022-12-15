#include "utilities.h"

using namespace std;

float wind_velocity_x = 0;
float wind_velocity_z = 0;
int flag_angle = 0;

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