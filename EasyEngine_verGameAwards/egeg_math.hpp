///
/// @file   egeg_math.hpp
/// @author î¬èÍ
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

    Vector2D operator-() const noexcept { return Vector2D{ -x, -y }; }
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

// 
/*===========================================================================*/
#include "egeg_math.inl"
END_EGEG
#endif /// INCLUDED_EGEG_MATH_HEADER_
/// EOF
