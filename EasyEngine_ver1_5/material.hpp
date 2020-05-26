///
/// @file   material.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_MATERIAL_HEADER_
#define INCLUDED_EGEG_MATERIAL_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "property.hpp"

BEGIN_EGEG

using TagMaterialDiffuseColor        = Tag<DirectX::XMFLOAT3, 0U>;
using TagMaterialSpecularColor       = Tag<DirectX::XMFLOAT3, 1U>;
using TagMaterialAmbientColor        = Tag<DirectX::XMFLOAT3, 2U>;
using TagMaterialTransparency        = Tag<float, 0U>;
using TagMaterialRefractiveIndex     = Tag<float, 1U>;
using TagMaterialDiffuseTexture      = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 0U>;
using TagMaterialSpecularTexture     = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 1U>;
using TagMaterialAmbientTexture      = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 2U>;
using TagMaterialBumpTexture         = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 3U>;
using TagMaterialTransparencyTexture = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 4U>;
using TagMaterialReflectionTexture   = Tag<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 5U>;

using Material = Property<
    TagMaterialDiffuseColor,
    TagMaterialSpecularColor,   
    TagMaterialAmbientColor,
    TagMaterialTransparency,
    TagMaterialRefractiveIndex,
    TagMaterialDiffuseTexture,
    TagMaterialSpecularTexture,
    TagMaterialAmbientTexture,
    TagMaterialBumpTexture,
    TagMaterialTransparencyTexture,
    TagMaterialReflectionTexture >;

END_EGEG
#endif /// !INCLUDED_EGEG_MATERIAL_HEADER_
/// EOF
