///
/// @file    texture_manager.hpp
/// @author  板場
///          
/// @brief   テクスチャ管理者
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。
///
#ifndef INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
#include <unordered_map>
#include "texture_loader.hpp"
BEGIN_EG_EG
class TextureManager
{
public :
    static TextureManager* instance() { static TextureManager i; return&i; }

    ///
    /// @brief   画像を取得します。
    /// @details キャッシュに画像がない場合(新規の取得の場合)画像を読み込みます。<br>
    ///          キャッシュに画像がある場合、そのコピーを返却します。
    ///
    /// @param[in] FilePath : 画像のファイルパス
    /// @param[out] ppOutTexture : 読み込んだ画像を受け取るインターフェイス
    ///
    /// @return 取得に成功した場合[ true ] 失敗した場合[ false ]を返却します。返却します。
    ///
    bool get( const wchar_t* FilePath, ITexture** ppOutTextur );

private :
    TextureManager() = default;

    ITextureLoader* loader_ = nullptr;
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
/// EOF
