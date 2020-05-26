///
/// @file   texture_loader.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_HEADER_

#include <string>
#include <wrl.h>
#include <d3d11.h>
#include "rendering_manager_child.hpp"
#include "return_value.hpp"


BEGIN_EGEG

///
/// @class TextureLoader
/// @brief �e�N�X�`�����[�_�[
///
class TextureLoader :
    public RenderingManagerChild
{
public :
    ///
    /// @brief �t�@�C������e�N�X�`�����\�[�X��ǂݍ���
    ///
    /// @param[in] TextureFilePath : �ǂݍ��ރe�N�X�`�����\�[�X�t�@�C���̃p�X
    ///
    /// @return �ǂݍ��񂾃e�N�X�`�����\�[�X
    ///
    DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> load(
        const std::string& TextureFilePath );
};

END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_HEADER_
/// EOF
