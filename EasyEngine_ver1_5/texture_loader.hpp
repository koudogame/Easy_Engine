///
/// @file   texture_loader.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_

#include <string>
#include <wrl.h>
#include <d3d11.h>
#include "rendering_manager_child.hpp"
#include "return_value.hpp"


BEGIN_EGEG

///
/// @class TextureLoader
/// @brief テクスチャローダー
///
class TextureLoader :
    public RenderingManagerChild
{
public :
    ///
    /// @brief ファイルからテクスチャリソースを読み込む
    ///
    /// @param[in] TextureFilePath : 読み込むテクスチャリソースファイルのパス
    ///
    /// @return 読み込んだテクスチャリソース
    ///
    DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> load(
        const std::string& TextureFilePath );
};

END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
