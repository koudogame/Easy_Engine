///
/// @file   physical_collision_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#define INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class  PhysicalCollisionComponent
/// @brief  物理適応衝突判定用コンポーネント
///
class PhysicalCollisionComponent :
    public CollisionComponent
{
public :
    ///< IDの取得
    static uint32_t getID() { return UID<PhysicalCollisionComponent>::getID(); }

    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pOwner : オーナー
    ///
    PhysicalCollisionComponent( Actor* pOwner ) : CollisionComponent( pOwner ) {}

    ///
    /// @brief  アクターとの衝突判定
    ///
    /// @param[in] pOther : 判定を行うアクター
    ///
    /// @return 衝突あり[ true ]　衝突なし[ false ]
    ///
    bool isCollided( Actor* pOther ) override;

    ///
    /// @brief  ステータスの設定
    ///
    /// @param[in] Mass : 質量
    /// @param[in] Restitution : 反発係数
    /// @param[in] StaticFriction : 静止摩擦係数
    /// @param[in] KineticFriction : 動摩擦係数
    ///
    void setStatuc( float Mass, float Restitution, float StaticFriction, float KineticFriction )
    {
        setMass( Mass );
        setRestitution( Restitution );
        setStaticFriction( StaticFriction );
        setKineticFriction( KineticFriction );
    }
    ///
    /// @brief  質量の設定
    ///
    /// @param[in] Mass : 質量
    ///
    void setMass( float Mass ) { mass_ = Mass; }
    ///
    /// @brief  反発係数の設定
    ///
    /// @param[in] Restitution : 反発係数
    ///
    void setRestitution( float Restitution ) { restitution_ = Restitution; }
    ///
    /// @brief  静止摩擦係数の設定
    ///
    /// @param[in] StaticFriction : 静止摩擦係数
    ///
    void setStaticFriction( float StaticFriction ) { static_friction_ = StaticFriction; }
    ///
    /// @brief  動摩擦係数の設定
    ///
    /// @param[in] KineticFriction : 動摩擦係数
    ///
    void setKineticFriction( float KineticFriction ) { kinetic_friction_ = KineticFriction; } 
    
private :
    float mass_ = 0.0F;             /// 質量
    float restitution_ = 0.0F;      /// 反発係数
    float static_friction_ = 0.0F;  /// 静止摩擦係数
    float kinetic_friction_ = 0.0F; /// 運動摩擦係数
};
END_EGEG
#endif /// !INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
/// EOF
