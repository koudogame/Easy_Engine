///
/// @file    game.hpp
/// @author  ��
///
#ifndef INCLUDED_EGEG_GAME_HEADER_
#define INCLUDED_EGEG_GAME_HEADER_
#include "easy_engine.hpp"
#include "sprite_component.hpp"
BEGIN_EGEG
class ITexture;
///
/// @class  Game
///          
/// @brief   �Q�[���{��
/// @details �Q�[���̃G���g���[�N���X�ł��B<br>
///          �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B
///
class Game
{
public :
    ///
    /// @brief  ����������
    ///
    /// @return ����������[ true ] ���������s[ false ]
    ///
    bool initialize();
    ///
    /// @brief  �I������
    ///
    void finalize();

    ///
    /// @brief  �X�V����
    ///
    /// @param[in] DeltaTimeMS : �o�ߎ���(: �~���b)
    ///
    /// @return �X�V�p��[ true ]�@�X�V�I��[ false ]
    ///
    bool update( uint64_t DeltaTimeMS );

private :
    SpriteComponent sprite;
    ITexture *texture_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_HEADER_
/// EOF
