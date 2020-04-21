///
/// @file   component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_

#include "component_id.hpp"

BEGIN_EGEG
class Actor;

namespace component {
///
/// @class   Component
/// @brief   �R���|�[�l���g���
/// @details �h���N���X�̓R���|�[�l���gID��ԋp����֐���<br>
///          static uint32_t getID() �Ƃ��Ē�`���ĉ������B <br>
///          getID�̓e���v���[�g�֐��ŌĂяo���܂��BTypeID<T>���g�p���Ȃ��ŉ������B
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

    ///< �I�[�i�[�̎擾
    Actor* getOwner() const noexcept { return owner_; }

protected :
    Component( Actor* Owner ) : owner_( Owner ) {}
    Actor* owner_;  ///< ���g��ێ����Ă���A�N�^�[
};

} /// namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
