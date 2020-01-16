///
/// @file    texture_manager.hpp
/// @author  板場
///          
/// @brief   テクスチャマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          このクラスを使用して読み込んだテクスチャは、必ずこのクラスで開放してください。
///
#ifndef INCLUDED_TEXTURE_MANAGER_HEADER_
#define INCLUDED_TEXTURE_MANAGER_HEADER_
#include <string>
#include <unordered_map>
#include "easy_engine.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class TextureManager
{
public :
    ///
    /// @brief  インスタンスへのアクセス
    ///
    /// @return インスタンス
    ///
    static TextureManager* instance() { return instance_; }

    ///
    /// @brief   テクスチャのロード
    /// @details キャッシュに読み込み済みテクスチャがある場合、そのコピーを返却します。
    ///
    /// @param[in] FilePath : 読み込むテクスチャのファイルパス
    /// @param[out] ppTexture : 読み込んだテクスチャを受け取るインターフェイス
    ///
    /// @return 読み込み成功[ true ] 読み込み失敗[ false ]
    ///
    bool load( const std::wstring& FilePath, ITexture** ppTexture );
    ///
    /// @brief   テクスチャの開放
    /// @details 参照者のデクリメントを行い、参照者がいなくなった時点で開放します。<br>
    ///          引数で受け取ったインターフェイスには、nullptrが代入されます。
    ///
    /// @param[inout] ppTexture : 開放するテクスチャ
    ///
    void release( ITexture** ppTexture );

    ///
    /// @brief   インスタンスの生成
    ///
    /// @param[in] Creator : 生成者
    /// @param[in] pTextureLoader : 使用するテクスチャローダー
    ///
    static void create( const EasyEngine& Creator, ITextureLoader* pTextureLoader );
    ///
    /// @brief  インスタンスの破棄
    ///
    /// @param[in] Deleter : 破棄者
    ///
    static void destroy( const EasyEngine& Deleter );
    ~TextureManager();

    TextureManager( const TextureManager& ) = delete;
    TextureManager& operator=( const TextureManager& ) = delete;
private :
    TextureManager( ITextureLoader* );
    static TextureManager* instance_;
    ITextureLoader* p_loader_;
    std::unordered_map<std::wstring, ITexture*> cache_;   /// テクスチャリソースのキャッシュ
};
END_EGEG
#endif /// !INCLUDED_TEXTURE_MANAGER_HEADER_
/// EOF
