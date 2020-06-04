///
/// @file   component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  Component
/// @brief  �R���|�[�l���g
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  ������
    ///
    /// @return true:�����@false:���s
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I��
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  �I�[�i�[�̎擾
    ///
    /// @return �I�[�i�[
    ///
    LevelNode* getOwner() const noexcept { return owner_; }

private :
    LevelNode* owner_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
