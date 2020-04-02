///
/// @file   material.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EG_EG_MATERIAL_HEADER_
#define INCLUDED_EG_EG_MATERIAL_HEADER_

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "table.hpp"

BEGIN_EGEG

using Tag_MaterialDiffuseColor    = Field<DirectX::XMFLOAT3, 0U>;
using Tag_MaterialSpecularColor   = Field<DirectX::XMFLOAT3, 1U>;
using Tag_MaterialAmbientColor    = Field<DirectX::XMFLOAT3, 2U>;
using Tag_MaterialTransparency    = Field<float, 3U>;
using Tag_MaterialRefractiveIndex = Field<float, 4U>;
using Tag_MaterialDiffuseTexture  = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 0U>;
using Tag_MaterialSpecularTexture = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 1U>;
using Tag_MaterialAmbientTexture  = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 2U>;
using Tag_MaterialBumpTexture     = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 3U>;
using Tag_MaterialTransparencyTexture = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 4U>;
using Tag_MaterialreflectionTexture   = Field<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, 5U>;

using Material = Table<
    Tag_MaterialDiffuseColor,
    Tag_MaterialSpecularColor,   
    Tag_MaterialAmbientColor,
    Tag_MaterialTransparency,
    Tag_MaterialRefractiveIndex,
    Tag_MaterialDiffuseTexture,
    Tag_MaterialSpecularTexture,
    Tag_MaterialAmbientTexture,
    Tag_MaterialBumpTexture,
    Tag_MaterialTransparencyTexture,
    Tag_MaterialreflectionTexture>;

END_EGEG
#endif /// !INCLUDED_EG_EG_MATERIAL_HEADER_
/// EOF#pragma once
