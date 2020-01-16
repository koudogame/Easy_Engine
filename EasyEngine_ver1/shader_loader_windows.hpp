///
/// @file   shader_loader_windows.hpp
/// @author ��
///
/// @brief  Windows�p�V�F�[�_�[���[�_�[
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "shader_loader.hpp"
BEGIN_EGEG
class ShaderLoaderWindows :
    public IShaderLoader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pDevice : D3D�f�o�C�X
    ///
    ShaderLoaderWindows( ID3D11Device* pDevice );

// IShaderLoader
/*-----------------------------------------------------------------*/
    bool loadVertexShader( const std::string&, IVertexShader** ) override;
    bool loadGeometryShader( const std::string&, IGeometryShader** ) override;
    bool loadPixelShader( const std::string&, IPixelShader** ) override;

private :
    ~ShaderLoaderWindows();
    ID3D11Device* p_device_;    /// D3D�f�o�C�X
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
/// EOF
