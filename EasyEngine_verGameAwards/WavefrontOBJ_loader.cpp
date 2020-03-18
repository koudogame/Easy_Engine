// �쐬�� : ��
#include "WavefrontOBJ_loader.hpp"

BEGIN_EGEG

// WavefrontOBJ �֐���`
/*===========================================================================*/
// .obj�t�@�C�����烁�b�V���f�[�^�����[�h
// �L���b�V���Ƀf�[�^������ꍇ�A�R�s�[��ԋp
//
// �ǂݍ��񂾃��b�V���f�[�^�̓L���b�V���Ɋi�[����B
DetailedReturnValue<std::shared_ptr<const Mesh>> WavefrontOBJLoader::loadMesh(
    std::string FileName )
{
    auto mesh_itr = mesh_cache_.find( FileName ); // �L���b�V�����烁�b�V���f�[�^���擾

    if( mesh_itr != mesh_cache_.end() )
    { // �L���b�V���ɑ��݂��Ȃ��ꍇ
        // �V�K�ɓǂݍ��݁A�L���b�V���ɕۑ�
        /*auto mesh = loadMeshFromFile( FileName.c_str() );
        if( mesh ) mesh_cache_.emplace( std::move(FileName), mesh.get() );

        return mesh;*/
    }
    else if( mesh_itr->second.expired() )
    { // �L���b�V���ɂ��邪�A���ɔj������Ă����ꍇ
        // �ēx�ǂݍ��݁A�Ή�����ʒu�ɕۊ�
        //auto mesh = loadMeshFromFile( FileName.c_str() );
        //mesh_itr->second = mesh.get();

        //// Attention : ���̃u���b�N�𔲂���ƃX�}�[�g�|�C���^�̃f�X�g���N�^���Ăяo����A
        ////             �m�ۂ�������������������̂ł��̃u���b�N����return����錾���Ă���B
        //return mesh;
    }

    // �L���b�V������Ă��郁�b�V����ԋp
    return DetailedReturnValue<std::shared_ptr<const Mesh>>( true, mesh_itr->second );
}

// 
END_EGEG
// EOF
