///
/// @file   vertex.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_VERTEX_HEADER_
#define INCLUDED_EGEG_VERTEX_HEADER_

#include <d3d11.h>
#include <wrl.h>
#include "egeg.hpp"
#include "table.hpp"

BEGIN_EGEG

using VertexPositionType = DirectX::XMFLOAT3;
using VertexUVType       = DirectX::XMFLOAT2;
using VertexNormalType   = DirectX::XMFLOAT3;

using Tag_VertexPosition = Field<Microsoft::WRL::ComPtr<ID3D11Buffer>, 0U>;
using Tag_VertexUV       = Field<Microsoft::WRL::ComPtr<ID3D11Buffer>, 1U>;
using Tag_VertexNormal   = Field<Microsoft::WRL::ComPtr<ID3D11Buffer>, 2U>;
using Tag_VertexIndex    = Field<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U>;

using Vertex = Table<
    Tag_VertexPosition,
    Tag_VertexUV,
    Tag_VertexNormal,
    Tag_VertexIndex>;

END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_HEADER_
/// EOF
