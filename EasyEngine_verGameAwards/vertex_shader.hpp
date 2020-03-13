///
/// @file   vertex_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#include "shader.hpp"
#include "vertex_binder.hpp"
BEGIN_EGEG
///
/// @class   VertexShader
/// @brief   パイプライン構成オブジェクト「頂点シェーダ―」
/// @details 派生クラスは、必ずデストラクタより前にシェーダーオブジェクト、及び入力レイアウトオブジェクトを生成し保持するものとします。<br>
///          コンストラクタでの処理を推奨します。
///
class VertexShader :
    public Shader
{
public :
    virtual ~VertexShader() { shader_->Release(); input_layout_->Release(); }
    VertexShader( const VertexShader& Lhs )
    {
        shader_ = Lhs.shader_;
        shader_->AddRef();
        input_layout_ = Lhs.input_layout_;
        input_layout_->AddRef();
    }
    VertexShader& operator=( const VertexShader& Lhs )
    {
        Lhs.shader_->AddRef();
        Lhs.input_layout_->AddRef();

        if( shader_ ) shader_->Release();
        if( input_layout_ ) input_layout_->Release();
        shader_ = Lhs.shader_;
        input_layout_ = Lhs.input_layout_;
    }

    ///< 頂点の入力レイアウトにバインドするオブジェクトを取得する
    virtual VertexBinder getVertexBinder() const = 0;

protected :
    ID3D11VertexShader* shader_ = nullptr;
    ID3D11InputLayout*  input_layout_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_HEADER_
/// EOF
