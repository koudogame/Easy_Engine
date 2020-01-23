///
/// @file    render_batch.hpp
/// @author  板場
///          
/// @brief   レンダーバッチ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          render関数で登録されたレンダーコンポーネントの描画関数を一度に呼び出します。
///
#ifndef INCLUDED_EGEG_RENDER_BATCH_HEADER_
#define INCLUDED_EGEG_RENDER_BATCH_HEADER_
#include <unordered_set>
#include "render_component.hpp"
BEGIN_EGEG
class RenderBatch
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static RenderBatch* instance() { static RenderBatch i; return &i; }

    ///
    /// @brief   コンポーネントの登録
    ///
    /// @param[in] pComponent : 登録するレンダーコンポーネント
    ///
    void registerComponent( RenderComponent* pComponent ) { components_.insert( pComponent ); }
    ///
    /// @brief  コンポーネントの削除
    ///
    /// @param[in] pComponent : 削除対象のコンポーネント
    ///
    void unregisterComponent( RenderComponent* pComponent ) { components_.erase( pComponent ); }

    ///
    /// @brief  登録されているコンポーネントのrender関数を呼び出します。
    ///
    void render();

private :
    RenderBatch() = default;
    RenderBatch( const RenderBatch& ) = delete;
    RenderBatch& operator=( const RenderBatch& ) = delete;

    std::unordered_set<RenderComponent*> components_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_BATCH_HEADER_
/// EOF
