///
/// @file    body_2d.hpp
/// @author  板場
///          
/// @brief   ボディ
/// @details 衝突判定の処理を「ダブルディスパッチ」を使用して実現しています。
///
#ifndef INCLUDED_EGEG_BODY_2D_HEADER_
#define INCLUDED_EGEG_BODY_2D_HEADER_
#include "point_2d.hpp"
#include "circle_2d.hpp"
#include "line_2d.hpp"
BEGIN_EGEG
class IBody2D
{
public :
    virtual ~IBody2D() = default;

    ///
    /// @brief  絶対移動
    ///
    /// @param[in] Destination : 移動先の座標
    ///
    virtual void moveAbs( const Vector2D& Destination ) = 0;
    ///
    /// @brief  相対移動
    ///
    /// @param[in] Distance : 移動距離
    ///
    virtual void moveRel( const Vector2D& Distance ) = 0;

    ///
    /// @brief   ダブルディスパッチ開始メッセージ
    /// @details 相手に自分の詳細な形を伝え、衝突の判定を行ってもらいます。
    ///          ex.) Body->isCollision( this->shape_ );    のように実装してください。
    ///
    /// @param[in] Body : 衝突を判定する相手
    ///
    virtual bool isCollision( const IBody2D* Body ) const = 0;

    ///
    /// @brief  点との衝突判定
    ///
    /// @param[in] Point : 衝突を判定する点
    ///
    /// @return 衝突あり[ true ] 衝突なし[ false ]
    ///
    virtual bool isCollision( const Point2D& Point ) = 0;
    ///
    /// @brief  円との衝突判定
    ///
    /// @param[in] Circle : 衝突を判定する円
    ///
    /// @return 衝突あり[ true ] 衝突なし[ false ]
    ///
    virtual bool isCollision( const Circle& Circle ) = 0;
    ///
    /// @brief  線分との衝突判定
    ///
    /// @param[in] Line : 衝突を判定する線分
    ///
    /// @return 衝突あり[ true ] 衝突なし[ false ]
    ///
    virtual bool isCollision( const Line2D& Line ) = 0;

    ///
    /// @brief   大体の衝突範囲を取得
    /// @details 詳細な衝突判定を行う前のテスト
    ///
    /// @return  大体の範囲( Circle )
    ///
    virtual const Circle& getRoughRange() const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_2D_HEADER_
/// EOF
