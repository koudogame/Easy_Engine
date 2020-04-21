///
/// @file   sprite_pixel_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_SPRITE_PIXEL_SHADER_HEADER_
#define INCLUDED_SPRITE_PIXEL_SHADER_HEADER_

#include "pixel_shader.hpp"

///
/// @class  SpritePixelShader
/// @brief  スプライト用ピクセルシェーダ―
///
class SpritePixelShader :
    public EGEG PixelShader
{
public :
    static constexpr const char* kPSFileName = "sprite_ps.cso";

    template <class ShaderType>
    SpritePixelShader( ShaderType&& PS ) :
        PixelShader( std::forward<ShaderType>(PS) )
    {
    }

    void setShaderOnPipeline( ID3D11DeviceContext* ) override;
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* ) override;
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* ) override;
    void setSamplersOnPipeline( ID3D11DeviceContext* ) override;
    void setMaterial( const EGEG Material& ) override;
};

#endif /// !INCLUDED_SPRITE_PIXEL_SHADER_HEADER_
/// EOF
