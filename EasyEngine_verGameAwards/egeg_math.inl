///
/// @file   egeg_math.inl
/// @author î¬èÍ
///
#ifdef INCLUDED_EGEG_MATH_HEADER_
#ifndef INCLUDED_EGEG_MATH_INLINE_
#define INCLUDED_EGEG_MATH_INLINE_
/*===========================================================================*/

inline Vector2D::Vector2D( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat2( this, V );
}
inline Vector2D& Vector2D::operator=( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat2( this, V );
    return *this;
}
inline Vector2D::operator DirectX::XMVECTOR() const noexcept
{
    return DirectX::XMLoadFloat2( this );
}
inline Vector2D::operator bool() const noexcept
{
    return DirectX::XMVector2IsInfinite( *this );
}
inline Vector2D Vector2D::operator-() const noexcept
{
    return Vector2D( -x, -y );
}
inline bool Vector2D::operator==( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector2Equal( *this, V );
}
inline bool Vector2D::operator!=( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector2NotEqual( *this, V );
}
inline Vector2D& Vector2D::operator+=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorAdd( *this, V );
    return *this;
}
inline Vector2D& Vector2D::operator-=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorSubtract( *this, V );
    return *this;
}
inline Vector2D& Vector2D::operator*=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorMultiply( *this, V );
    return *this;
}
inline Vector2D& Vector2D::operator/=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorDivide( *this, V );
    return *this;
}
inline Vector2D& Vector2D::operator*=( float S ) noexcept
{
    using namespace DirectX;
    return *this *= XMLoadFloat2( &XMFLOAT2{S, S} );
}
inline Vector2D& Vector2D::operator/=( float S ) noexcept
{
    using namespace DirectX;
    return *this /= XMLoadFloat2( &XMFLOAT2{S, S} );
}
inline float Vector2D::dot( const DirectX::FXMVECTOR V ) const noexcept
{
    Vector2D temp = DirectX::XMVector2Dot( *this, V );
    return temp.x;
}
inline float Vector2D::cross( const DirectX::FXMVECTOR V ) const noexcept
{
    Vector2D temp = DirectX::XMVector2Cross( *this, V );
    return temp.x;
}
inline float Vector2D::length() const noexcept
{
    Vector2D temp = DirectX::XMVector2Length( *this );
    return temp.x;
}
inline float Vector2D::lengthSquared() const noexcept
{
    Vector2D temp = DirectX::XMVector2LengthSq( *this );
    return temp.x;
}

/*===========================================================================*/

inline Vector3D::Vector3D( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat3( this, V );
}
inline Vector3D& Vector3D::operator=( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat3( this, V );
    return *this;
}
inline Vector3D::operator DirectX::XMVECTOR() const noexcept
{
    return DirectX::XMLoadFloat3( this );
}
inline Vector3D::operator bool() const noexcept
{
    return DirectX::XMVector3IsInfinite( *this );
}
inline Vector3D Vector3D::operator-() const noexcept
{
    return Vector3D( -x, -y, -z );
}
inline bool Vector3D::operator==( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector3Equal( *this, V );
}
inline bool Vector3D::operator!=( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector3NotEqual( *this, V );
}
inline Vector3D& Vector3D::operator+=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorAdd( *this, V );
    return *this;
}
inline Vector3D& Vector3D::operator-=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorSubtract( *this, V );
    return *this;
}
inline Vector3D& Vector3D::operator*=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorMultiply( *this, V );
    return *this;
}
inline Vector3D& Vector3D::operator/=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorDivide( *this, V );
    return *this;
}
inline Vector3D& Vector3D::operator*=( float S ) noexcept
{
    using namespace DirectX;
    return *this *= XMLoadFloat3( &XMFLOAT3{S, S, S} );
}
inline Vector3D& Vector3D::operator/=( float S ) noexcept
{
    using namespace DirectX;
    return *this /= XMLoadFloat3( &XMFLOAT3{S, S, S} );
}
inline float Vector3D::dot( DirectX::FXMVECTOR V ) const noexcept
{
    Vector3D temp = DirectX::XMVector3Dot( *this, V );
    return temp.x;
}
inline DirectX::XMVECTOR Vector3D::cross( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector3Cross( *this, V );
}
inline float Vector3D::length() const noexcept
{
    Vector3D temp = DirectX::XMVector3Length( *this );
    return temp.x;
}
inline float Vector3D::lengthSquared() const noexcept
{
    Vector3D temp = DirectX::XMVector3LengthSq( *this );
    return temp.x;
}

/*===========================================================================*/



#endif /// INCLUDED_EGEG_MATH_INLINE_
#endif /// INCLUDED_EGEG_MATH_HEADER_
/// EOF
