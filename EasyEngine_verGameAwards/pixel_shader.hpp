///
/// @file   pixel_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   PixelShader
/// @brief   パイプライン構成オブジェクト「ピクセルシェーダー」
/// @details 派生クラスは、必ずデストラクタより前にシェーダーオブジェクトを生成し保持するものとします。<br>
///          コンストラクタでの処理を推奨します。
///
class PixelShader :
    public Shader
{
public :
    virtual ~PixelShader() { shader_->Release(); }
    PixelShader( const PixelShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
    }
    PixelShader& operator=( const PixelShader& Lhs )
    {
        Lhs.shader_->AddRef();

        if( shader_ ) shader_->Release();
        shader_ = Lhs.shader_;
    }
    
protected :
    ID3D11PixelShader* shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
