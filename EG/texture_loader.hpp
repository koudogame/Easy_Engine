///
/// @file    texture_loader.hpp
/// @author  板場
///          
/// @brief   テクスチャリソースローダーの基底クラス
/// @details 派生クラスは loadFromFileを実装して下さい。
/// 
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#include <unordered_map>
#include "interface.hpp"
BEGIN_EGEG
class ITexture;
class ITextureLoader :
    public SharedObject
{
public :
    ///
    /// @brief   テクスチャのロード
    /// @details キャッシュにある場合、コピーするためロード時間はかかりません。
    ///          キャッシュにない場合、ロード時間がかかります。
    ///
    /// @param[in] FilePath : リソースのファイルパス
    /// @param[out] ppOutTexture : ロードしたテクスチャを受け取るインターフェイス
    ///
    /// @return ロードに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool load( const wchar_t* FilePath, ITexture** ppOutTexture );

    ///
    /// @brief   テクスチャリソースの解放通知を受け取ります。
    /// @details 引数のテクスチャがキャッシュに存在したら、キャッシュから削除します。
    ///
    /// @param[in] Notifier : 解放を通知するテクスチャ
    ///
    void notifyReleaseTexture( ITexture* Notifier );
protected :
    ///
    /// @brief  ファイルからテクスチャをロードする
    ///
    /// @param[in] Path : リソースのファイルパス
    /// @param[out] ppOut : ロードしたテクスチャをセットするインターフェイス
    ///
    /// @return ロード成功[ true ] ロード失敗[ false ]
    ///
    virtual bool loadFromFile( const wchar_t* Path, ITexture** ppOut ) = 0;
    virtual ~ITextureLoader() = default;

private :
    std::unordered_map<const wchar_t*, ITexture*> cache_;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
///  EOF
