///
/// @file    shader_manager.hpp
/// @author  ��
///          
/// @brief   �V�F�[�_�[�}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          ���̃N���X���g�p���ēǂݍ��񂾃V�F�[�_�[�́A�K�����̃N���X�ŊJ�����Ă��������B<br>
///          �ǂݍ��񂾃V�F�[�_�[��ێ����A���̃N���X�̔j�����ɊJ������Ă��Ȃ��V�F�[�_�[���J�����܂��B
///
#ifndef INCLUDED_EGEG_SHADER_MANAGER_HEADER_
#define INCLUDED_EGEG_SHADER_MANAGER_HEADER_
#include <unordered_set>
#include "easy_engine.hpp"
#include "shader_loader.hpp"
BEGIN_EGEG
class ShaderManager
{
public :
    ///
    /// @brief  �C���X�^���X�ւ̃A�N�Z�X
    ///
    /// @return �C���X�^���X
    ///
    static ShaderManager* instance() { return instance_; }

    ///
    /// @brief  ���_�V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppVertexShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    bool loadVertexShader( const char* FilePath, IVertexShader** ppVertexShader );
    ///
    /// @brief   ���_�V�F�[�_�\�̊J��
    /// @details �����Ŏ󂯎�����C���^�[�t�F�C�X�ɂ́Anullptr���������܂��B
    ///
    /// @param[inout] ppVertexShader : �J�����钸�_�V�F�[�_�\
    ///
    void releaseVertexShader( IVertexShader** ppVertexShader );

    ///
    /// @brief  �W�I���g���V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppGeometryShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    bool loadGeometryShader( const char* FilePath, IGeometryShader** ppGeometryShader );
    ///
    /// @brief   �W�I���g���V�F�[�_�[�̊J��
    /// @details �����Ŏ󂯎�����C���^�[�t�F�C�X�ɂ́Anullptr���������܂��B
    ///
    /// @param[inout] ppGeometryShader : �J������W�I���g���V�F�[�_�[
    ///
    void releaseGeometryShader( IGeometryShader** ppGeometryShader );

    ///
    /// @brief  �s�N�Z���V�F�[�_�\�̓ǂݍ���
    ///
    /// @param[in] FilePath : �R���p�C���ς݃V�F�[�_�[�̃t�@�C���p�X
    /// @param[out] ppPixelShader : �ǂݍ��񂾃V�F�[�_�[���󂯎��C���^�[�t�F�C�X
    ///
    /// @return �ǂݍ��݂ɐ���[ true ] �ǂݍ��݂Ɏ��s[ false ]
    ///
    bool loadPixelShader( const char* FilePath, IPixelShader** ppPixelShader );
    ///
    /// @brief   �s�N�Z���V�F�[�_�\�̊J��
    /// @details �����Ŏ󂯎�����C���^�[�t�F�C�X�ɂ́Anullptr���������܂��B
    ///
    /// @param[inout] ppPixelShader : �J������s�N�Z���V�F�[�_�\
    ///
    void releasePixelShader( IPixelShader** ppPixelShader );

    ///
    /// @brief  �C���X�^���X�̐���
    ///
    /// @param[in] pCreator : ������
    /// @param[in] pShaderLoader : �g�p����V�F�[�_�[���[�_�[
    ///
    static void create( EasyEngine* pCreator, IShaderLoader* pShaderLoader );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] pDeleter : �j����
    ///
    static void destroy( EasyEngine* pDeleter );
    ~ShaderManager();

    ShaderManager( const ShaderManager& ) = delete;
    ShaderManager& operator=( const ShaderManager& ) = delete;
private :
    ShaderManager( IShaderLoader* );
    static ShaderManager* instance_;
    IShaderLoader* p_loader_;
    std::unordered_set<IVertexShader*> vs_list_;    /// ���̃N���X���g�p���Đ������ꂽ�A���_�V�F�[�_�\���X�g
    std::unordered_set<IGeometryShader*> gs_list_;  /// ���̃N���X���g�p���Đ������ꂽ�A�W�I���g���V�F�[�_���X�g
    std::unordered_set<IPixelShader*> ps_list_;     /// ���̃N���X���g�p���Đ������ꂽ�A�s�N�Z���V�F�[�_�\���X�g
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_MANAGER_HEADER_
/// EOF