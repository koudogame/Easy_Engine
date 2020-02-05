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
/// @detaisl Actor�N���X�̃I�[�i�[�ɑ΂��ĉe�����܂��B<br>
///          �h���N���X�� static uint32_t getID()���������Ă��������B<br>
///          
///
class Component :
    public GameObject
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Owner : �I�[�i�[
    ///
    Component( Actor* Owner ) : owner_( Owner ) {}
    virtual ~Component() = default;

protected :
    Actor* owner_;    ///< �I�[�i�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
