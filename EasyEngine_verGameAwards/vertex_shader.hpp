///
/// @file   vertex_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_HEADER_
#include <type_traits>
#include <wrl.h>
#include "shader.hpp"
#include "vertex_binder.hpp"
BEGIN_EGEG
///
/// @class   VertexShader
/// @brief   パイプライン構成オブジェクト「頂点シェーダ―」
/// @details 派生クラスは、自身の扱う頂点シェーダ―ファイルと頂点入力レイアウトをそれぞれ<br>
///          static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[]<br>
///          static constexpr const char* kVSFileName<br>
///          として定義して下さい。ShaderLoaderで利用します。
///
class VertexShader :
    public Shader
{
public :
    template <class ShaderType,
              class InputLayoutType>
    VertexShader( ShaderType&& Shader, InputLayoutType&& InputLayout ) :
        shader_( std::forward<ShaderType>(Shader) ),
        input_layout_( std::forward<InputLayoutType>(InputLayout) )
    {
    }
    virtual ~VertexShader() = default;

    ///< 頂点の入力レイアウトにバインドするオブジェクトを取得する
    virtual VertexBinder getVertexBinder() const = 0;

    ///< パイプラインに頂点入力レイアウトをセット
    void setInputLayoutOnPipeline( ID3D11DeviceContext* ImmediateContext ) 
    {
        ImmediateContext->IASetInputLayout( input_layout_.Get() );
    }

protected :
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_ = nullptr;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  input_layout_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_HEADER_
/// EOF
