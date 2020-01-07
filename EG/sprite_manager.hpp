///
/// @file   sprite_manager.hpp
/// @author 板場
///
/// @brief  スプライト管理者
///
/// @details    スプライトの描画を一気に行い、リソースの無駄遣いを抑制します。<br>
///             シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
///
#ifndef INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#include "sprite.hpp"
BEGIN_EG_EG
class SpriteManager
{
public :
    ///
    /// @brief  インスタンスのアドレスを取得します。
    ///
    /// @return インスタンスのアドレス
    ///
    static SpriteManager* instance() { static SpriteManager i; return &i; }

    ///
    /// @brief   描画をエントリーします。
    /// @details この関数は描画を行いません。
    ///
    /// @param[in] Entry : 描画をエントリーするスプライト
    ///
    void entryRender( Sprite& Entry );

    ///
    /// @brief  関数呼び出し時にエントリーされているスプライトを描画します。
    ///
    void render();
     
private :
    SpriteManager() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
/// EOF
