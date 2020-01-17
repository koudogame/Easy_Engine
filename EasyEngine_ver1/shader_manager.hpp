///
/// @file    shader_manager.hpp
/// @author  板場
///          
/// @brief   シェーダーマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          このクラスを使用して読み込んだシェーダーは、必ずこのクラスで開放してください。<br>
///          読み込んだシェーダーを保持し、このクラスの破棄時に開放されていないシェーダーを開放します。
///
#ifndef INCLUDED_EGEG_SHADER_MANAGER_HEADER_
#define INCLUDED_EGEG_SHADER_MANAGER_HEADER_
#include <string>
#include <unordered_set>
#include "easy_engine.hpp"
#include "shader_loader.hpp"
BEGIN_EGEG
class ShaderManager
{
public :
    ///
    /// @brief  インスタンスへのアクセス
    ///
    /// @return インスタンス
    ///
    static ShaderManager* instance() { return instance_; }

    ///
    /// @brief  頂点シェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppVertexShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    bool loadVertexShader( const std::string& FilePath, IVertexShader** ppVertexShader );
    ///
    /// @brief   頂点シェーダ―の開放
    /// @details 引数で受け取ったインターフェイスには、nullptrが代入されます。
    ///
    /// @param[inout] ppVertexShader : 開放する頂点シェーダ―
    ///
    void releaseVertexShader( IVertexShader** ppVertexShader );

    ///
    /// @brief  ジオメトリシェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppGeometryShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    bool loadGeometryShader( const std::string& FilePath, IGeometryShader** ppGeometryShader );
    ///
    /// @brief   ジオメトリシェーダーの開放
    /// @details 引数で受け取ったインターフェイスには、nullptrが代入されます。
    ///
    /// @param[inout] ppGeometryShader : 開放するジオメトリシェーダー
    ///
    void releaseGeometryShader( IGeometryShader** ppGeometryShader );

    ///
    /// @brief  ピクセルシェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppPixelShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    bool loadPixelShader( const std::string& FilePath, IPixelShader** ppPixelShader );
    ///
    /// @brief   ピクセルシェーダ―の開放
    /// @details 引数で受け取ったインターフェイスには、nullptrが代入されます。
    ///
    /// @param[inout] ppPixelShader : 開放するピクセルシェーダ―
    ///
    void releasePixelShader( IPixelShader** ppPixelShader );

    ///
    /// @brief  インスタンスの生成
    ///
    /// @param[in] Creator : 生成者
    /// @param[in] pShaderLoader : 使用するシェーダーローダー
    ///
    static void create( const EasyEngine& Creator, IShaderLoader* pShaderLoader );
    ///
    /// @brief  インスタンスの破棄
    ///
    /// @param[in] Deleter : 破棄者
    ///
    static void destroy( const EasyEngine& Deleter );

private :
    ShaderManager( IShaderLoader* );
    ~ShaderManager();
    ShaderManager( const ShaderManager& ) = delete;
    ShaderManager& operator=( const ShaderManager& ) = delete;

    static ShaderManager* instance_;
    IShaderLoader* p_loader_;                       /// 使用するシェーダーローダー
    std::unordered_set<IVertexShader*> vs_list_;    /// このクラスを使用して生成された、頂点シェーダ―リスト
    std::unordered_set<IGeometryShader*> gs_list_;  /// このクラスを使用して生成された、ジオメトリシェーダリスト
    std::unordered_set<IPixelShader*> ps_list_;     /// このクラスを使用して生成された、ピクセルシェーダ―リスト
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_MANAGER_HEADER_
/// EOF
