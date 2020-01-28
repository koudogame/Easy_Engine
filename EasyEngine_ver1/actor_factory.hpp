///
/// @file   actor_factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
#define INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
#include "factory.hpp"
#include "actor.hpp"
BEGIN_EGEG
///
/// @class   ActorFactory
///          
/// @brief   �A�N�^�[�t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
class ActorFactory :
    public Factory<Actor, Actor*(*)()>
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static ActorFactory* instance() { static ActorFactory i; return &i; }

private :
    ActorFactory() = default;
    ActorFactory( const ActorFactory& ) = delete;
    ActorFactory& operator=( const ActorFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
/// EOF
