///
/// @file   level_light.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_LIGHT_HEADER_
#define INCLUDED_EGEG_LEVEL_LIGHT_HEADER_

#include "level_node.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  LevelLight
/// @brief  ���x���m�[�h�u���C�g�v
///
/// @details ���C�g�ł��B�Q�[�����ɏo�Ă��郉�C�g�֌W�̃I�u�W�F�N�g�͂��̃N���X���p�����Ă��������B
///
class LevelLight :
    public LevelNode
{
public :
    enum class LightType
    {
        kDirectional,
        kPoint
    };

    static constexpr NodeType kNodeType = NodeType::kLight;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  ���C�g�^���擾
    ///
    /// @return ���C�g�^
    ///
    virtual LightType getLightType() = 0;

    ///
    /// @brief  �r���[���W�ϊ��s����v�Z
    ///
    /// @return ���C�g�̎��_�ւ̕ϊ��s��
    ///
    virtual Matrix4x4 calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_LIGHT_HEADER_
/// EOF
