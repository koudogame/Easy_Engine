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
}
inline Vector2D::operator DirectX::XMVECTOR() const noexcept
{
    return DirectX::XMLoadFloat2( this );
}
inline Vector2D::operator bool() const noexcept
{
    return DirectX::XMVector2IsInfinite( *this );
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
}
inline Vector2D& Vector2D::operator-=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorSubtract( *this, V );
}
inline Vector2D& Vector2D::operator*=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorMultiply( *this, V );
}
inline Vector2D& Vector2D::operator/=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorDivide( *this, V );
}
inline Vector2D& Vector2D::operator*=( float S ) noexcept
{
    DirectX::XMVECTOR temp = DirectX::XMLoadFloat2( &DirectX::XMFLOAT2{S, S} );
    *this = DirectX::XMVectorMultiply( *this, temp );
}
inline Vector2D& Vector2D::operator/=( float S ) noexcept
{
    DirectX::XMVECTOR temp = DirectX::XMLoadFloat2( &DirectX::XMFLOAT2{S, S} );
    *this = DirectX::XMVectorDivide( *this, temp );
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

#endif /// INCLUDED_EGEG_MATH_INLINE_
#endif /// INCLUDED_EGEG_MATH_HEADER_
/// EOF
