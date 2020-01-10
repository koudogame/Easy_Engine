///
/// @file    shader_manager.hpp
/// @author  ��
///          
/// @brief   �V�F�[�_�[�Ǘ���
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          ���̃N���X��load�֐����g�p���ēǂݍ��񂾃e�N�X�`���́A<br>
///          ���̃N���X��release�֐����g�p���ĉ�����Ă��������B
/// 
#ifndef INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
#define INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
#include <unordered_map>
#include "shader_loader.hpp"
BEGIN_EG_EG
class ShaderManager
{
public :
    static ShaderManager* instance() { static ShaderManager i; return &i; }

    ///
    /// @brief   ���_�V�F�[�_�[��ǂݍ��݂܂��B
    /// @details �L���b�V���ɂȂ��ꍇ�A�V�K�ɓǂݍ��݂܂��B<br>
    ///          �L���b�V���ɂ���ꍇ�A���̃R�s�[��ԋp���܂��B
    ///
    /// @param[in] FilePath : �R���p�C���ςݒ��_�V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppOutTexture : �ǂݍ��񂾒��_�V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool loadVertexShader( const char* FilePath, IVertexShader** ppOutShader );
    
    ///
    /// @brief   �s�N�Z���V�F�[�_�[��ǂݍ��݂܂��B
    /// @details �L���b�V���ɂȂ��ꍇ�A�V�K�ɓǂݍ��݂܂��B<br>
    ///          �L���b�V���ɂ���ꍇ�A���̃R�s�[��ԋp���܂��B
    ///
    /// @param[in] FilePath : �R���p�C���ς݃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppOutTexture : �ǂݍ��񂾃s�N�Z���V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool loadPixelShader( const char* FilePath, IPixelShader** ppOutShader );

    ///
    /// @brief   ���_�V�F�[�_�[�̉�����s���܂��B
    /// @details �����̃C���^�[�t�F�C�X�ɂ́A�����nullptr�������܂��B<br>
    ///          �L���b�V������폜�����^�C�~���O�͎Q�Ǝ҂����Ȃ��Ȃ������ł��B
    ///
    /// @param[inout] ppShader : ����Ώۂ̒��_�V�F�[�_�[
    ///
    void releaseVertexShader( IVertexShader** ppShader );
    
    ///
    /// @brief   �s�N�Z���V�F�[�_�[�̉�����s���܂��B
    /// @details �����̃C���^�[�t�F�C�X�ɂ́A�����nullptr�������܂��B<br>
    ///          �L���b�V������폜�����^�C�~���O�͎Q�Ǝ҂����Ȃ��Ȃ������ł��B
    ///
    /// @param[inout] ppShader : ����Ώۂ̃s�N�Z���V�F�[�_�[
    ///
    void releasePixelShader( IPixelShader** ppShader );


    ~ShaderManager()
    {
        p_loader_->release();
    }
private :
    ShaderManager();

    IShaderLoader* p_loader_;
    std::unordered_map<const char*, IVertexShader*> vs_cache_;
    std::unordered_map<const char*, IPixelShader*>  ps_cache_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_SHADER_MANAGER_HEADER_
/// EOF
