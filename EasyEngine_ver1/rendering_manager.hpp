///
/// @file    rendering_manager.hpp
/// @author  板場
///          
/// @brief   レンダリングマネージャ－
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "renderer.hpp"
BEGIN_EGEG
class RenderingManager
{
public :
    ///
    /// @brief  インスタンスへのアクセス
    ///
    /// @return インスタンス
    ///
    static RenderingManager* instance() { return instance_; }

    ///
    /// @brief   描画開始
    /// @details 引数のカラー情報は、各色0.0F ~ 1.0Fで設定してください。
    ///
    /// @param[in] ColorRGBA : 画面のクリア色 { R, G, B, A }
    ///
    void beginRender( const Vector4D& ColorRGBA );
    ///
    /// @brief   描画のエントリー
    /// @details 実際に描画は行いません。
    ///
    /// @param[in] Model : 描画するモデル
    ///
    void entryRender( const Model& Model );
    ///
    /// @brief   描画のエントリー
    /// @details 実際に描画は行いません。
    ///
    /// @param[in] Mesh : メッシュ
    /// @param[in] pTexture : テクスチャ
    /// @param[in] pVertexShader : 頂点シェーダー
    /// @param[in] pGeometryShader : ジオメトリシェーダー
    /// @param[in] pPixelShader : ピクセルシェーダー
    ///
    void entryRender( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader );
    ///
    /// @brief   描画終了
    /// @details beginRenderの呼び出しから、<br>
    ///          この関数が呼び出されるまでにエントリーされたモデルを描画します。
    ///
    void endRender();


    ///
    /// @brief  インスタンスの生成
    ///
    /// @param[in] Creator : 生成者
    /// @param[in] pRenderer : 使用するレンダラー
    ///
    static void create( const EasyEngine& Creator, IRenderer* pRenderer );
    ///
    /// @brief  インスタンスの破棄
    ///
    /// @param[in] Deleter : 破棄者
    ///
    static void destroy( const EasyEngine& Deleter );

    RenderingManager( const RenderingManager& ) = delete;
    RenderingManager& operator=( const RenderingManager& ) = delete;
private :
    RenderingManager( IRenderer* );
    ~RenderingManager();
    static RenderingManager* instance_;
    IRenderer* p_renderer_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
/// EOF
