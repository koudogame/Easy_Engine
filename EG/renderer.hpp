#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
// �쐬�� : ��
#include "interface.hpp"
#include "vertex_shader.hpp"
#include "pixel_shader.hpp"
#include "texture.hpp"
#include "mesh.hpp"

BEGIN_EG_EG
enum RendererID
{
    kDirect3D11,
};
//
// �����_���[�C���^�[�t�F�C�X
// RendererFactory�ɂ�萶������邱�Ƃ�O��Ƃ��Ă��܂��B
//
// ���������ς�ł��Ȃ��C���^�[�t�F�C�X�̐�����h�����߁A
// �C���X�^���X���𐧌����Ă��܂��B
//
class IRenderer :
    public Interface
{
public :
    virtual ~IRenderer() = default;
    
// FileIO
/*-----------------------------------------------------------------*/
    // �e�N�X�`�����\�[�X�̃��[�h
    virtual bool loadTexture( const wchar_t FilePath[], ITexture** ppOutTexture ) = 0;
    // ���_�V�F�[�_�̃��[�h
    virtual bool loadVertexShader( const char FilePath[], IVertexShader** ppOutShader ) = 0;
    // �s�N�Z���V�F�[�_�̃��[�h
    virtual bool loadPixelShader( const char FilePath[], IPixelShader** ppOutShader ) = 0;
    
// Render
/*-----------------------------------------------------------------*/
    // �����_�[�J�n
    virtual void beginRender( float BackColorRGBA[4] ) = 0;
    // ���_�V�F�[�_�̐ݒ�
    virtual void setVertexShader( IVertexShader* pVertexShader ) = 0;
    // �s�N�Z���V�F�[�_�̐ݒ�
    virtual void setPixelShader( IPixelShader* pPixelShader ) = 0;
    // �e�N�X�`���̐ݒ�
    virtual void setTexture( ITexture* pTexture ) = 0;
    // ���b�V���̕`��
    virtual void render( const Mesh& Object ) = 0;
    // �����_�[�I��
    virtual void endRender() = 0;

protected :
    IRenderer() = default;
};
END_EG_EG
#endif //INCLUDED_EG_EG_RENDERER_HEADER_
// EOF
