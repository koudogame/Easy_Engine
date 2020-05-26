///
/// @file   shader.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_SHADER_HEADER_
#define INCLUDED_EGEG_SHADER_HEADER_

#include <memory> ///< �V�F�[�_�\�I�u�W�F�N�g�̃n���h��
#include <d3d11.h>
#include "return_value.hpp"
#include "vertex.hpp"
#include "material.hpp"

BEGIN_EGEG

#define DECLARATION_SHADER_MEMBER( ShaderClassName ) \
public : static std::unique_ptr<ShaderClassName> create(); DetailedReturnValue<bool> shading( ID3D11DeviceContext*, const VertexData&, const Material& ) override; private :

///
/// @class   IShader
/// @brief   �V�F�[�_�\�C���^�t�F�C�X
/// @details ���ӓ_
///             �e�h���N���X�́Astatic std::unique_ptr<T> create() �Ƃ��ăV�F�[�_�\�I�u�W�F�N�g�̐����������`���ĉ������B <br>
///             ���_�V�F�[�_�\�̒萔�o�b�t�@�� �X���b�g0 ~ �X���b�g2 �͈ȉ��̂悤�ɐݒ肳��܂��B <br>
///                 b0 : �ˉe�ϊ��s��( DirectX::XMFLOAT4X4 ) <br>
///                 b1 : �r���[�ϊ��s��( DirectX::XMFLOAT4X4 ) <br>
///                 b2 : ���[���h�ϊ��s��( DirectX::XMFLOAT4X4 )
///
class IShader
{
public :
    using VertexData = Property<TagVertexPosition, TagVertexUV, TagVertexNormal>;
    virtual ~IShader() = default;

    ///
    /// @brief  �V�F�[�f�B���O
    ///
    /// @param[in] DC       : �f�o�C�X�R���e�L�X�g
    /// @param[in] Vertices : ���_�f�[�^
    /// @param[in] Material : �}�e���A��
    ///
    /// @return true : �����@false : ���s
    ///
    virtual DetailedReturnValue<bool> shading( ID3D11DeviceContext* DC, const VertexData& Vertices, const Material& Material ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_HEADER_
/// EOF
