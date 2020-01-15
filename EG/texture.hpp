///
/// @file   texture.hpp
/// @author ��
///
/// @brief  �e�N�X�`�����\�[�X�C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_TEXTURE_HEADER_
#define INCLUDED_EG_EG_TEXTURE_HEADER_
#include "interface.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class ITexture :
    public SharedObject
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] Loader : ���g�̐�����
    ///
    ITexture( ITextureLoader* Loader ) :
        loader_( Loader )
    {
        loader_->addRef();
    }

protected :
    virtual ~ITexture()
    {
        loader_->notifyReleaseTexture( this );
        loader_->release();
    }

private :
    ITextureLoader* loader_;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_HEADER_
/// EOF
