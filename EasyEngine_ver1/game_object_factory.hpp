///
/// @file   game_object_factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
#include "factory.hpp"
#include "game_object.hpp"
BEGIN_EGEG
///
/// @class  GameObjectFactory
/// @brief  �Q�[���I�u�W�F�N�g�̃t�@�N�g��
///
class GameObjectFactory :
    public Factory<GameObject, GameObject*(*)()>
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static GameObjectFactory* instance() { static GameObjectFactory i; return &i; }

private :
    GameObjectFactory() = default;
    GameObjectFactory( const GameObjectFactory& ) = delete;
    GameObjectFactory& operator=( const GameObjectFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
/// EOF
