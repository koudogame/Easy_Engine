///
/// @file   geometry_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include <type_traits>
#include <wrl.h>
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   GeometryShader
/// @brief   パイプライン構成オブジェクト「ジオメトリシェーダー」
/// @details 派生クラスは、自身の扱うジオメトリシェーダ―ファイルを<br>
///          static constexpr const char* kGSFileName<br>
///          として定義して下さい。ShaderLoaderで利用します。
///
class GeometryShader :
    public Shader
{
public :
    template <class ShaderType>
    GeometryShader( ShaderType&& Shader ) :
        shader_( std::forward<ShaderType>(Shader) )
    {
    }
    virtual ~GeometryShader() = default;

private :
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
