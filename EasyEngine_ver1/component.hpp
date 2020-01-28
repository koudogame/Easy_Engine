///
/// @file   component.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include "actor.hpp"
BEGIN_EGEG
///
/// @class   Component
///          
/// @brief   �R���|�[�l���g���N���X
/// @detaisl Actor�N���X�̃I�[�i�[�ɑ΂��ĉe�����܂��B
///
class Component
{
public :
    virtual ~Component() = default;

    ///
    /// @brief  ����������
    ///
    /// @param[in] pOwner : �I�[�i�[�̃A�h���X
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize( Actor* pOwner ) = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;

protected :
    Actor* owner_ = nullptr;    ///< �I�[�i�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
