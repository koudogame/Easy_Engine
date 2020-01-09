///
/// @file    game.hpp
/// @author  ��
///          
/// @brief   �Q�[���N���X
/// @details �Q�[���̒��j������ň����܂��B<br>
///          �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
///
#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Director;
class Game
{
public:
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static Game* instance() { static Game game; return &game; }

    ///
    /// @brief  �Q�[���̎��s
    ///
    void execute();

private:
    Game() = default;

    bool initialize();
    void finalize();
    bool update(long long Erapsed);

    Director* director_ = nullptr;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_GAME_HEADER_
/// EOF
