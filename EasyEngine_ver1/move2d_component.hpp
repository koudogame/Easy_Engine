///
/// @file   move2d_component.hpp
/// @author 板場
///
/// @brief  2D移動コンポーネント
///
#ifndef INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
#include "component.hpp"
#include "egeg_math.hpp"
#include "job.hpp"
BEGIN_EGEG
class Move2DComponent :
    public IComponent
{
public :
    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差
    ///
    void update( uint64_t DeltaTimeMS );

    ///
    /// @brief   変位の取得
    /// @details この関数を前回呼び出した時からの変位ベクトルを返却します。
    ///
    /// @return  変位
    ///
    Vector2D getDisplacement();

    ///
    /// @brief  速さの設定
    ///
    /// @param[in] Speed : 速さ( pix/sec )
    ///
    void setSpeed( float Speed ) { speed_ = Speed * 0.001F; }
    ///
    /// @brief  速さの取得
    ///
    /// @return 速さ
    ///
    float getSpeed() const { return speed_; }

    ///
    /// @brief   移動方向の設定
    ///
    /// @param[in] AngleDEG : 移動角度( 度数法 )
    ///
    void setAngle( float AngleDEG );
    ///
    /// @brief  移動方向の取得
    ///
    /// @return 移動方向
    ///
    float getAngle() const { return angle_; }


// IComponent
/*-----------------------------------------------------------------*/
    bool initialize() override;
    void finalize() override;

private :
    float    speed_ = 0.0F;                 /// 速さ( pix/ms )
    float    angle_ = 0.0F;                 /// 角度( getAngle呼び出し時、毎回計算するのを防ぐ )
    Vector2D direction_ = { 0.0F, 0.0F };   /// 方向ベクトル( 正規化ベクトル )
    uint64_t erapsed_ = 0U;                 /// 経過時間( ms )
    Job      job_;                          /// ジョブ登録用
};
END_EGEG
#endif /// !INCLUDED_EGEG_MOVE2D_COMPONENT_HEADER_
/// EOF
