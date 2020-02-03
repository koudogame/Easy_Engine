// 作成者 : 板場
#include <cmath>
#include "collision_detection.hpp"

BEGIN_EGEG
// CollisionDetection : 関数の実装
/*===========================================================================*/
// 矩形と矩形 (AABB)
bool CollisionDetection::isCollided( const Rectangle& Rect1, const Rectangle& Rect2 )
{
    // Rect1の4頂点を計算
    const float kRect1WidthHarf  = Rect1.width * 0.5F;
    const float kRect1HeightHarf = Rect1.height * 0.5F;
    const float kRect1Left   = Rect1.origin.x - kRect1WidthHarf;
    const float kRect1Top    = Rect1.origin.y - kRect1HeightHarf;
    const float kRect1Right  = Rect1.origin.x + kRect1WidthHarf;
    const float kRect1Bottom = Rect1.origin.y + kRect1HeightHarf;

    // Rect2の4頂点を計算
    const float kRect2WidthHarf  = Rect2.width * 0.5F;
    const float kRect2HeightHarf = Rect2.height * 0.5F;
    const float kRect2Left   = Rect2.origin.x - kRect2WidthHarf;
    const float kRect2Top    = Rect2.origin.y - kRect2HeightHarf;
    const float kRect2Right  = Rect2.origin.x + kRect2WidthHarf;
    const float kRect2Bottom = Rect2.origin.y + kRect2HeightHarf;

    // 判定
    if( kRect1Left <= kRect2Right &&
        kRect1Right >= kRect2Left &&
        kRect1Top <= kRect2Bottom &&
        kRect1Bottom >= kRect2Top )
    {
        return true;
    }
    else
        return false;
}

// 円と円
bool CollisionDetection::isCollided( const Circle& Cir1, const Circle& Cir2 )
{
    // 円同士の距離を計算
    float dist_x = Cir2.origin.x - Cir1.origin.x;
    float dist_y = Cir2.origin.y - Cir1.origin.y;
    float distance = (dist_x * dist_x) + (dist_y * dist_y);

    float dist_coll = Cir1.radius + Cir2.radius;    // 衝突する距離
    dist_coll *= dist_coll;

    // 距離が互いの半径を加算した値よりも小さければ衝突
    if( distance <= dist_coll )
    {
        return true;
    }
    else
        return false;
}

// 線分と線分　参考サイト : http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
bool CollisionDetection::isCollided( const Line& Line1, const Line& Line2, float* DivRat1, float* DivRat2 )
{
    // 平行判定
    if( Line1.line.cross( Line2.line ) == 0.0F )  
    {
        return false;
    }

    // 交差判定
    Vector2D vec_s_s = Line2.start - Line1.start;
    float rec_crs_1_2 = 1.F / Line1.line.cross(Line2.line);
    float divrat_2 = vec_s_s.cross(Line1.line) * rec_crs_1_2;
    float divrat_1 = vec_s_s.cross(Line2.line) * rec_crs_1_2;

    if( DivRat1 )   *DivRat1 = divrat_1;
    if( DivRat2 )   *DivRat2 = divrat_2;

    if( divrat_1 >= 0.F && divrat_1 <= 1.00001F &&
        divrat_2 >= 0.F && divrat_2 <= 1.00001F )
    {
        return true;
    }
    else
        return false;
}

// 矩形と円形
bool CollisionDetection::isCollided( const Rectangle& Rect, const Circle& Cir )
{
    return false;
}

// 矩形と線分
bool CollisionDetection::isCollided( const Rectangle& Rect, const Line& Line )
{
    return false;
}

// 円形と線分
bool CollisionDetection::isCollided( const Circle& Cir, const Line& Line )
{
    return false;
}
END_EGEG
// EOF
