///
/// @file    shader_manager.hpp
/// @author  板場
///          
/// @brief   シェーダー管理者
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          このクラスのload関数を使用して読み込んだテクスチャは、<br>
///          このクラスのrelease関数を使用して解放してください。
/// 
#ifndef INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
#define INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
#include <unordered_map>
#include "shader_loader.hpp"
BEGIN_EG_EG
class ShaderManager
{
public :
    static ShaderManager* instance() { static ShaderManager i; return &i; }

    ///
    /// @brief   頂点シェーダーを読み込みます。
    /// @details キャッシュにない場合、新規に読み込みます。<br>
    ///          キャッシュにある場合、そのコピーを返却します。
    ///
    /// @param[in] FilePath : コンパイル済み頂点シェーダーのファイルパス
    /// @param[out] ppOutTexture : 読み込んだ頂点シェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool loadVertexShader( const char* FilePath, IVertexShader** ppOutShader );
    
    ///
    /// @brief   ピクセルシェーダーを読み込みます。
    /// @details キャッシュにない場合、新規に読み込みます。<br>
    ///          キャッシュにある場合、そのコピーを返却します。
    ///
    /// @param[in] FilePath : コンパイル済みピクセルシェーダーのファイルパス
    /// @param[out] ppOutTexture : 読み込んだピクセルシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    bool loadPixelShader( const char* FilePath, IPixelShader** ppOutShader );

    ///
    /// @brief   頂点シェーダーの解放を行います。
    /// @details 引数のインターフェイスには、解放後nullptrを代入します。<br>
    ///          キャッシュから削除されるタイミングは参照者がいなくなった時です。
    ///
    /// @param[inout] ppShader : 解放対象の頂点シェーダー
    ///
    void releaseVertexShader( IVertexShader** ppShader );
    
    ///
    /// @brief   ピクセルシェーダーの解放を行います。
    /// @details 引数のインターフェイスには、解放後nullptrを代入します。<br>
    ///          キャッシュから削除されるタイミングは参照者がいなくなった時です。
    ///
    /// @param[inout] ppShader : 解放対象のピクセルシェーダー
    ///
    void releasePixelShader( IPixelShader** ppShader );


    ~ShaderManager()
    {
        p_loader_->release();
    }
private :
    ShaderManager();

    IShaderLoader* p_loader_;
    std::unordered_map<const char*, IVertexShader*> vs_cache_;
    std::unordered_map<const char*, IPixelShader*>  ps_cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
/// EOF
