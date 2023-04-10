#include <cmath>

#include "matrix.h"

Matrix::Matrix()
{
    m11 = 1;  m21 = 0;  m31 = 0;  m41 = 0;
    m12 = 0;  m22 = 1;  m32 = 0;  m42 = 0;
    m13 = 0;  m23 = 0;  m33 = 1;  m43 = 0;
    m14 = 0;  m24 = 0;  m34 = 0;  m44 = 1;
}

Matrix operator* (const Matrix& a, const Matrix& b)
{
    Matrix m;

    //row 1
    m.m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14;
    m.m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24;
    m.m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34;
    m.m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44;
    
    //row 2
    m.m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14;
    m.m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24;
    m.m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34;
    m.m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44;

    //row 3
    m.m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14;
    m.m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24;
    m.m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34;
    m.m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44;

    //row 4
    m.m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14;
    m.m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24;
    m.m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34;
    m.m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44;

    return m;
}

Matrix operator- (const Matrix& a)
{
    Matrix m;

    m.m11 = a.m11;  m.m21 = a.m12;  m.m31 = a.m13;  m.m41 = -a.m41;
    m.m12 = a.m21;  m.m22 = a.m22;  m.m32 = a.m23;  m.m42 = -a.m42;
    m.m13 = a.m31;  m.m23 = a.m32;  m.m33 = a.m33;  m.m43 = -a.m43;
    m.m14 =     0;  m.m24 =     0;  m.m34 =     0;  m.m44 =      1;

    return m;
}

Vector3 operator* (const Matrix& m, const Vector3& v)
{
    Vector3 result = {
        m.m11 * v.x + m.m21 * v.y + m.m31 * v.z,
        m.m12 * v.x + m.m22 * v.y + m.m32 * v.z,
        m.m13 * v.x + m.m23 * v.y + m.m33 * v.z
    };
    return result;
}

Matrix Matrix::translation(const Vector3& position)
{
    Matrix m;
    m.m11 = 1;  m.m21 = 0;  m.m31 = 0;  m.m41 = position.x;
    m.m12 = 0;  m.m22 = 1;  m.m32 = 0;  m.m42 = position.y;
    m.m13 = 0;  m.m23 = 0;  m.m33 = 1;  m.m43 = position.z;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

Matrix Matrix::rotation(const Vector3& rotation)
{
    float sx = sin(rotation.x);
    float sy = sin(rotation.y);
    float sz = sin(rotation.z);
    float cx = cos(rotation.x);
    float cy = cos(rotation.y);
    float cz = cos(rotation.z);
    
    Matrix m;
    m.m11 =   cz * cy;  m.m21 =  cz * sy * sx + -sz * cx;  m.m31 =  cz * sy * cx + -sz * -sx;  m.m41 = 0;
    m.m12 =   sz * cy;  m.m22 =  sz * sy * sx +  cz * cx;  m.m32 =  sz * sy * cx +  cz * -sx;  m.m42 = 0;
    m.m13 =  -sy;       m.m23 =  cy * sx;                  m.m33 =  cy * cx;                   m.m43 = 0;
    m.m14 =   0;        m.m24 =  0;                        m.m34 =  0;                         m.m44 = 1;
    return m;
}

Matrix Matrix::rotationX(float x)
{
    Matrix m;
    m.m11 = 1;  m.m21 =      0;  m.m31 =       0;  m.m41 = 0;
    m.m12 = 0;  m.m22 = cos(x);  m.m32 = -sin(x);  m.m42 = 0;
    m.m13 = 0;  m.m23 = sin(x);  m.m33 =  cos(x);  m.m43 = 0;
    m.m14 = 0;  m.m24 =      0;  m.m34 =       0;  m.m44 = 1;
    return m;
}

Matrix Matrix::rotationY(float y)
{
    Matrix m;
    m.m11 =  cos(y);  m.m21 = 0;  m.m31 = sin(y);  m.m41 = 0;
    m.m12 =       0;  m.m22 = 1;  m.m32 =      0;  m.m42 = 0;
    m.m13 = -sin(y);  m.m23 = 0;  m.m33 = cos(y);  m.m43 = 0;
    m.m14 =       0;  m.m24 = 0;  m.m34 =      0;  m.m44 = 1;
    return m;
}

Matrix Matrix::rotationZ(float z)
{
    Matrix m;
    m.m11 = cos(z);  m.m21 = -sin(z);  m.m31 = 0;  m.m41 = 0;
    m.m12 = sin(z);  m.m22 =  cos(z);  m.m32 = 0;  m.m42 = 0;
    m.m13 =      0;  m.m23 =       0;  m.m33 = 1;  m.m43 = 0;
    m.m14 =      0;  m.m24 =       0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

Matrix Matrix::scale(const Vector3& scale)
{
    Matrix m;
    m.m11 = scale.x;  m.m21 = 0;        m.m31 = 0;        m.m41 = 0;
    m.m12 = 0;        m.m22 = scale.y;  m.m32 = 0;        m.m42 = 0;
    m.m13 = 0;        m.m23 = 0;        m.m33 = scale.z;  m.m43 = 0;
    m.m14 = 0;        m.m24 = 0;        m.m34 = 0;        m.m44 = 1;
    return m;
}

Matrix Matrix::perspective(double fov, double aspect, double zNear, double zFar)
{
    //https://wiki.delphigl.com/index.php/glFrustum
    double h = zNear * tan(fov * 0.5);
    double w = h * aspect;

    float m11 = zNear / w;
    float m22 = zNear / h;
    float m33 = -(zFar + zNear) / (zFar - zNear);
    float m43 = -2 * zFar * zNear / (zFar - zNear);

    Matrix m;
    m.m11 = m11;  m.m21 =   0;  m.m31 =   0;  m.m41 =   0;
    m.m12 =   0;  m.m22 = m22;  m.m32 =   0;  m.m42 =   0;
    m.m13 =   0;  m.m23 =   0;  m.m33 = m33;  m.m43 = m43;
    m.m14 =   0;  m.m24 =   0;  m.m34 =  -1;  m.m44 =   0;
    return m;
}