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
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[
    ///
    Component( Actor* Owner ) : owner_( Owner ) {}
    virtual ~Component() = default;

    ///
    /// @brief  ����������
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �I������
    ///
    virtual void finalize() = 0;

protected :
    Actor* owner_;    ///< �I�[�i�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
