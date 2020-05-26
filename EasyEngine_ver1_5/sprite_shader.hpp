///
/// @file   sprite_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SPRITE_SHADER_HEADER_
#define INCLUDED_EGEG_SPRITE_SHADER_HEADER_

#include "shader.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  SpriteShader
/// @brief  スプライト用シェーダ―
///
class SpriteShader :
    public IShader
{
    DECLARATION_SHADER_MEMBER( SpriteShader )

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vs_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  il_;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  ps_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SPRITE_SHADER_HEADER_
/// EOF
