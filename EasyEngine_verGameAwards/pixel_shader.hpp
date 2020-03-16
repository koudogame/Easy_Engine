///
/// @file   pixel_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_PIXEL_SHADER_HEADER_
#include <type_traits>
#include <wrl.h>
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   PixelShader
/// @brief   パイプライン構成オブジェクト「ピクセルシェーダー」
/// @details 派生クラスは、自身の扱うピクセルシェーダ―ファイルを<br>
///          static constexpr const char* kPSFileName<br>
///          として定義して下さい。ShaderLoaderで利用します。
///
class PixelShader :
    public Shader
{
public :
    template <class ShaderType>
    PixelShader( ShaderType&& Shader ) :
        shader_( std::forward<ShaderType>(Shader) )
    {
    }
    virtual ~PixelShader() = default;
    
protected :
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_PIXEL_SHADER_HEADER_
/// EOF
