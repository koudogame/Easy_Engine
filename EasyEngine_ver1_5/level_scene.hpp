///
/// @file   level_scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_SCENE_HEADER_
#define INCLUDED_EGEG_LEVEL_SCENE_HEADER_

#include "level_node.hpp"
#include "render_component.hpp"
#include "level_camera.hpp"
#include "level_light.hpp"

BEGIN_EGEG

///
/// @class  LevelScene
/// @brief  ���x���m�[�h�u�V�[���v
///
/// @details �`���Ԃł��B
///
class LevelScene :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kScene;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  �`��R���|�[�l���g��o�^
    ///
    /// @param[in] Component : �`�惂�f��
    ///
    virtual void entry( RenderComponent* Component ) = 0;
    ///
    /// @brief  �`��R���|�[�l���g�̓o�^������
    ///
    /// @param[in] Component : �o�^���������郂�f��
    ///
    virtual void exit( RenderComponent* Component ) = 0;

    ///
    /// @brief  �J�������Z�b�g
    ///
    /// @param[in] Camera : �J����
    ///
    virtual void setCamera( LevelCamera* Camera ) = 0;

    ///
    /// @brief  ���C�g��ǉ�
    ///
    /// @param[in] Light : ���C�g
    ///
    virtual void addLight( LevelLight* ) = 0;

    ///
    /// @brief  �`��
    ///
    /// @param[in] Delta : �t���[���o�ߎ���
    ///
    /// @details �^�X�N�}�l�[�W���[�ɃW���u�Ƃ��ēo�^�ł���悤�ɁA�������w�肵�Ă��܂��B <br>
    ///
    virtual void render( uint64_t Delta ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_SCENE_HEADER_
/// EOF
