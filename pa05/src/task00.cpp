
#include "common.h"

/**
 * Examples of usage of the linalg library for vector/matrix
 * math.  Available aliases:
 *   Vec2f, Vec3f, Vec4f,
 *   Color3f, Color4f,
 *   Vec2i, Vec3i,
 *   Mat4
 */
int main() {
    // Vec3f is an alias for linalg::vec<float, 3>
    Vec3f a{1,2,3};
    Vec3f b{ 4, 5, 6};

    fmt::print("a = {}", a);
    fmt::print("b = {}", b);

    // Normalize a vector
    fmt::print("a = {}\n", a);
    a = normalize(a);
    fmt::print("a (normalized) = {}\n", a);

    // Scaling a vector
    a = a * 0.5f;
    fmt::print("a * 0.5 = {}\n", a);

    // adding vectors
    Vec3f c = a + b;
    fmt::print("a + b = {}\n", c);

    // Dot product
    float d = dot(a,b);
    fmt::print("a dot b = {}\n", d);

    // Cross product
    c = cross(a, b);
    fmt::print("a cross b = {}\n", c);

    // Matrix construction
    Mat4 mi{linalg::identity};
    // Translation by (1, 2, -1)
    Mat4 m_translation{ {1, 0, 0, 0}, {0, 1, 0, 0},
                        {0, 0, 1, 0}, {1, 2, -1, 1}};

    fmt::print("Identity matrix:\n{}\n", mi);
    fmt::print("Translation (1,2,-1):\n{}\n", m_translation);

    // Matrix multiply
    Mat4 product = mul( mi, m_translation );
    fmt::print("mi * m_translation = \n{}\n", product);

    // Transform as a point
    Vec3f p{2,0,3};
    Vec4f transformed = mul( m_translation, Vec4f{p.x, p.y, p.z, 1.0f});
    fmt::print("transformed (point) = {}\n", transformed);

    // Transform as a vector
    transformed = mul( m_translation, Vec4f{p.x, p.y, p.z, 0.0f});
    fmt::print("transformed (vector) = {}\n", transformed);

    // Use the space below to practice with the linalg types and functions...
}