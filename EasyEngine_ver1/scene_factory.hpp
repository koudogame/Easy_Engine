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
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
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
#endif /// !INCLUDED_EGEG_SCENE_FACTORY_HEADER_
/// EOF
