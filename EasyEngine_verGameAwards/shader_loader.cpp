// �쐬�� : ��
#include "shader_loader.hpp"
#include <fstream>

BEGIN_EGEG

// ShaderLoader �֐�����
/*===========================================================================*/
// �t�@�C���T�C�Y�̎擾
// �����̃t�@�C���X�g���[���͊��Ƀt�@�C�����J���Ă�����̂Ƃ���B
// ���̊֐��𔲂�����A�X�g���[���̓t�@�C���n�_���w���B
//
// in Stream : �T�C�Y���擾����t�@�C���X�g���[��
//
// return �t�@�C���T�C�Y
size_t ShaderLoader::getFileSize( std::fstream& Stream )
{
    Stream.seekg( 0, std::ios::end );
    auto end = Stream.tellg();
    Stream.clear();
    Stream.seekg( 0, std::ios::beg );
    auto beg = Stream.tellg();
    
    return static_cast<size_t>( end - beg );
}

END_EGEG
// EOF
