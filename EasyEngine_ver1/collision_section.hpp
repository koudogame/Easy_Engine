///
/// @file   collision_section.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COLLISION_SECTION_HEADER_
#define INCLUDED_EGEG_COLLISION_SECTION_HEADER_
#include <list>
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class  CollisionSection
/// @brief  ��Ԃ̃Z�N�V����
///
class CollisionSection
{
public :
    ///
    /// @brief  �Փ˃R���|�[�l���g�̒ǉ�
    ///
    /// @param[in] pComponent : �ǉ�����R���|�[�l���g
    ///
    void entry( CollisionComponent* pComponent );
    ///
    /// @brief   �Փ˃R���|�[�l���g�̍폜
    /// @details �R���|�[�l���g�̏����Z�N�V�������������Ă��܂��B<br>
    ///          �Z�N�V�����̈ړ��� 1.exit - 2.entry �̏��Ԃōs���Ă��������B
    ///
    /// @param[in] pComponent : �폜����R���|�[�l���g
    ///
    void exit( CollisionComponent* pComponent );

    ///
    /// @brief   ���ݎw���Ă���q�Z�N�V�����̑I��
    /// @details �ێ����Ă���Z�N�V�������Ăяo�����ɕԋp���܂��B<br>
    ///          �ꏄ�����ꍇ�A�Ō��nullptr��ԋp���܂��B
    ///
    /// @return  �q�Z�N�V����
    ///
    CollisionSection* pickChild();

    ///
    /// @brief   ���ݎw���Ă���R���|�[�l���g�̑I��
    /// @details �ێ����Ă���R���|�[�l���g���Ăяo�����ɕԋp���܂��B<br>
    ///          �ꏄ�����ꍇ�A�Ō��nullptr��ԋp���܂��B
    ///
    /// @return  �R���|�[�l���g
    ///
    CollisionComponent* pickComponent();

private :
    std::vector<CollisionSection*> childs_;
    std::list<CollisionComponent*> components_;

    uint32_t child_idx_  = 0U;
    std::list<CollisionComponent*>::iterator component_itr_ = components_.begin();
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SECTION_HEADER_
/// EOF
