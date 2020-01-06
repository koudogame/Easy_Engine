#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
// �쐬�� : ��
#include "texture.hpp"
#include "model.hpp"

BEGIN_EG_EG
//
// �����_���[�C���^�[�t�F�C�X
// RendererFactory�ɂ�萶������邱�Ƃ�O��Ƃ��Ă��܂��B
//
// ���������ς�ł��Ȃ��C���^�[�t�F�C�X�̐�����h�����߁A
// �C���X�^���X���𐧌����Ă��܂��B
//
class IRenderer
{
public :
    virtual ~IRenderer() = default;
    
// FileIO
/*-----------------------------------------------------------------*/
    // �e�N�X�`�����\�[�X�̃��[�h
    //virtual bool loadResource( const wchar_t FilePath[], ITexture* pOut ) = 0;

    //// �V�F�[�_�̃��[�h
    //virtual bool loadVertexShader( const char FilePath[], IShader* pOut ) = 0;
    //virtual bool loadPixelShader( const char FilePath[], IShader* pOut ) = 0;
    //// �V�F�[�_�̃A�����[�h
    //virtual void unloadShader( IShader* pOut ) = 0;
    
// Render
/*-----------------------------------------------------------------*/
    // ��ʂ̃N���A
    virtual void clear( float R, float G, float B, float A ) = 0;
    // ���f���̕`��
    virtual void render( const Model& Object ) = 0;

protected :
    IRenderer() = default;
};
END_EG_EG
#endif //INCLUDED_EG_EG_RENDERER_HEADER_
// EOF
