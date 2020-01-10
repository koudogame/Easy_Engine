///
/// @file    game.hpp
/// @author  ��
///          
/// @brief   �Q�[���G���g���[�N���X
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
///
#ifndef INCLUDED_EG_EG_GAME_HEADER_
#define INCLUDED_EG_EG_GAME_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EG_EG
class Game
{
public:
    ///< �^�[�Q�b�g�v���b�g�t�H�[���ł��B
    static constexpr PlatformID kTargetPlatform = PlatformID::kWindows;

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
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_GAME_HEADER_
/// EOF
