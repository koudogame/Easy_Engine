///
/// @file   texture_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_

#include "loader.hpp"
#include "detailed_returnvalue.hpp"

BEGIN_EGEG
///
/// @class  TextureLoader
/// @brief  �e�N�X�`�����\�[�X�̃��[�_�[
///
class TextureLoader :
    public Loader
{
public :
    TextureLoader( const Microsoft::WRL::ComPtr<ID3D11Device>& Device ) :
        Loader( Device )
    {
    }

    ///
    /// @brief  �t�@�C������e�N�X�`�����\�[�X��ǂݍ���
    ///
    /// @param[in] FileName : �ǂݍ��ރe�N�X�`���̃t�@�C���p�X
    ///
    /// @return �ǂݍ��񂾃e�N�X�`���̃V�F�[�_�\���\�[�X�r���[
    ///
    DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> load(
        const std::wstring& FilePath );
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_HEADER_
/// EOF

