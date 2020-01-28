///
/// @file   component.hpp
/// @author ��
///
/// @brief  �R���|�[�l���g
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "egeg_common.hpp"
BEGIN_EGEG
class GameObject;
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  ����������
    ///
    /// @param[in] Owner : �I�[�i�[�̃A�h���X
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize( GameObject* Owner ) = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;

protected :
    GameObject* owner_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
