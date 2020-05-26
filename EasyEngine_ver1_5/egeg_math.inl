///
/// @file   egeg_math.inl
/// @author î¬èÍ
///
#ifdef  INCLUDED_EGEG_MATH_HEADER_
#ifndef INCLUDED_EGEG_MATH_INLINE_
#define INCLUDED_EGEG_MATH_INLINE_


/******************************************************************************

	Vector2D

******************************************************************************/
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
    Vector2D temp{ DirectX::XMVector2Dot(*this, V) };
    return temp.x;
}
inline float Vector2D::cross( const DirectX::FXMVECTOR V ) const noexcept
{
    Vector2D temp{ DirectX::XMVector2Cross(*this, V) };
    return temp.x;
}
inline float Vector2D::length() const noexcept
{
    Vector2D temp{ DirectX::XMVector2Length(*this) };
    return temp.x;
}
inline float Vector2D::lengthSquared() const noexcept
{
    Vector2D temp{ DirectX::XMVector2LengthSq(*this) };
    return temp.x;
}
inline Vector2D operator+( const Vector2D& L, const Vector2D& R ) noexcept
{
    return Vector2D{ DirectX::XMVectorAdd(L, R) };
}
inline Vector2D operator-( const Vector2D& L, const Vector2D& R ) noexcept
{
    return Vector2D{ DirectX::XMVectorSubtract(L, R) };
}
inline Vector2D operator*( const Vector2D& L, const Vector2D& R ) noexcept
{
    return Vector2D{ DirectX::XMVectorMultiply(L,R) };
}
inline Vector2D operator/( const Vector2D& L, const Vector2D& R ) noexcept
{
    return Vector2D{ DirectX::XMVectorDivide(L, R) };
}
inline Vector2D operator*( const Vector2D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector2D{ XMVectorMultiply(L, XMLoadFloat2(&XMFLOAT2{R, R})) };
}
inline Vector2D operator/( const Vector2D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector2D{ XMVectorDivide(L, XMLoadFloat2(&XMFLOAT2{R, R})) };
}


/******************************************************************************

	Vector3D

******************************************************************************/
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
    Vector3D temp{ DirectX::XMVector3Dot(*this, V) };
    return temp.x;
}
inline DirectX::XMVECTOR Vector3D::cross( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector3Cross( *this, V );
}
inline float Vector3D::length() const noexcept
{
    Vector3D temp{ DirectX::XMVector3Length(*this) };
    return temp.x;
}
inline float Vector3D::lengthSquared() const noexcept
{
    Vector3D temp{ DirectX::XMVector3LengthSq(*this) };
    return temp.x;
}
inline Vector3D operator+( const Vector3D& L, const Vector3D& R ) noexcept
{
    return Vector3D{ DirectX::XMVectorAdd(L, R) };
}
inline Vector3D operator-( const Vector3D& L, const Vector3D& R ) noexcept
{
    return Vector3D{ DirectX::XMVectorSubtract(L, R) };
}
inline Vector3D operator*( const Vector3D& L, const Vector3D& R ) noexcept
{
    return Vector3D{ DirectX::XMVectorMultiply(L, R) };
}
inline Vector3D operator/( const Vector3D& L, const Vector3D& R ) noexcept
{
    return Vector3D{ DirectX::XMVectorDivide(L, R) };
}
inline Vector3D operator*( const Vector3D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector3D{ XMVectorMultiply(L, XMLoadFloat3(&XMFLOAT3{R, R, R})) };
}
inline Vector3D operator/( const Vector3D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector3D{ XMVectorDivide(L, XMLoadFloat3(&XMFLOAT3{R, R, R})) };
}

/******************************************************************************

	Vector4D

******************************************************************************/
inline Vector4D::Vector4D( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat4( this, V );
}
inline Vector4D& Vector4D::operator=( DirectX::FXMVECTOR V ) noexcept
{
    DirectX::XMStoreFloat4( this, V );
    return *this;
}
inline Vector4D::operator DirectX::XMVECTOR() const noexcept
{
    return DirectX::XMLoadFloat4( this );
}
inline Vector4D::operator bool() const noexcept
{
    return DirectX::XMVector4IsInfinite( *this );
}
inline Vector4D Vector4D::operator-() const noexcept
{
    return Vector4D( -x, -y, -z, -w );
}
inline bool Vector4D::operator==( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector4Equal( *this, V );
}
inline bool Vector4D::operator!=( DirectX::FXMVECTOR V ) const noexcept
{
    return DirectX::XMVector4NotEqual( *this, V );
}
inline Vector4D& Vector4D::operator+=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorAdd( *this, V );
    return *this;
}
inline Vector4D& Vector4D::operator-=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorSubtract( *this, V );
    return *this;
}
inline Vector4D& Vector4D::operator*=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorMultiply( *this, V );
    return *this;
}
inline Vector4D& Vector4D::operator/=( DirectX::FXMVECTOR V ) noexcept
{
    *this = DirectX::XMVectorDivide( *this, V );
    return *this;
}
inline Vector4D& Vector4D::operator*=( float S ) noexcept
{
    using namespace DirectX;
    return *this *= XMLoadFloat4( &XMFLOAT4{S, S, S, S} );
}
inline Vector4D& Vector4D::operator/=( float S ) noexcept
{
    using namespace DirectX;
    return *this /= XMLoadFloat4( &XMFLOAT4{S, S, S, S} );
}
inline float Vector4D::dot( DirectX::FXMVECTOR V ) const noexcept
{
    Vector2D temp{ DirectX::XMVector4Dot(*this, V) };
    return temp.x;
}
inline float Vector4D::length() const noexcept
{
    Vector2D temp{ DirectX::XMVector4Length(*this) };
    return temp.x;
}
inline float Vector4D::lengthSquared() const noexcept
{
    Vector2D temp{ DirectX::XMVector4LengthSq(*this) };
    return temp.x;
}
inline Vector4D operator+( const Vector4D& L, const Vector4D& R ) noexcept
{
    return Vector4D{ DirectX::XMVectorAdd(L, R) };
}
inline Vector4D operator-( const Vector4D& L, const Vector4D& R ) noexcept
{
    return Vector4D{ DirectX::XMVectorSubtract(L,R) };
}
inline Vector4D operator*( const Vector4D& L, const Vector4D& R ) noexcept
{
    return Vector4D{ DirectX::XMVectorMultiply(L,R) };
}
inline Vector4D operator/( const Vector4D& L, const Vector4D& R ) noexcept
{
    return Vector4D{ DirectX::XMVectorDivide(L, R) };
}
inline Vector4D operator*( const Vector4D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector4D{ XMVectorMultiply(L, XMLoadFloat4(&XMFLOAT4{R, R, R, R})) };
}
inline Vector4D operator/( const Vector4D& L, const float R ) noexcept
{
    using namespace DirectX;
    return Vector4D{ XMVectorDivide(L, XMLoadFloat4(&XMFLOAT4{R, R, R, R})) };
}


/******************************************************************************

	Matrix3x3

******************************************************************************/
inline Matrix3x3::Matrix3x3( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat3x3( this, M );
}
inline Matrix3x3& Matrix3x3::operator=( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat3x3( this, M );
    return *this;
}
inline Matrix3x3::operator DirectX::XMMATRIX() const noexcept
{
    return DirectX::XMLoadFloat3x3( this );
}


/******************************************************************************

	Matrix4x3

******************************************************************************/
inline Matrix4x3::Matrix4x3( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat4x3( this, M );
}
inline Matrix4x3& Matrix4x3::operator=( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat4x3( this, M );
    return *this;
}
inline Matrix4x3::operator DirectX::XMMATRIX() const noexcept
{
    return DirectX::XMLoadFloat4x3( this );
}


/******************************************************************************

	Matrix3x4

******************************************************************************/
inline Matrix3x4::Matrix3x4( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat3x4( this, M );
}
inline Matrix3x4& Matrix3x4::operator=( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat3x4( this, M );
    return *this;
}
inline Matrix3x4::operator DirectX::XMMATRIX() const noexcept
{
    return DirectX::XMLoadFloat3x4( this );
}


/******************************************************************************

	Matrix4x4

******************************************************************************/
inline Matrix4x4::Matrix4x4( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat4x4( this, M );
}
inline Matrix4x4& Matrix4x4::operator=( DirectX::FXMMATRIX M ) noexcept
{
    DirectX::XMStoreFloat4x4( this, M );
    return *this;
}
inline Matrix4x4::operator DirectX::XMMATRIX() const noexcept
{
    return DirectX::XMLoadFloat4x4( this );
}

#endif /// !INCLUDED_EGEG_MATH_INLINE_
#endif /// !INCLUDED_EGEG_MATH_HEADER_
/// EOF
