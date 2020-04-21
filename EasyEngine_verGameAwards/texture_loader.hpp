///
/// @file   texture_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_

#include "rendering_manager_child.hpp"
#include "result.hpp"

BEGIN_EGEG
///
/// @class  TextureLoader
/// @brief  �e�N�X�`�����\�[�X�̃��[�_�[
///
class TextureLoader :
    public RenderingManagerChild
{
public :

    ///
    /// @brief  �t�@�C������e�N�X�`�����\�[�X��ǂݍ���
    ///
    /// @param[in] FileName : �ǂݍ��ރe�N�X�`���̃t�@�C���p�X
    ///
    /// @return �ǂݍ��񂾃e�N�X�`���̃V�F�[�_�\���\�[�X�r���[
    ///
    DetailedResult<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> load(
        const std::wstring& FilePath );
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
/// EOF

