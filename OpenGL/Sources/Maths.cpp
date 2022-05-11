#include <Log.h>
#include <Maths.h>


using namespace Core;
using namespace Maths;

#define M_PI 3.14159265358979323846

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(float a, float b)
{
    x = a;
    y = b;
}

void Vec2::Print()
{
    Debug::Log vec2;
    vec2.Print("x = %f  y = %f\n",x,y);
}


float Vec2::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    return { x, y };
}

Vec2::~Vec2()
{
}

Vec3::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}
void Vec3::Print()
{
    Debug::Log vec3;
    vec3.Print("x = %f  y = %f   z = %f\n", x, y,z);
}
float Vec3::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vec3 Vec3::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    z = z / GetMagnitude();
    return { x, y, z };
}

Vec3 Core::Maths::operator+(const Vec3& a, const Vec3& b)
{
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 Core::Maths::operator*(const float& a, const Vec3& b)
{
    return { b.x * a, b.y * a, b.z * a };
}

Vec3 Core::Maths::operator*(const Vec3& b, const float& a)
{
    return { b.x * a, b.y * a, b.z * a };
}

float Core::Maths::operator*(const Vec3& a, const Vec3& b)
{
    return (b.x * a.x) + (b.y * a.y) + (b.z * a.z);
}

float Core::Maths::dot(const Vec3& a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Core::Maths::operator-(const Vec3& a, const Vec3& b)
{
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3 Core::Maths::CrossProduct(const Vec3& a, const Vec3& b)
{
    float x2, y2, z2;

    x2 = b.z * a.y - b.y * a.z;
    y2 = b.x * a.z - b.z * a.x;
    z2 = b.y * a.x - b.x * a.y;
    return { x2, y2, z2 };
}

Vec3::~Vec3()
{
}

Vec4::Vec4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vec4::Vec4(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

Vec4::Vec4(const Vec3& vec3, float _w)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}

void Vec4::Homogenize()
{
    if (w != 0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }
}

Vec3 Vec4::GetHomogenize()
{
    Vec3 result;
    if (w != 0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }
    result = { x, y, z };
    return (result);
}

void Vec4::Print()
{
    Debug::Log vector;
    vector.Print("\n|%f|%f|%f|%f|\n\n", x, y, z, w);
}

float Vec4::GetMagnitude()
{
    Vec4 temp({ x, y, z }, w);
    temp.Homogenize();
    return sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
}

void Vec4::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    z = z / GetMagnitude();
}

Vec4 Vec4::operator+(const Vec4& rhs)
{
    Vec4 temp({ this->x + rhs.x, this->y + rhs.y, this->z + rhs.z }, this->w + rhs.w);
    return temp;
}

Vec4 Vec4::operator*(const float& rhs)
{
    Vec4 temp({ this->x * rhs, this->y * rhs, this->z * rhs }, this->w * rhs);
    return temp;
}

Vec4::~Vec4()
{
}

Mat4::Mat4()
{
    for (int i = 0; i < 16; i++)
    {
        mat[i] = 0;
    }
}

void Mat4::Print()
{
    Debug::Log matrix;
    matrix.Print("\n");
    matrix.Print("-------------------------\n");
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
            matrix.Print("|");

        matrix.Print(" %d ", (int)mat[i]);
        matrix.Print("|");
        if (i % 4 == 3)
            matrix.Print("\n-------------------------\n");
    }
    matrix.Print("\n");
}
Mat4 Mat4::identity()
{
    float array[16] = {

        1.f,
        0.f,
        0.f,
        0.f,
        0.f,
        1.f,
        0.f,
        0.f,
        0.f,
        0.f,
        1.f,
        0.f,
        0.f,
        0.f,
        0.f,
        1.f,

    };

    Mat4 temp = array;
    return temp;
}
Mat4::Mat4(const float(&arr)[16])
{
    for (int i = 0; i < 16; i++)
    {
        mat[i] = arr[i];
    }
}

Mat4 Mat4::operator*(const Mat4& rhs)
{
    Mat4 temp;
    temp.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[8] + mat[3] * rhs.mat[12];
    temp.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[9] + mat[3] * rhs.mat[13];
    temp.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[6] + mat[2] * rhs.mat[10] + mat[3] * rhs.mat[14];
    temp.mat[3] = mat[0] * rhs.mat[3] + mat[1] * rhs.mat[7] + mat[2] * rhs.mat[11] + mat[3] * rhs.mat[15];

    temp.mat[4] = mat[4] * rhs.mat[0] + mat[5] * rhs.mat[4] + mat[6] * rhs.mat[8] + mat[7] * rhs.mat[12];
    temp.mat[5] = mat[4] * rhs.mat[1] + mat[5] * rhs.mat[5] + mat[6] * rhs.mat[9] + mat[7] * rhs.mat[13];
    temp.mat[6] = mat[4] * rhs.mat[2] + mat[5] * rhs.mat[6] + mat[6] * rhs.mat[10] + mat[7] * rhs.mat[14];
    temp.mat[7] = mat[4] * rhs.mat[3] + mat[5] * rhs.mat[7] + mat[6] * rhs.mat[11] + mat[7] * rhs.mat[15];

    temp.mat[8] = mat[8] * rhs.mat[0] + mat[9] * rhs.mat[4] + mat[10] * rhs.mat[8] + mat[11] * rhs.mat[12];
    temp.mat[9] = mat[8] * rhs.mat[1] + mat[9] * rhs.mat[5] + mat[10] * rhs.mat[9] + mat[11] * rhs.mat[13];
    temp.mat[10] = mat[8] * rhs.mat[2] + mat[9] * rhs.mat[6] + mat[10] * rhs.mat[10] + mat[11] * rhs.mat[14];
    temp.mat[11] = mat[8] * rhs.mat[3] + mat[9] * rhs.mat[7] + mat[10] * rhs.mat[11] + mat[11] * rhs.mat[15];

    temp.mat[12] = mat[12] * rhs.mat[0] + mat[13] * rhs.mat[4] + mat[14] * rhs.mat[8] + mat[15] * rhs.mat[12];
    temp.mat[13] = mat[12] * rhs.mat[1] + mat[13] * rhs.mat[5] + mat[14] * rhs.mat[9] + mat[15] * rhs.mat[13];
    temp.mat[14] = mat[12] * rhs.mat[2] + mat[13] * rhs.mat[6] + mat[14] * rhs.mat[10] + mat[15] * rhs.mat[14];
    temp.mat[15] = mat[12] * rhs.mat[3] + mat[13] * rhs.mat[7] + mat[14] * rhs.mat[11] + mat[15] * rhs.mat[15];

    return temp;
}

Vec4 Mat4::operator*(const Vec4& rhs)
{
    Vec4 temp;
    temp.x = mat[0] * rhs.x + mat[1] * rhs.y + mat[2] * rhs.z + mat[3] * rhs.w;
    temp.y = mat[4] * rhs.x + mat[5] * rhs.y + mat[6] * rhs.z + mat[7] * rhs.w;
    temp.z = mat[8] * rhs.x + mat[9] * rhs.y + mat[10] * rhs.z + mat[11] * rhs.w;
    temp.w = mat[12] * rhs.x + mat[13] * rhs.y + mat[14] * rhs.z + mat[15] * rhs.w;
    return temp;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
{
    float array[16] =
    {
        1, 0, 0, translation.x,
        0, 1, 0, translation.y,
        0, 0, 1, translation.z,
        0, 0, 0, 1 };
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
{
    float array[16] =
    {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1 };
    Mat4 temp = array;
    return temp;
}
Mat4::Mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
    float arr[16] = { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p };

    for (int i = 0; i < 16; i++)
    {
        mat[i] = arr[i];
    }
}

Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    float array[16] =
    {
        1, 0, 0, 0,
        0, cos(angle), sin(angle), 0,
        0, -sin(angle), cos(angle), 0,
        0, 0, 0, 1 };
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    float array[16] =
    {
        cos(angle), 0, -sin(angle), 0,
        0, 1, 0, 0,
        sin(angle), 0, cos(angle), 0,
        0, 0, 0, 1 };
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    float array[16] =
    {
        cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    /*   float array[16] =
    {
        scale.x * cosf(rotation.y)*cosf(rotation.z),-sinf(rotation.z),sinf(rotation.z),position.x,
        sinf(rotation.z),scale.y*cosf(rotation.x)*cosf(rotation.x),-sinf(rotation.z),position.y,
        -sinf(rotation.y),sinf(rotation.x),scale.z*cosf(rotation.y)*cosf(rotation.x),position.z,
        0,0,0,1
    };
    Mat4 temp = array;
    return  temp ; */
    return CreateTranslationMatrix(position) * (CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z)) * CreateScaleMatrix(scale);
}

Mat4 Mat4::Perspective()
{
    float f = 2; // far clipping plane
    float n = 1; // near clipping plane
    float fov = 60;
    float s = 1 / tanf((fov / 2) * (M_PI / 180));
    float c = f / (f - n);
    float array[16] = {

        s,
        0.f,
        0.f,
        0.f,
        0.f,
        s,
        0.f,
        0.f,
        0.f,
        0.f,
        -c,
        -1.f,
        0.f,
        0.f,
        -(c * n),
        0.f,

    };
    return array;
}


void Mat4::TransposeMatrix(const int M, const int N)
{

    Mat4 temp = mat;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int index = i * N + j;
            int index2 = j * M + i;
            mat[index2] = temp.mat[index];
        }
    }
}

Mat4::~Mat4()
{
}

Mat3::Mat3()
{
    for (int i = 0; i < 9; i++)
    {
        mat[i] = 0;
    }
}

void Mat3::Print()
{
    Debug::Log matrix;
    matrix.Print("\n");
    matrix.Print("-------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            matrix.Print("|");

        matrix.Print(" %d ", (int)mat[i]);
        matrix.Print("|");
        if (i % 3 == 2)
            matrix.Print("\n-------------------------\n");
    }
    matrix.Print("\n");
}
Mat3 Mat3::identity()
{
    float array[9] = {

        1.f,
        0.f,
        0.f,
        0.f,
        1.f,
        0.f,
        0.f,
        0.f,
        1.f
    };

    Mat3 temp = array;
    return temp;
}
Mat3::Mat3(const float(&arr)[9])
{
    for (int i = 0; i < 9; i++)
    {
        mat[i] = arr[i];
    }
}

Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float arr[9] = { a, b, c, d, e, f, g, h, i };

    for (int i = 0; i < 9; i++)
    {
        mat[i] = arr[i];
    }
}

Mat3 Mat3::operator*(const Mat3& rhs)
{
    Mat3 temp;
    temp.mat[0] = mat[0] * rhs.mat[0] + mat[1] * rhs.mat[3] + mat[2] * rhs.mat[6];
    temp.mat[1] = mat[0] * rhs.mat[1] + mat[1] * rhs.mat[4] + mat[2] * rhs.mat[7];
    temp.mat[2] = mat[0] * rhs.mat[2] + mat[1] * rhs.mat[5] + mat[2] * rhs.mat[8];

    temp.mat[3] = mat[3] * rhs.mat[0] + mat[4] * rhs.mat[3] + mat[5] * rhs.mat[6];
    temp.mat[4] = mat[3] * rhs.mat[1] + mat[4] * rhs.mat[4] + mat[5] * rhs.mat[7];
    temp.mat[5] = mat[3] * rhs.mat[2] + mat[4] * rhs.mat[5] + mat[5] * rhs.mat[8];

    temp.mat[6] = mat[6] * rhs.mat[0] + mat[7] * rhs.mat[3] + mat[8] * rhs.mat[6];
    temp.mat[7] = mat[6] * rhs.mat[1] + mat[7] * rhs.mat[4] + mat[8] * rhs.mat[7];
    temp.mat[8] = mat[6] * rhs.mat[2] + mat[7] * rhs.mat[5] + mat[8] * rhs.mat[8];


    return temp;
}

Vec3 Mat3::operator*(const Vec3& rhs)
{
    Vec3 temp;
    temp.x = mat[0] * rhs.x + mat[1] * rhs.y + mat[2] * rhs.z;
    temp.y = mat[3] * rhs.x + mat[4] * rhs.y + mat[5] * rhs.z ;
    temp.z = mat[6] * rhs.x + mat[7] * rhs.y + mat[8] * rhs.z ;
    return temp;
}
void Mat3::TransposeMatrix(const int M, const int N)
{

    Mat3 temp = mat;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int index = i * N + j;
            int index2 = j * M + i;
            mat[index2] = temp.mat[index];
        }
    }
}

Mat3::~Mat3()
{
}
