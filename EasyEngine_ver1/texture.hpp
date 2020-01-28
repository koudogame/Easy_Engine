///
/// @file   texture.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TEXTURE_HEADER_
#define INCLUDED_EGEG_TEXTURE_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
///
/// @class ITexture
///
/// @brief  �e�N�X�`���f�[�^
///
class ITexture :
    public SharedObject
{
public :
    ///
    /// @brief  �e�N�X�`���̉������擾
    ///
    /// @return �e�N�X�`���̉���
    ///
    virtual long getWidth() const = 0;
    ///
    /// @brief  �e�N�X�`���̏c�����擾
    ///
    /// @return �e�N�X�`���̏c��
    ///
    virtual long getHeight() const = 0;

protected :
    virtual ~ITexture() = 0 {}

};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_HEADER_
/// EOF
