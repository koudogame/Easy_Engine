///
/// @file   egeg_math.hpp
/// @author 板場
///
/// @brief  数学ライブラリ
///
#ifndef INCLUDED_EGEG_MATH_HEADER_
#define INCLUDED_EGEG_MATH_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif // !_DEBUG
#include <corecrt_math_defines.h>
#include <cmath>
#include "egeg_common.hpp"

BEGIN_EGEG
// 角度変換
/*===========================================================================*/
///
/// @brief  度数法の値を弧度法の値へ変換します。
///
/// @param[in] Degrees : 変換したい値( 度数法 )
///
/// @return 引数の値を弧度法へ変換した値
///
inline float convertToRadians( float Degrees )
{
    static constexpr float kToRadians = static_cast<float>(M_PI) / 180.0F;
    return Degrees * kToRadians;
}

///
/// @brief  弧度法の値を度数法の値へ変換します。
///
/// @param[in] Radians : 変換したい値( 弧度法 )
///
/// @return 引数の値を度数法へ変換した値
///
inline float convertToDegrees( float Radians )
{
    static constexpr float kToDegrees = 180.0F / static_cast<float>(M_PI);
    return Radians * kToDegrees;
}

// Vector2D
/*===========================================================================*/
struct Float2
{
    float x;
    float y;
};
struct Vector2D : public Float2
{
    Vector2D() = default;
    Vector2D( const Vector2D& ) = default;
    Vector2D( Vector2D&& ) = default;
    Vector2D& operator=( const Vector2D& ) = default;
    Vector2D& operator=( Vector2D&& ) = default;
    constexpr Vector2D( float X, float Y ) :
        Float2{ X, Y }
    {}
    explicit constexpr Vector2D( float S ) :
        Float2{ S, S }
    {}

    inline float dot( const Vector2D& ) const;
    inline float cross( const Vector2D& ) const;
    inline Vector2D& operator=( float );
    inline Vector2D& operator+=( const Vector2D& );
    inline Vector2D& operator-=( const Vector2D& );
    inline Vector2D& operator*=( float );
    inline Vector2D& operator/=( float );
};
inline Vector2D operator+( const Vector2D&, const Vector2D& );
inline Vector2D operator-( const Vector2D&, const Vector2D& );
inline Vector2D operator*( const Vector2D&, float );
inline Vector2D operator/( const Vector2D&, float );


// Vector3D
/*===========================================================================*/
struct Float3
{
    float x;
    float y;
    float z;
};
struct Vector3D : public Float3
{
    Vector3D() = default;
    Vector3D( const Vector3D& ) = default;
    Vector3D( Vector3D&& ) = default;
    Vector3D& operator=( const Vector3D& ) = default;
    Vector3D& operator=( Vector3D&& ) = default;
    constexpr Vector3D( float X, float Y, float Z ) :
        Float3{ X, Y, Z }
    {}
    explicit constexpr Vector3D( float S ) :
        Float3{ S, S, S }
    {}

    inline float dot( const Vector3D& );
    inline Vector3D cross( const Vector3D& );
    inline Vector3D& operator=( float );
    inline Vector3D& operator+=( const Vector3D& );
    inline Vector3D& operator-=( const Vector3D& );
    inline Vector3D& operator*=( float );
    inline Vector3D& operator/=( float );
};
inline Vector3D operator+( const Vector3D&, const Vector3D& );
inline Vector3D operator-( const Vector3D&, const Vector3D& );
inline Vector3D operator*( const Vector3D&, float );
inline Vector3D operator/( const Vector3D&, float );


// Vector4D
/*===========================================================================*/
struct Float4
{
    float x;
    float y;
    float z;
    float w;
};
struct Vector4D : public Float4
{
    Vector4D() = default;
    Vector4D( const Vector4D& ) = default;
    Vector4D( Vector4D&& ) = default;
    Vector4D& operator=( const Vector4D& ) = default;
    Vector4D& operator=( Vector4D&& ) = default;
    constexpr Vector4D( float X, float Y, float Z, float W ) :
        Float4{ X, Y, Z, W }
    {}
    explicit constexpr Vector4D( float S ) :
        Float4{ S, S, S, S }
    {}

    inline float dot( const Vector4D& );
    inline Vector4D& operator=( float );
    inline Vector4D& operator+=( const Vector4D& );
    inline Vector4D& operator-=( const Vector4D& );
    inline Vector4D& operator*=( float );
    inline Vector4D& operator/=( float );
};
inline Vector4D operator+( const Vector4D&, const Vector4D& );
inline Vector4D operator-( const Vector4D&, const Vector4D& );
inline Vector4D operator*( const Vector4D&, float );
inline Vector4D operator/( const Vector4D&, float );


// Matrix3x3
/*===========================================================================*/
struct Float3x3
{
     union
    {
        struct
        {
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        };
        float m[3][3];
    };
};
struct Matrix3x3 : public Float3x3
{
    Matrix3x3() = default;
    Matrix3x3( const Matrix3x3& ) = default;
    Matrix3x3( Matrix3x3&& ) = default;
    Matrix3x3& operator=( const Matrix3x3& ) = default;
    Matrix3x3& operator=( Matrix3x3&& ) = default;
    constexpr Matrix3x3( 
        float M00, float M01, float M02,
        float M10, float M11, float M12,
        float M20, float M21, float M22 ) :
        Float3x3 {
        M00, M01, M02,
        M10, M11, M12,
        M20, M21, M22 }
    {}

    static inline Matrix3x3 createIdentity();
    static inline Matrix3x3 createTransposeMatrix( const Matrix3x3& );
    static inline Matrix3x3 createTranslationMatrix( const Vector2D& );
    static inline Matrix3x3 createRotationMatrix( float AngleDEG );
    static inline Matrix3x3 createScalingMatrix( const Vector2D& );

    inline Vector3D row( unsigned ) const;
    inline Vector3D column( unsigned ) const;
    inline void transpose();
    inline Matrix3x3& operator+=( const Matrix3x3& );
    inline Matrix3x3& operator-=( const Matrix3x3& );
    inline Matrix3x3& operator*=( const Matrix3x3& );
    inline Matrix3x3& operator*=( float );
    inline Matrix3x3& operator/=( float );
};
inline Matrix3x3 operator+( const Matrix3x3&, Matrix3x3& );
inline Matrix3x3 operator-( const Matrix3x3&, Matrix3x3& );
inline Matrix3x3 operator*( const Matrix3x3&, Matrix3x3& );
inline Matrix3x3 operator*( const Matrix3x3&, float );
inline Matrix3x3 operator/( const Matrix3x3&, float );


// Matrix4x4
/*===========================================================================*/
struct Float4x4
{
    union
    {
        struct
        {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        float m[4][4];
    };
};
struct Matrix4x4 : public Float4x4
{
    Matrix4x4() = default;
    Matrix4x4( const Matrix4x4& ) = default;
    Matrix4x4( Matrix4x4&& ) = default;
    Matrix4x4& operator=( const Matrix4x4& ) = default;
    Matrix4x4& operator=( Matrix4x4&& ) = default;
    constexpr Matrix4x4( 
        float M00, float M01, float M02, float M03,
        float M10, float M11, float M12, float M13,
        float M20, float M21, float M22, float M23,
        float M30, float M31, float M32, float M33) :
        Float4x4{
        M00, M01, M02, M03,
        M10, M11, M12, M13,
        M20, M21, M22, M23,
        M30, M31, M32, M33 }
    {}
    
    static inline Matrix4x4 createIdentity();
    static inline Matrix4x4 createTransposeMatrix( const Matrix4x4& );
    static inline Matrix4x4 createTranslationMatrix( const Vector3D& );
    static inline Matrix4x4 createRotationXMatrix( float AngleDEG );
    static inline Matrix4x4 createRotationYMatrix( float AngleDEG );
    static inline Matrix4x4 createRotationZMatrix( float AngleDEG );
    static inline Matrix4x4 createScalingMatrix( const Vector3D& );

    inline Vector4D row( unsigned Line ) const;
    inline Vector4D column( unsigned Line ) const;
    inline void transpose();
    inline Matrix4x4& operator+=( const Matrix4x4& );
    inline Matrix4x4& operator-=( const Matrix4x4& );
    inline Matrix4x4& operator*=( const Matrix4x4& );
    inline Matrix4x4& operator*=( float S );
    inline Matrix4x4& operator/=( float S );
};
inline Matrix4x4 operator+( const Matrix4x4&, Matrix4x4& );
inline Matrix4x4 operator-( const Matrix4x4&, Matrix4x4& );
inline Matrix4x4 operator*( const Matrix4x4&, Matrix4x4& );
inline Matrix4x4 operator*( const Matrix4x4&, float );
inline Matrix4x4 operator/( const Matrix4x4&, float );


// Vector2D 関数実装
/*===========================================================================*/
inline float Vector2D::dot( const Vector2D& V ) const
{
    return (this->x * V.x) + (this->y * V.y);
}
inline float Vector2D::cross( const Vector2D& V ) const
{
    return (this->x * V.y) - (this->y * V.x);
}
inline Vector2D& Vector2D::operator=( float S )
{
    this->x = S;
    this->y = S;
    return *this;
}
inline Vector2D& Vector2D::operator+=( const Vector2D& V )
{
    this->x += V.x;
    this->y += V.y;
    return *this;
}
inline Vector2D& Vector2D::operator-=( const Vector2D& V )
{
    this->x -= V.x;
    this->y -= V.y;
    return *this;
}
inline Vector2D& Vector2D::operator*=( float S )
{
    this->x *= S;
    this->y *= S;
    return *this;
}
inline Vector2D& Vector2D::operator/=( float S )
{
    float reciprocal = 1.0F / S;
    this->x *= reciprocal;
    this->y *= reciprocal;
    return *this;
}
inline Vector2D operator+( const Vector2D& L, const Vector2D& R )
{
    return Vector2D( L.x + R.x, L.y + R.y );
}
inline Vector2D operator-( const Vector2D& L, const Vector2D& R )
{
    return Vector2D( L.x - R.x, L.y - R.y );
}
inline Vector2D operator*( const Vector2D& V, float S )
{
    return Vector2D( V.x * S, V.y * S );
}
inline Vector2D operator/( const Vector2D& V, float S )
{
    float reciprocal = 1.0F / S;
    return Vector2D( V.x * reciprocal, V.y * reciprocal );
}


// Vector3D 関数実装
/*===========================================================================*/
inline float Vector3D::dot( const Vector3D& V )
{
    return (this->x * V.x) + (this->y * V.y) + (this->z * V.z);
}
inline Vector3D Vector3D::cross( const Vector3D& V )
{
    return Vector3D(
        (this->y * V.z) - (this->z * V.y),
        (this->z * V.x) - (this->x * V.z),
        (this->x * V.y) - (this->y * V.x) );
}
inline Vector3D& Vector3D::operator=( float S )
{
    this->x = S;
    this->y = S;
    this->z = S;
    return *this;
}
inline Vector3D& Vector3D::operator+=( const Vector3D& V )
{
    this->x += V.x;
    this->y += V.y;
    return *this;
}
inline Vector3D& Vector3D::operator-=( const Vector3D& V )
{
    this->x -= V.x;
    this->y -= V.y;
    return *this;
}
inline Vector3D& Vector3D::operator*=( float S )
{
    this->x *= S;
    this->y *= S;
    return *this;
}
inline Vector3D& Vector3D::operator/=( float S )
{
    float reciprocal = 1.0F / S;
    this->x *= reciprocal;
    this->y *= reciprocal;
    return *this;
}
inline Vector3D operator+( const Vector3D& L, const Vector3D& R )
{
    return Vector3D( L.x + R.x, L.y + R.y, L.z + R.z );
}
inline Vector3D operator-( const Vector3D& L, const Vector3D& R )
{
    return Vector3D( L.x - R.x, L.y - R.y, L.z - R.z );
}
inline Vector3D operator*( const Vector3D& V, float S )
{
    return Vector3D( V.x * S, V.y * S, V.z * S );
}
inline Vector3D operator/( const Vector3D& V, float S )
{
    float reciprocal = 1.0F / S;
    return Vector3D( V.x * reciprocal, V.y * reciprocal, V.z * reciprocal );
}


// Vector4D 関数実装
/*===========================================================================*/
inline float Vector4D::dot( const Vector4D& V )
{
    return (this->x * V.x) + (this->y * V.y) + (this->z * V.z) + (this->w * V.w);
}
inline Vector4D& Vector4D::operator=( float S )
{
    this->x *= S;
    this->y *= S;
    return *this;
}
inline Vector4D& Vector4D::operator+=( const Vector4D& V )
{
    this->x += V.x;
    this->y += V.y;
    return *this;
}
inline Vector4D& Vector4D::operator-=( const Vector4D& V )
{
    this->x -= V.x;
    this->y -= V.y;
    return *this;
}
inline Vector4D& Vector4D::operator*=( float S )
{
    this->x *= S;
    this->y *= S;
    this->z *= S;
    this->w *= S;
    return *this;
}
inline Vector4D& Vector4D::operator/=( float S )
{
    float reciprocal = 1.0F / S;
    this->x *= reciprocal;
    this->y *= reciprocal;
    this->z *= reciprocal;
    this->w *= reciprocal;
    return *this;
}
inline Vector4D operator+( const Vector4D& L, const Vector4D& R )
{
    return Vector4D( L.x + R.x, L.y + R.y, L.z + R.z, L.w + R.w );
}
inline Vector4D operator-( const Vector4D& L, const Vector4D& R )
{
    return Vector4D( L.x - R.x, L.y - R.y, L.z - R.z, L.w - R.w );
}
inline Vector4D operator*( const Vector4D& L, float S )
{
    return Vector4D( L.x * S, L.y * S, L.z * S, L.w * S );
}
inline Vector4D operator/( const Vector4D& L, float S )
{
    float reciprocal = 1.0F / S;
    return Vector4D( L.x * reciprocal, L.y * reciprocal, L.z * reciprocal, L.w * reciprocal );
}


// Matrix3x3 関数の実装
/*===========================================================================*/
inline Matrix3x3 Matrix3x3::createIdentity()
{
    return Matrix3x3(
        1.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 1.0F );
}
inline Matrix3x3 Matrix3x3::createTransposeMatrix( const Matrix3x3& M )
{
    Matrix3x3 matrix;
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            matrix.m[i][j] = M.m[j][i];
        }
    }
    return matrix;
}
inline Matrix3x3 Matrix3x3::createTranslationMatrix( const Vector2D& V )
{
    return Matrix3x3(
        1.0F, 0.0F, V.x,
        0.0F, 1.0F, V.y,
        0.0F, 0.0F, 1.0F );
}
inline Matrix3x3 Matrix3x3::createRotationMatrix( float AngleDEG )
{
    float angle = convertToRadians( AngleDEG );
    return Matrix3x3(
        std::cos( angle ), -std::sin( angle ), 0.0F,
        std::sin( angle ), std::cos( angle ), 0.0F,
        0.0F, 0.0F, 1.0F );
}
inline Matrix3x3 Matrix3x3::createScalingMatrix( const Vector2D& V )
{
    return Matrix3x3 (
        V.x, 0.0F, 0.0F,
        0.0F, V.y, 0.0F,
        0.0F, 0.0F, 1.0F );
}
inline Vector3D Matrix3x3::row( unsigned Line ) const
{
#ifdef _DEBUG
    assert( Line < 3 );
#endif
    return Vector3D( this->m[Line][0], this->m[Line][1], this->m[Line][2] );
}
inline Vector3D Matrix3x3::column( unsigned Line ) const
{
#ifdef _DEBUG
    assert( Line < 3 );
#endif
    return Vector3D( this->m[0][Line], this->m[1][Line], this->m[2][Line] );
}
inline void Matrix3x3::transpose()
{
    float temp;
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            temp = this->m[i][j];
            this->m[i][j] = this->m[j][i];
            this->m[j][i] = temp;
        }
    }
}
inline Matrix3x3& Matrix3x3::operator+=( const Matrix3x3& M )
{
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            this->m[i][j] += M.m[i][j];
        }
    }
    return *this;
}
inline Matrix3x3& Matrix3x3::operator-=( const Matrix3x3& M )
{
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            m[i][j] -= M.m[i][j];
        }
    }
    return *this;
}
inline Matrix3x3& Matrix3x3::operator*=( const Matrix3x3& M )
{
    Matrix3x3 matrix;

    Vector3D vec_l;
    Vector3D vec_r;
    for( int row = 0; row < 3; ++row ) {
        for( int col = 0; col < 3; ++col )
        {
            vec_l = this->row( row );
            vec_r = M.column( col );

            matrix.m[row][col] = vec_l.dot( vec_r );
        }
    }
    return this->operator=( matrix );
}
inline Matrix3x3& Matrix3x3::operator*=( float S )
{
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            m[i][j] *= S;
        }
    }
    return *this;
}
inline Matrix3x3& Matrix3x3::operator/= ( float S )
{
    float reciprocal = 1.0F / S;
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            m[i][j] *= reciprocal;
        }
    }
    return *this;
}
inline Matrix3x3 operator+( const Matrix3x3& L, const Matrix3x3& R )
{
    Matrix3x3 matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            matrix.m[i][j] = L.m[i][j] + R.m[i][j];
        }
    }
    return matrix;
}
inline Matrix3x3 operator-( const Matrix3x3& L, const Matrix3x3& R )
{
    Matrix3x3 matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            matrix.m[i][j] = L.m[i][j] - R.m[i][j];
        }
    }
    return matrix;
}
inline Matrix3x3 operator*( const Matrix3x3& L, const Matrix3x3& R )
{
    Matrix3x3 matrix;
    Vector3D vec_l;
    Vector3D vec_r;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col)
        {
            vec_l = L.row(row);
            vec_r = R.column(col);

            matrix.m[row][col] = vec_l.dot(vec_r);
        }
    }
    return matrix;
}
inline Matrix3x3 operator*( const Matrix3x3& M, float S )
{
    Matrix3x3 matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            matrix.m[i][j] = M.m[i][j] * S;
        }
    }
    return matrix;
}
inline Matrix3x3 operator/( const Matrix3x3& M, float S )
{
    Matrix3x3 matrix;
    float reciprocal = 1.0F / S;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            matrix.m[i][j] = M.m[i][j] * reciprocal;
        }
    }
    return matrix;
}


// Matrix4x4 関数の実装
/*===========================================================================*/
inline Matrix4x4 Matrix4x4::createIdentity()
{
    return Matrix4x4(
        1.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Matrix4x4 Matrix4x4::createTransposeMatrix( const Matrix4x4& M )
{
    Matrix4x4 matrix;
    for( int i = 0; i < 3; ++i ) {
        for( int j = 0; j < 3; ++j )
        {
            matrix.m[i][j] = M.m[j][i];
        }
    }
    return matrix;
}
inline Matrix4x4 Matrix4x4::createTranslationMatrix( const Vector3D& V )
{
    return Matrix4x4 (
        1.0F, 0.0F, 0.0F, V.x,
        0.0F, 1.0F, 0.0F, V.y,
        0.0F, 0.0F, 1.0F, V.z,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Matrix4x4 Matrix4x4::createRotationXMatrix( float AngleDEG )
{
    float angle = convertToRadians( AngleDEG );
    float sin = std::sin( angle );
    float cos = std::cos( angle );
    return Matrix4x4(
        1.0F, 0.0F, 0.0F, 0.0F,
        0.0F, cos, -sin, 0.0F,
        0.0F, sin, cos, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Matrix4x4 Matrix4x4::createRotationYMatrix( float AngleDEG )
{
    float angle = convertToRadians( AngleDEG );
    float sin = std::sin( angle );
    float cos = std::cos( angle );
    return Matrix4x4(
        cos, 0.0F, sin, 0.0F,
        0.0F, 1.0F, 0.0F, 0.0F,
        -sin, 0.0F, cos, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Matrix4x4 Matrix4x4::createRotationZMatrix( float AngleDEG )
{
    float angle = convertToRadians( AngleDEG );
    float sin = std::sin( angle );
    float cos = std::cos( angle );
    return Matrix4x4 (
        cos, -sin, 0.0F, 0.0F,
        sin, cos, 0.0F, 0.0F,
        0.0F, 0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Matrix4x4 Matrix4x4::createScalingMatrix( const Vector3D& V )
{
    return Matrix4x4(
        V.x, 0.0F, 0.0F, 0.0F,
        0.0F, V.y, 0.0F, 0.0F,
        0.0F, 0.0F, V.z, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F );
}
inline Vector4D Matrix4x4::row( unsigned Line ) const
{
#ifdef _DEBUG
    assert( Line < 4 );
#endif
    return Vector4D( this->m[Line][0], this->m[Line][1], this->m[Line][2], this->m[Line][3] );
}
inline Vector4D Matrix4x4::column( unsigned Line ) const
{
#ifdef _DEBUG
    assert( Line < 4 );
#endif
    return Vector4D( this->m[0][Line], this->m[1][Line], this->m[2][Line], this->m[3][Line] );
}
inline void Matrix4x4::transpose()
{
    float temp;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}
inline Matrix4x4& Matrix4x4::operator+=( const Matrix4x4& M )
{
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            this->m[i][j] += M.m[i][j];
        }
    }
    return *this;
}
inline Matrix4x4& Matrix4x4::operator-=( const Matrix4x4& M )
{
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            this->m[i][j] -= M.m[i][j];
        }
    }
    return *this;
}
inline Matrix4x4& Matrix4x4::operator*=( const Matrix4x4& M )
{
    Matrix4x4 matrix;
    Vector4D vec_1;
    Vector4D vec_2;
    for( int row = 0; row < 4; ++row ) {
        for( int col = 0; col < 4; ++col )
        {
            vec_1 = this->row( row );
            vec_2 = M.column( col );
            matrix.m[row][col] = vec_1.dot( vec_2 );
        }
    }
    return this->operator=( matrix );
}
inline Matrix4x4& Matrix4x4::operator*=( float S )
{
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            m[i][j] *= S;
        }
    }
    return *this;
}
inline Matrix4x4& Matrix4x4::operator/=( float S )
{
    float reciprocal = 1.0F / S;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            m[i][j] *= reciprocal;
        }
    }
    return *this;
}
inline Matrix4x4 operator+( const Matrix4x4& L, const Matrix4x4& R )
{
    Matrix4x4 matrix;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            matrix.m[i][j] = L.m[i][j] + R.m[i][j];
        }
    }
    return matrix;
}
inline Matrix4x4 operator-( const Matrix4x4& L, const Matrix4x4& R )
{
    Matrix4x4 matrix;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            matrix.m[i][j] = L.m[i][j] - R.m[i][j];
        }
    }
    return matrix;
}
inline Matrix4x4 operator*( const Matrix4x4& L, const Matrix4x4& R )
{
    Matrix4x4 matrix;
    Vector4D vec_1;
    Vector4D vec_2;
    for( int row = 0; row < 4; ++row ) {
        for( int col = 0; col < 4; ++col )
        {
            vec_1 = L.row( row );
            vec_2 = R.column( col );
            matrix.m[row][col] = vec_1.dot( vec_2 );
        }
    }
    return matrix;
}
inline Matrix4x4 operator*( const Matrix4x4& M, float S )
{
    Matrix4x4 matrix;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            matrix.m[i][j] = M.m[i][j] * S;
        }
    }
    return matrix;
}
inline Matrix4x4 operator/( const Matrix4x4& M, float S )
{
    Matrix4x4 matrix;
    float reciprocal = 1.0F / S;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j )
        {
            matrix.m[i][j] = M.m[i][j] * reciprocal;
        }
    }
    return matrix;
}
END_EGEG
#endif /// !INCLUDED_EGEG_MATH_HEADER_
/// EOF
