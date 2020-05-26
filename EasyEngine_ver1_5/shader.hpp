///
/// @file   shader.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_

#include <memory> ///< シェーダ―オブジェクトのハンドラ
#include <d3d11.h>
#include "return_value.hpp"
#include "vertex.hpp"
#include "material.hpp"

BEGIN_EGEG

#define DECLARATION_SHADER_MEMBER( ShaderClassName ) \
public : static std::unique_ptr<ShaderClassName> create(); DetailedReturnValue<bool> shading( ID3D11DeviceContext*, const VertexData&, const Material& ) override; private :

///
/// @class   IShader
/// @brief   シェーダ―インタフェイス
/// @details 注意点
///             各派生クラスは、static std::unique_ptr<T> create() としてシェーダ―オブジェクトの生成処理を定義して下さい。 <br>
///             頂点シェーダ―の定数バッファは スロット0 ~ スロット2 は以下のように設定されます。 <br>
///                 b0 : 射影変換行列( DirectX::XMFLOAT4X4 ) <br>
///                 b1 : ビュー変換行列( DirectX::XMFLOAT4X4 ) <br>
///                 b2 : ワールド変換行列( DirectX::XMFLOAT4X4 )
///
class IShader
{
public :
    using VertexData = Property<TagVertexPosition, TagVertexUV, TagVertexNormal>;
    virtual ~IShader() = default;

    ///
    /// @brief  シェーディング
    ///
    /// @param[in] DC       : デバイスコンテキスト
    /// @param[in] Vertices : 頂点データ
    /// @param[in] Material : マテリアル
    ///
    /// @return true : 成功　false : 失敗
    ///
    virtual DetailedReturnValue<bool> shading( ID3D11DeviceContext* DC, const VertexData& Vertices, const Material& Material ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
