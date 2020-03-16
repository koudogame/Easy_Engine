///
/// @file   component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "egeg.hpp"
BEGIN_EGEG
class Actor;

///
/// @class   Component
/// @brief   �R���|�[�l���g���
/// @details �h���N���X�̓R���|�[�l���gID��ԋp����֐���<br>
///          static uint32_t getID() �Ƃ��Ē�`���ĉ������B
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  ����������
    ///
    /// @return ����[ true ]�@���s[ false ]
    ///
    virtual bool initialize() = 0;

    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;

protected :
    Component( Actor* Owner ) : owner_( Owner ) {}
    Actor* owner_;  ///< ���g��ێ����Ă���A�N�^�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
