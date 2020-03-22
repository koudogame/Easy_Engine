// �쐬�� : ��
#include "WavefrontOBJ_loader.hpp"
#include <fstream>

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

    if( mesh_itr == mesh_cache_.end() )
    { // �L���b�V���ɑ��݂��Ȃ��ꍇ
        // �V�K�ɓǂݍ��݁A�L���b�V���ɕۑ�
        auto mesh = loadMeshFromFile( FileName.c_str() );
        if( mesh ) mesh_cache_.emplace( std::move(FileName), mesh.get() );

        return mesh;
    }
    else if( mesh_itr->second.expired() )
    { // �L���b�V���ɂ��邪�A���ɔj������Ă����ꍇ
        // �ēx�ǂݍ��ݕۊǁB����ǂݍ��݂ł͂Ȃ��̂ŁA���[�h�̃`�F�b�N���s���Ă��Ȃ��B
        auto mesh = loadMeshFromFile( FileName.c_str() );
        mesh_itr->second = mesh.get();

        // Attention : ���̃u���b�N�𔲂���ƃX�}�[�g�|�C���^�̃f�X�g���N�^���Ăяo����A
        //             �m�ۂ�������������������̂ł��̃u���b�N����return����錾���Ă���B
        return mesh;
    }

    // �L���b�V������Ă��郁�b�V����ԋp
    return DetailedReturnValue<std::shared_ptr<const Mesh>>( true, mesh_itr->second );
}

// .obj�t�@�C�����烁�b�V���f�[�^�����[�h
DetailedReturnValue<std::shared_ptr<const Mesh>> WavefrontOBJLoader::loadMeshFromFile( const char* FileName )
{
    using RetTy = DetailedReturnValue<std::shared_ptr<const Mesh>>;

    // �t�@�C���I�[�v��
    std::fstream stream( FileName );
    if( !stream )
    { // �t�@�C���I�[�v�����s
        return RetTy( false, nullptr, "�t�@�C���I�[�v�����s" );
    }

    std::vector<VertexPositionType> position; position.reserve( 256U );
    std::vector<VertexUVType>       texcoord; texcoord.reserve( 256U );
    std::vector<VertexNormalType>   normal;   normal.reserve( 256U );
    std::vector<UINT>               index;    index.reserve( 1024U );
    std::vector<VertexPositionType> position_for_buf; position_for_buf.reserve( 256U );
    std::vector<VertexUVType>       texcoord_for_buf; texcoord_for_buf.reserve( 256U );
    std::vector<VertexNormalType>   normal_for_buf;   normal_for_buf.reserve( 256U );

    std::string data_type;
    UINT start_idx = 0U;
    VertexPositionType vp;
    VertexUVType       vt;
    VertexNormalType   vn;
    while( stream >> data_type )
    { // �t�@�C�����璸�_�f�[�^��ǂݍ���
        if( data_type == "v" )
        { // ���_���W�̓ǂݍ���
            stream >> vp.x >> vp.y >> vp.z;
            position.push_back( vp );
        }
        else if( data_type == "vt" )
        { // �e�N�X�`�����W�̓ǂݍ���
            stream >> vt.x >> vt.y;
            texcoord.push_back( vt );
        }
        else if( data_type == "vn" )
        { // �@���x�N�g���̓ǂݍ���
            stream >> vn.x >> vn.y >> vn.z;
            normal.push_back( vn );
        }
        else if( data_type == "f" )
        { // ��(�|���S��)�̓ǂݍ���
            index.push_back( start_idx+ 2 );
            index.push_back( start_idx+ 1 );
            index.push_back( start_idx+ 0 );

            start_idx += 3;
        
            std::string str;
            int pos_idx;
            int uv_idx;
            int norm_idx;

            for( int i = 0; i < 3; ++i )
            {
                stream >> str;
                sscanf_s( str.data(),
                    "%d/%d/%d",
                    &pos_idx, &uv_idx, &norm_idx
                );

                // ���_���f�[�^��
                position_for_buf.push_back( position.at(pos_idx - 1) );
                texcoord_for_buf.push_back( texcoord.at(uv_idx - 1) );
                normal_for_buf.push_back( normal.at(norm_idx - 1) );
            }
        }
    }
    stream.close();

    // �o�b�t�@�I�u�W�F�N�g�̍쐬
    ID3D11Buffer* position_buffer;
    D3D11_BUFFER_DESC desc {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof( VertexPositionType ) * position_for_buf.size();
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA srd {};
    srd.pSysMem = position_for_buf.data();
    device_->CreateBuffer( &desc, &srd, &position_buffer );

    ID3D11Buffer* index_buffer;
    desc.ByteWidth = sizeof( UINT ) * index.size();
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    srd.pSysMem = index.data();
    device_->CreateBuffer( &desc, &srd, &index_buffer );
    
    // ���b�V���f�[�^�̍쐬
    Mesh* mesh = new Mesh();
    mesh->setVertexBuffer( kVertexPositionSemantic, position_buffer );
    mesh->setIndexBuffer( index_buffer );
    mesh->setNumVertices( index.size() );
    position_buffer->Release();
    index_buffer->Release();

    return RetTy(true, std::unique_ptr<Mesh>(mesh) );
}
END_EGEG
// EOF
