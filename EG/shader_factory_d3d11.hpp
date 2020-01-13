///
/// @file    shader_factory_d3d11.hpp
/// @author  ��
///          
/// @brief   D3D11�p�V�F�[�_�[�t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          �V�����V�F�[�_�[�̓o�^��REGISTER_SHADER�}�N�����g�p���ĉ������B
///
#ifndef INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
#define INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
#include <unordered_map>
#include "shader_factory.hpp"
BEGIN_EGEG
class ShaderFactoryD3D11 :
    public IShaderFactory
{
public : 
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static ShaderFactoryD3D11* instance() { static ShaderFactoryD3D11 i; return &i; }

    ///
    /// @brief  �V�F�[�_�[�̓o�^
    ///
    /// @param[in] Name : �V�F�[�_�[�̖��O
    /// @param[in] pCreateFunction : �V�F�[�_�[�̐����֐��̃A�h���X
    ///
    void registerShader( const char* Name, IShader*(*pCreateFunction)() )
    {
        creators_[Name] = pCreateFunction;
    }
   
// IShaderFactory
/*-----------------------------------------------------------------*/
    bool create( const char* Name, IShader** ppOutShader ) override
    {
        auto find = creators_.find( Name );
        if( find == creators_.end() ) return false;

        *ppOutShader = find->second();
        if( *ppOutShader == nullptr)  return false;

        return true;
    }

private :
    std::unordered_map<const char*, IShader*(*)()> creators_;
};


class REGISTER_SHADER_D3D11
{
public :
    REGISTER_SHADER_D3D11( const char* Name, IShader*(*pFunc)() )
    {
        ShaderFactoryD3D11::instance()->registerShader(Name, pFunc);
    }
};
///
/// @def     REGISTER_SHADER_D3D11
/// @brief   �V�F�[�_�[��D3D11�̃V�F�[�_�[�t�@�N�g���ɓo�^���܂��B
/// @details �w�b�_�[�ŌĂяo���Ȃ��ł��������B
///
/// @param[in] Name : �o�^����V�F�[�_�[�̖��O
/// @param[in] pCreateFunction : �������������������֐��̃A�h���X
///
#define REGISTER_SHADER_D3D11( Name, pCreateFunction ) \
BEGIN_EGEG \
namespace impl{} namespace { namespace impl { \
REGISTER_SHADER_D3D11 register_the_shader( Name, pCreateFunction ); \
}} END_EGEG

END_EGEG
#endif /// !INCLUDED_EG_EG_SHADER_FACTORY_D3D11_HEADER_
/// EOF
