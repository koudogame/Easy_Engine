///
/// @file   vertex.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_VERTEX_HEADER_
#define INCLUDED_EGEG_VERTEX_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "property.hpp"

BEGIN_EGEG

using VertexPositionType = DirectX::XMFLOAT3;
using VertexUVType       = DirectX::XMFLOAT2;
using VertexNormalType   = DirectX::XMFLOAT3;

using TagVertexPosition = Tag<Microsoft::WRL::ComPtr<ID3D11Buffer>, 0U>;
using TagVertexUV       = Tag<Microsoft::WRL::ComPtr<ID3D11Buffer>, 1U>;
using TagVertexNormal   = Tag<Microsoft::WRL::ComPtr<ID3D11Buffer>, 2U>;
using TagVertexIndex    = Tag<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U>;

using Vertex = Property<
    TagVertexPosition,
    TagVertexUV,
    TagVertexNormal,
    TagVertexIndex >;

END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_HEADER_
/// EOF
