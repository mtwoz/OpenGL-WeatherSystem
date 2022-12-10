#include <cmath>

class Vec3 {
public:
    float f[3]{};

    Vec3() = default;

    Vec3(float x, float y, float z);

    float length();

    Vec3 normalized();

    void operator+=(const Vec3 &v);

    Vec3 operator/(const float &a);

    Vec3 operator-(const Vec3 &v);

    Vec3 operator+(const Vec3 &v);

    Vec3 operator*(const float &a);

    Vec3 operator-();

    Vec3 cross(const Vec3 &v);

    float dot(const Vec3 &v);
};