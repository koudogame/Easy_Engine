///
/// @file   scene_factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_FACTORY_HEADER_
#define INCLUDED_EGEG_SCENE_FACTORY_HEADER_
#include "factory.hpp"
#include "scene.hpp"
BEGIN_EGEG
///
/// @class   SceneFactory
///          
/// @brief   �V�[���t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          �V�[���̓o�^�ɂ�REGISTER_SCENE�}�N�����g�p���ĉ������B
///
class SceneFactory :
    public Factory<Scene, Scene*(*)()>
{
public :
    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static SceneFactory* instance() { static SceneFactory i; return &i; }

private :
    SceneFactory() = default;
    SceneFactory( const SceneFactory& ) = delete;
    SceneFactory& operator=( const SceneFactory& ) = delete;
};
END_EGEG


class REGISTER_SCENE
{
public :
    REGISTER_SCENE( uint32_t ID, EGEG Scene*(*pFunc)() ) { EGEG SceneFactory::instance()->registerCreator( ID, pFunc); }
};
///
/// @def     REGISTER_SCENE
/// @brief   �V�[�����t�@�N�g���ɓo�^
/// @details �w�b�_�[�t�@�C���ŌĂяo���Ȃ��ł��������B
///
/// @param[in] SceneID  : �V�[���̐���ID
/// @param[in] pCreator : �����t�@���N�^
///
#define REGISTER_SCENE( SceneID, pCreator ) \
namespace impl{} namespace { namespace impl { \
REGISTER_SCENE register_scene( SceneID, pCreator ); \
}}
#endif /// !INCLUDED_EGEG_SCENE_FACTORY_HEADER_
/// EOF
