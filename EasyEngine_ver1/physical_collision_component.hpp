///
/// @file   physical_collision_component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#define INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class  PhysicalCollisionComponent
/// @brief  �����K���Փ˔���p�R���|�[�l���g
///
class PhysicalCollisionComponent :
    public CollisionComponent
{
public :
    ///< ID�̎擾
    static uint32_t getID() { return UID<PhysicalCollisionComponent>::getID(); }

    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pOwner : �I�[�i�[
    ///
    PhysicalCollisionComponent( Actor* pOwner ) : CollisionComponent( pOwner ) {}

    ///
    /// @brief  �A�N�^�[�Ƃ̏Փ˔���
    ///
    /// @param[in] pOther : ������s���A�N�^�[
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    bool isCollided( Actor* pOther ) override;

    ///
    /// @brief  �X�e�[�^�X�̐ݒ�
    ///
    /// @param[in] Mass : ����
    /// @param[in] Restitution : �����W��
    /// @param[in] StaticFriction : �Î~���C�W��
    /// @param[in] KineticFriction : �����C�W��
    ///
    void setStatuc( float Mass, float Restitution, float StaticFriction, float KineticFriction )
    {
        setMass( Mass );
        setRestitution( Restitution );
        setStaticFriction( StaticFriction );
        setKineticFriction( KineticFriction );
    }
    ///
    /// @brief  ���ʂ̐ݒ�
    ///
    /// @param[in] Mass : ����
    ///
    void setMass( float Mass ) { mass_ = Mass; }
    ///
    /// @brief  �����W���̐ݒ�
    ///
    /// @param[in] Restitution : �����W��
    ///
    void setRestitution( float Restitution ) { restitution_ = Restitution; }
    ///
    /// @brief  �Î~���C�W���̐ݒ�
    ///
    /// @param[in] StaticFriction : �Î~���C�W��
    ///
    void setStaticFriction( float StaticFriction ) { static_friction_ = StaticFriction; }
    ///
    /// @brief  �����C�W���̐ݒ�
    ///
    /// @param[in] KineticFriction : �����C�W��
    ///
    void setKineticFriction( float KineticFriction ) { kinetic_friction_ = KineticFriction; } 
    
private :
    float mass_ = 0.0F;             /// ����
    float restitution_ = 0.0F;      /// �����W��
    float static_friction_ = 0.0F;  /// �Î~���C�W��
    float kinetic_friction_ = 0.0F; /// �^�����C�W��
};
END_EGEG
#endif /// !INCLUDED_EGEG_PHYSICAL_COLLISION_COMPONENT_HEADER_
/// EOF
