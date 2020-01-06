#ifndef INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
// 作成者 : 板場
#include "sprite.hpp"

BEGIN_EG_EG
//
// スプライト管理者
// スプライトの描画を一気に行い、リソースの無駄遣いを抑制する。
//
// シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
//
class SpriteManager
{
public :
    // インスタンスへのアクセス
    static SpriteManager* instance() { static SpriteManager i; return &i; }

    //
    // Spriteの描画をエントリー
    //
    void entryRender( Sprite& Entry );

    //
    // エントリーされているSpriteを描画
    //
    void render();
     
private :
    SpriteManager() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
// EOF
