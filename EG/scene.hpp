///
/// @file scene.hpp
/// @author ��
///
/// @brief �V�[�����N���X
///
///
#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_
#include "easy_engine.hpp"
BEGIN_EGEG
class SceneManager;
class Scene
{
public :
    ///
    /// @brief �R���X�g���N�^
    ///
    Scene( SceneManager* Manager ) :
        manager_( Manager )
    {}

    ///
    /// @brief �f�X�g���N�^
    ///
    virtual ~Scene() = default;

    ///
    /// @brief �X�V����
    ///
    virtual void update() = 0;

    ///
    /// @brief �I������
    ///
    virtual void finalize() = 0;

    ///
    /// @brief �`�揈��
    ///
    virtual void draw() = 0;

protected :
    SceneManager* manager_; ///< @brief �V�[���}�l�[�W���[
};
END_EGEG
#endif /// !INCLUDED_EG_EG_SCENE_HEADER_
/// EOF
