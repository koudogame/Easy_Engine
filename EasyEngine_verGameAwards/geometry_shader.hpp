///
/// @file   geometry_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
#include "shader.hpp"
BEGIN_EGEG
///
/// @class   GeometryShader
/// @brief   パイプライン構成オブジェクト「ジオメトリシェーダー」
/// @details 派生クラスは、必ずデストラクタより前にシェーダーオブジェクトを生成し保持するものとします。<br>
///          コンストラクタでの処理を推奨します。
///
class GeometryShader :
    public Shader
{
public :
    virtual ~GeometryShader() { shader_->Release(); }
    GeometryShader( const GeometryShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
    }
    GeometryShader& operator=( const GeometryShader& Lhs )
    {
        Lhs.shader_->AddRef();

        if( shader_ ) shader_->Release();
        shader_ = Lhs.shader_;
    }

private :
    ID3D11GeometryShader* shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_HEADER_
/// EOF
