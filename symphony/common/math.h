#ifndef __X_MATH_H_
#define __X_MATH_H_

#include <string>

#define PI 3.1415926f
#define TWO_PI 6.2831852f
#define DEG_TO_RAD 0.0174533f
#define RAD_TO_DEG 57.2957805f

// float Q_rsqrt( float number )
// {
//  long i;
//  float x2, y;
//  const float threehalfs = 1.5F;
//
//  x2 = number * 0.5F;
//  y  = number;
//  i  = * ( long* ) &y;                        // evil FLOATing point bit level
//  hacking i  = 0x5f3759df - ( i >> 1 );               // what the fuck? y  = *
//  ( float* ) &i; y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
// //   y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can
// be removed
//  return y;
// }

class Vector2D {
   public:
    Vector2D(float _x = 0.0f, float _y = 0.0f);

    Vector2D& operator*=(float v);

    Vector2D& operator/=(float v);

    Vector2D& operator-=(float v);

    Vector2D& operator+=(float v);

    Vector2D& operator+=(const Vector2D& v);

    Vector2D& operator-=(const Vector2D& v);

    bool operator==(Vector2D& pt);

    Vector2D operator-(const Vector2D& v) const;

    float Length() const;

    float SquaredLength() const;

    float Distance(Vector2D pos);

    float Normalized();

    // 求到线段的距离
    float DistanceToSegment(Vector2D pt1, Vector2D pt2);

    // 求弧度范围: 0-π
    float AngleBetween(const Vector2D dest);

    // 向量转弧度范围: 0-2π
    float ToRadiansAngle();

    // 向量转角度范围: 0-360
    float ToDegreesAngle();

    Vector2D Rotate(Vector2D A, float radianAngle);

    void Rotate(float radianAngle);

    bool FromString(std::string str);

    float m_x;
    float m_y;
};

typedef Vector2D CPoint2D;

class Rect2D {
   public:
    Rect2D(float fLeft, float fTop, float fRight, float fBottom);

    Rect2D();

    void Init(float fLeft, float fTop, float fRight, float fBottom);

    bool Contains(CPoint2D pt);

    bool Contains(Rect2D rcArea);

    bool Intersects(Rect2D rcArea);

    void Reset();

    float m_fLeft = 0, m_fTop = 0, m_fBottom = 0, m_fRight = 0;
};

class Circle2D {
   public:
    Circle2D(float fX, float fY, float fRadius);

    Circle2D(CPoint2D pt, float fRadius);

    void Init(float fX, float fY, float fRadius);

    bool Contains(CPoint2D pt);

    bool Intersects(Rect2D rcArea);

    void Reset();

    CPoint2D m_CenterPos;
    float m_fRadius;
};

class Vector3D {
   public:
    Vector3D();

    Vector3D(float x1, float y1, float z1);

    Vector3D(const Vector3D& v);

    ~Vector3D();
    ;

    Vector3D& operator=(const Vector3D& v);

    Vector3D operator+(const Vector3D& v);

    Vector3D operator-(const Vector3D& v);

    Vector3D operator*(const Vector3D& rhs) const;

    Vector3D operator/(const Vector3D& rhs) const;

    Vector3D operator*(const Vector3D& v);

    Vector3D operator+(float f);

    Vector3D operator-(float f);

    Vector3D operator*(float f);

    Vector3D& operator+=(const Vector3D& v);

    Vector3D& operator-=(const Vector3D& v);

    Vector3D& operator*=(const Vector3D& v);

    Vector3D& operator/=(const Vector3D& rhs);

    Vector3D& operator+=(float f);

    Vector3D& operator-=(float f);

    Vector3D& operator*=(float f);

    bool operator==(const Vector3D& rkVector) const;

    bool operator!=(const Vector3D& rkVector) const;

    // 点集
    float DotProduct(const Vector3D& v);

    float Length();

    void Reset();

    float SquaredLength() const;

    float Normalize();

    Vector3D CrossProduct(const Vector3D& v);

    float AngleBetween(Vector3D dest);

    float Distance2D(Vector3D pos);

    // 求弧度范围: 0-π
    float AngleBetween2D(Vector3D& dest);

    Vector2D Rotate(Vector2D A, float radianAngle);

    // 求向量在对应向量的平行分量
    Vector3D ParallelComponent(Vector3D& unitBasis);

    // 求向量在对应向量的垂直分量
    Vector3D PerpendicularComponent(Vector3D& unitBasis);

    // 求弧度范围: 0-2π
    float ToRadiansAngle();

    // 求角度范围: 0-360
    float ToDegreesAngle();

    bool FromString(const char* pStr);

    float m_x, m_y, m_z;
};

typedef Vector3D CPoint3D;

namespace CommonMath {

// 角度转弧度
float DegreesToRadians(float fDegrees);

// 弧度转角度
float RadiansToDegrees(float fRadians);

// 限制取值
float Clamp(const float fValue, const float fMin, const float fMax);

bool IsInCircle(Vector3D tTarPos,
                float fTarRadius,
                Vector3D tCirclePos,
                float fCircleRadius);

}  // namespace CommonMath

#endif  //_MAP_H_