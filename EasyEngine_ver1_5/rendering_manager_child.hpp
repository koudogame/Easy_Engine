///
/// @file   rendering_manager_child.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_

#include "egeg_def.hpp"

BEGIN_EGEG

class RenderingManager; ///< RenderingManager�O���錾( �z�Q�Ɖ�� )

///
/// @class RenderingManagerChild
/// @brief �����_�����O�}�l�[�W���\�ɂ�萶�������I�u�W�F�N�g
///
class RenderingManagerChild
{
public :
    virtual ~RenderingManagerChild() = default;

    ///
    /// @brief �}�l�[�W���[�̎擾
    ///
    /// @return �����_�����O�}�l�[�W���[
    ///
    RenderingManager* getManager() const noexcept { return manager_; }


    ///
    /// @brief �}�l�[�W���[�̃Z�b�g
    ///
    /// @param[in] Manager : �����_�����O�}�l�[�W���\
    ///
    void setManager( RenderingManager& Manager ) noexcept { manager_ = &Manager; }

private :
    RenderingManager* manager_{ nullptr };
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_CHILD_HEADER_
/// EOF
