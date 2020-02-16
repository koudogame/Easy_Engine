///
/// @file   egeg_math.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MATH_HEADER_
#define INCLUDED_EGEG_MATH_HEADER_
#include <DirectXMath.h>
#include "egeg.hpp"
BEGIN_EGEG
// Vector2D 
/*===========================================================================*/
struct Vector2D : 
    public DirectX::XMFLOAT2
{
    Vector2D() = default;

    Vector2D( const Vector2D& ) = default;
    Vector2D& operator=( const Vector2D& ) = default;

    Vector2D( Vector2D&& ) = default;
    Vector2D& operator=( Vector2D&& ) = default;

    explicit constexpr Vector2D( float S ) noexcept : XMFLOAT2( S, S ) {}
    constexpr Vector2D( float X, float Y ) noexcept : XMFLOAT2( X, Y ) {}

    Vector2D( DirectX::FXMVECTOR V ) noexcept;
    Vector2D& operator=( DirectX::FXMVECTOR V ) noexcept;

    operator DirectX::XMVECTOR() const noexcept;
    operator bool() const noexcept;

    Vector2D operator-() const noexcept;
    bool operator==( DirectX::FXMVECTOR V ) const noexcept;
    bool operator!=( DirectX::FXMVECTOR V ) const noexcept;

    Vector2D& operator+=( DirectX::FXMVECTOR V ) noexcept;
    Vector2D& operator-=( DirectX::FXMVECTOR V ) noexcept;
    Vector2D& operator*=( DirectX::FXMVECTOR V ) noexcept;
    Vector2D& operator/=( DirectX::FXMVECTOR V ) noexcept;
    Vector2D& operator*=( float S ) noexcept;
    Vector2D& operator/=( float S ) noexcept;

    float dot( const DirectX::FXMVECTOR V ) const noexcept;
    float cross( const DirectX::FXMVECTOR V ) const noexcept;
    float length() const noexcept;
    float lengthSquared() const noexcept;
};

// Vector3D
/*===========================================================================*/
struct Vector3D :
    public DirectX::XMFLOAT3
{
    Vector3D() = default;

    Vector3D( const Vector3D& ) = default;
    Vector3D& operator=( const Vector3D& ) = default;

    Vector3D( Vector3D&& ) = default;
    Vector3D& operator=( Vector3D&& ) = default;

    explicit constexpr Vector3D( float S ) noexcept : XMFLOAT3( S, S, S ) {}
    constexpr Vector3D( float X, float Y, float Z ) noexcept : XMFLOAT3( X, Y, Z ) {}

    Vector3D( DirectX::FXMVECTOR V ) noexcept;
    Vector3D& operator=( DirectX::FXMVECTOR V ) noexcept;

    operator DirectX::XMVECTOR() const noexcept;
    operator bool() const noexcept;

    Vector3D operator-() const noexcept;
    bool operator==( DirectX::FXMVECTOR V ) const noexcept;
    bool operator!=( DirectX::FXMVECTOR V ) const noexcept;

    Vector3D& operator+=( DirectX::FXMVECTOR V ) noexcept;
    Vector3D& operator-=( DirectX::FXMVECTOR V ) noexcept;
    Vector3D& operator*=( DirectX::FXMVECTOR V ) noexcept;
    Vector3D& operator/=( DirectX::FXMVECTOR V ) noexcept;
    Vector3D& operator*=( float S ) noexcept;
    Vector3D& operator/=( float S ) noexcept;

    float dot( DirectX::FXMVECTOR  V ) const noexcept;
    DirectX::XMVECTOR cross( DirectX::FXMVECTOR V ) const noexcept;
    float length() const noexcept;
    float lengthSquared() const noexcept;
};
// Vector4D
/*===========================================================================*/
struct Vector4D :
    public DirectX::XMFLOAT4
{
    Vector4D() = default;

    Vector4D( const Vector4D& ) = default;
    Vector4D& operator=( const Vector4D& ) = default;

    Vector4D( Vector4D&& ) = default;
    Vector4D& operator=( Vector4D&& ) = default;

    explicit constexpr Vector4D( float S ) noexcept : XMFLOAT4( S, S, S, S ) {}
    constexpr Vector4D( float X, float Y, float Z, float W ) : XMFLOAT4( X, Y, Z, W ) {}

    Vector4D( DirectX::FXMVECTOR V ) noexcept;
    Vector4D& operator=( DirectX::FXMVECTOR V ) noexcept;

    operator DirectX::XMVECTOR() const noexcept;
    operator bool() const noexcept;

    Vector4D operator-() const noexcept;
    bool operator==( DirectX::FXMVECTOR V ) const noexcept;
    bool operator!=( DirectX::FXMVECTOR V ) const noexcept;

    Vector4D& operator+=( DirectX::FXMVECTOR V ) noexcept;
    Vector4D& operator-=( DirectX::FXMVECTOR V ) noexcept;
    Vector4D& operator*=( DirectX::FXMVECTOR V ) noexcept;
    Vector4D& operator/=( DirectX::FXMVECTOR V ) noexcept;
    Vector4D& operator*=( float S ) noexcept;
    Vector4D& operator/=( float S ) noexcept;

    float dot( DirectX::FXMVECTOR V ) const noexcept;
    // A 4D cross-product is not well-defined
    float length() const noexcept;
    float lengthSquared() const noexcept;
};

// Matrix3x3
/*===========================================================================*/

// Matrix4x3
/*===========================================================================*/

// Matrix3x4
/*===========================================================================*/

// Matrix4x4
/*===========================================================================*/

#include "egeg_math.inl"
END_EGEG
#endif /// INCLUDED_EGEG_MATH_HEADER_
/// EOF