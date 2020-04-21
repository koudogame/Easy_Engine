///
/// @file   model_pixel_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_MODEL_PIXEL_SHADER_HEADER_
#define INCLUDED_MODEL_PIXEL_SHADER_HEADER_

#include "pixel_shader.hpp"

///
/// @class  ModelPixelShader
/// @brief  3Dモデル用ピクセルシェーダ―
///
class ModelPixelShader :
    public EGEG PixelShader
{
public :
    static constexpr const char* kPSFileName = "model_ps.cso";

    template <class ShaderType>
    ModelPixelShader( ShaderType&& PS ) :
        PixelShader( std::forward<ShaderType>(PS) )
    {
    }

    void setShaderOnPipeline( ID3D11DeviceContext* ) override;
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* ) override;
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* ) override;
    void setSamplersOnPipeline( ID3D11DeviceContext* ) override;
    void setMaterial( const EGEG Material& ) override;
};

#endif /// !INCLUDED_MODEL_PIXEL_SHADER_HEADER_
/// EOF
