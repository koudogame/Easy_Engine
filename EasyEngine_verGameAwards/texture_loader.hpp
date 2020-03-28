///
/// @file   texture_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_

#include "loader.hpp"
#include "detailed_returnvalue.hpp"

BEGIN_EGEG
///
/// @class  TextureLoader
/// @brief  テクスチャリソースのローダー
///
class TextureLoader :
    public Loader
{
public :
    TextureLoader( const Microsoft::WRL::ComPtr<ID3D11Device>& Device ) :
        Loader( Device )
    {
    }

    ///
    /// @brief  ファイルからテクスチャリソースを読み込む
    ///
    /// @param[in] FileName : 読み込むテクスチャのファイルパス
    ///
    /// @return 読み込んだテクスチャのシェーダ―リソースビュー
    ///
    DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> load(
        const std::wstring& FilePath );
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
/// EOF

