///
/// @file    game.hpp
/// @author  ��
///          
/// @brief   �Q�[���{��
/// @details �Q�[���̃G���g���[�N���X�ł��B<br>
///          �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B
///
#ifndef INCLUDED_EGEG_GAME_HEADER_
#define INCLUDED_EGEG_GAME_HEADER_
#include "easy_engine.hpp"
BEGIN_EGEG
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
    void update( uint64_t DeltaTimeMS );
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_HEADER_
/// EOF
