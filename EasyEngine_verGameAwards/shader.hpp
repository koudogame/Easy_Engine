///
/// @file   shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_

#include <d3d11.h>
#include "material.hpp"

BEGIN_EGEG

///
/// @class  Shader
/// @brief  シェーダ―オブジェクト基底
///
class Shader
{
public :
    Shader() = default;
    virtual ~Shader() = default;
    Shader( const Shader& ) = default;
    Shader& operator=( const Shader& ) = default;
    Shader( Shader&& ) = default;
    Shader& operator=( Shader&& ) = default;

    ///< パイプラインにシェーダ―を設定
    virtual void setShaderOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< パイプラインにシェーダ―リソースを設定
    virtual void setShaderResourcesOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< パイプラインに定数バッファを設定
    virtual void setConstantBuffersOnPipeline( ID3D11DeviceContext* ) = 0;
    ///< パイプラインにサンプラーを設定
    virtual void setSamplersOnPipeline( ID3D11DeviceContext* ) = 0;

    ///< シェーダーにマテリアルをセット
    virtual void setMaterial( const Material& Material ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
