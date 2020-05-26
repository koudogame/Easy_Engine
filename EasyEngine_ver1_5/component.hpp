///
/// @file   component.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_

#include "actor.hpp"

BEGIN_EGEG

///
/// @class Component
/// @brief �R���|�[�l���g
///
class Component
{
public :
    ///
    /// @brief �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[�ƂȂ�A�N�^�[
    ///
    Component( Actor* Owner ) noexcept :
        owner_{ Owner }
    {}

    virtual ~Component() = default;

    ///
    /// @brief ������
    ///
    /// @return true:�����@false:���s
    ///
    virtual bool initialize() = 0;

    ///
    /// @brief ���s
    ///
    virtual void finalize() = 0;

    ///
    /// @brief �I�[�i�[�̎擾
    ///
    /// @return �I�[�i�\
    ///
    Actor* getOwner() const noexcept { return owner_; }

private :
    Actor* owner_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
