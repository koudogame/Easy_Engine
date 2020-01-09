///
/// @file   renderer_d3d11.hpp
/// @author ��
///
/// @brief  Direct3D11���g�p���������_���[�ł��B<br>
///         RendererFactory�ɂ�萶������܂��B
///
///
#ifndef INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#define INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
#include <unordered_map>
#include <Windows.h>
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EG_EG
class RendererD3D11 :
    public IRenderer
{
public :
    static IRenderer* create();

    void addRef() override { ++ref_cnt_; }
    void release() override;
    void beginRender( float* ) override;
    void setVertexShader( IVertexShader* ) override;
    void setPixelShader( IPixelShader* ) override;
    void setTexture( ITexture* ) override;
    void render( const Mesh& ) override;
    void endRender() override;


    void notifyRelease( ITexture* );        ///< �e�N�X�`���̉���ʒm���󂯎��܂��B
    void notifyRelease( IVertexShader* );   ///< ���_�V�F�[�_�[�̉���ʒm���󂯎��܂��B
    void notifyRelease( IPixelShader* );    ///<  �s�N�Z���V�F�[�_�[�̉���ʒm���󂯎��܂��B
private :
    bool initialize();  /// ���������� * �������ɌĂяo����܂��B
    ~RendererD3D11();

    unsigned ref_cnt_ = 0;  /// �Q�Ɛ��J�E���g

    HWND                    window_handle_;                     /// �o�̓^�[�Q�b�g�E�B���h�E�n���h��
    D3D_FEATURE_LEVEL       feature_level_;                     /// D3D�@�\���x��
    ID3D11Device*           p_device_ = nullptr;                /// D3D�f�o�C�X�C���^�[�t�F�C�X
    ID3D11DeviceContext*    p_immediate_context_ = nullptr;     /// D3D�f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
    IDXGISwapChain*         p_swap_chain_ = nullptr;            /// DXGI�X���b�v�`�F�C���C���^�[�t�F�X
    ID3D11RenderTargetView* p_render_target_view_ = nullptr;    /// D3D�`��^�[�Q�b�g�r���[�C���^�[�t�F�C�X

    std::unordered_map<const wchar_t*, ITexture*> textures_;            /// �e�N�X�`���L���b�V��
    std::unordered_map<const char*, IVertexShader*> vertex_shaderes_;   /// ���_�V�F�[�_�L���b�V��
    std::unordered_map<const char*, IPixelShader*> pixel_shaderes_;     /// �s�N�Z���V�F�[�_�L���b�V��
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_RENDERER_D3D11_HEADER_
/// EOF
