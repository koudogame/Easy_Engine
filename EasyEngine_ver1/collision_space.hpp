///
/// @file   collision_space.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#define INCLUDED_EGEG_COLLISION_SPACE_HEADER_
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class   CollisionSpace
/// @brief   �Փˋ�ԃN���X
///          
/// @details �Փ˔�����s����Ԃ̃C���^�[�t�F�C�X�ł��B<br>
///          �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
class CollisionSpace
{
public :
    virtual ~CollisionSpace() = default;

    static CollisionSpace* instance();

    ///
    /// @brief  ��Ԃւ̓o�^
    ///
    /// @param[in] pComponent : �o�^����R���|�[�l���g�̃A�h���X
    ///
    virtual void entry( CollisionComponent* pComponent ) = 0;
    ///
    /// @brief  ��Ԃ���폜
    ///
    /// @param[in] pComponent : �폜����R���|�[�l���g�̃A�h���X
    ///
    virtual void exit( CollisionComponent* pComponent ) = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SPACE_HEADER_
/// EOF
