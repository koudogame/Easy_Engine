///
/// @file   shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_
#include <d3d11.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  Shader
/// @brief  シェーダ―オブジェクト基底
///
class Shader
{
public :
    virtual ~Shader() = default;

    ///< パイプラインにシェーダ―オブジェクトを設定
    virtual void setShaderOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< パイプラインにシェーダ―リソースビューを設定
    virtual void setShaderResourceViewsOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< パイプラインに定数バッファを設定
    virtual void setConstantBuffersOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;
    ///< パイプラインにサンプラーを設定
    virtual void setSamplersOnPipeline( ID3D11DeviceContext* Pipeline ) = 0;

    ///
    /// @brief  パイプラインにシェーダーステージを設定
    ///
    /// @param[in] Pipeline : ステージを設定するパイプライン
    ///
    void setShaderStageOnPipeline( ID3D11DeviceContext* Pipeline )
    {
        setShaderOnPipeline( Pipeline );
        setShaderResourceViewsOnPipeline( Pipeline );
        setConstantBuffersOnPipeline( Pipeline );
        setSamplersOnPipeline( Pipeline );
    }
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
