// 作成者 : 板場
#include "transform2d.hpp"

BEGIN_EGEG
namespace component {

// Transform2D 関数定義
/*===========================================================================*/
// 初期化
bool Transform2D::initialize()
{
    position_ = Vector2D( 0.0F, 0.0F );
    pivot_    = Vector2D( 0.0F, 0.0F );
    scale_    = Vector2D( 1.0F, 1.0F );
    rotation_ = 0.0F;

    return true;
}

// 終了
void Transform2D::finalize()
{

}

} // namespace component
END_EGEG
// EOF
