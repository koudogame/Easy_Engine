///
/// @file   level_camera.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_CAMERA_HEADER_
#define INCLUDED_EGEG_LEVEL_CAMERA_HEADER_

#include "level_node.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  LevelCamera
/// @brief  ���x���m�[�h�u�J�����v
///
/// @details �J�����ł��B�Q�[�����̎��_�𑀍삷��I�u�W�F�N�g�͂��̃N���X���p�����Ă��������B
///
class LevelCamera :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kCamera;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  �r���[���W�ϊ��s����v�Z
    ///
    /// @return �r���[���W�ϊ��s��
    ///
    virtual Matrix4x4 calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_CAMERA_HEADER_
/// EOF
