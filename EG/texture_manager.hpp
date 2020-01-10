///
/// @file    texture_manager.hpp
/// @author  板場
///          
/// @brief   テクスチャ管理者
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          このクラスのload関数を使用して読み込んだテクスチャは、<br>
///          このクラスのrelease関数を使用して解放してください。
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
    /// @brief   画像を読み込みます。
    /// @details キャッシュにない場合、新規に読み込みます。<br>
    ///          キャッシュにある場合、そのコピーを返却します。
    ///
    /// @param[in] FilePath : 画像のファイルパス
    /// @param[out] ppOutTexture : 読み込んだ画像を受け取るインターフェイス
    ///
    /// @return 読み込みに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool load( const wchar_t* FilePath, ITexture** ppOutTextur );

    ///
    /// @brief   画像の解放を行います。
    /// @details 引数のインターフェイスには、解放後nullptrを代入します。<br>
    ///          キャッシュから削除されるタイミングは参照者がいなくなった時です。
    ///
    /// @param[inout] ppTexture : 解放対象のテクスチャ
    ///
    void release( ITexture** ppTexture );
    

    ~TextureManager()
    {
        p_loader_->release();
    }
private :
    TextureManager();

    ITextureLoader* p_loader_;
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_MANAGER_HEADER_
/// EOF
