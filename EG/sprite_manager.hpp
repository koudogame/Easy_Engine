///
/// @file   sprite_manager.hpp
/// @author ��
///
/// @brief  �X�v���C�g�Ǘ���
///
/// @details    �X�v���C�g�̕`�����C�ɍs���A���\�[�X�̖��ʌ�����}�����܂��B<br>
///             �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
///
#ifndef INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
#include "sprite.hpp"
BEGIN_EG_EG
class SpriteManager
{
public :
    ///
    /// @brief  �C���X�^���X�̃A�h���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static SpriteManager* instance() { static SpriteManager i; return &i; }

    ///
    /// @brief   �`����G���g���[���܂��B
    /// @details ���̊֐��͕`����s���܂���B
    ///
    /// @param[in] Entry : �`����G���g���[����X�v���C�g
    ///
    void entryRender( Sprite& Entry );

    ///
    /// @brief  �֐��Ăяo�����ɃG���g���[����Ă���X�v���C�g��`�悵�܂��B
    ///
    void render();
     
private :
    SpriteManager() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_SPRITE_MANAGER_HEADER_
/// EOF
