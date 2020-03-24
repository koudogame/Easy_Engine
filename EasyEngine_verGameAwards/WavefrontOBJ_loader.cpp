// �쐬�� : ��
#include "WavefrontOBJ_loader.hpp"
#include <fstream>

namespace
{
    template <class VertexDataType>
    ID3D11Buffer* createBufferFromData( ID3D11Device*, D3D11_BUFFER_DESC*, const std::vector<VertexDataType>& );
} // unnamed namespace

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
    std::vector<UINT>               index_for_buf;    index_for_buf.reserve( 1024U );
    std::vector<VertexPositionType> position_for_buf; position_for_buf.reserve( 256U );
    std::vector<VertexUVType>       texcoord_for_buf; texcoord_for_buf.reserve( 256U );
    std::vector<VertexNormalType>   normal_for_buf;   normal_for_buf.reserve( 256U );

    std::string command;    // �R�}���h�i�[�p�o�b�t�@
    UINT start_idx = 0U;    // �|���S���̊J�n�C���f�b�N�X
    VertexPositionType vp;  // ���_���W�p�ꎞ�I�u�W�F�N�g
    VertexUVType       vt;  // UV���W�p�ꎞ�I�u�W�F�N�g
    VertexNormalType   vn;  // �@���x�N�g���p�ꎞ�I�u�W�F�N�g
    while( stream >> command )
    { // �t�@�C������f�[�^��ǂݍ���
        if( command == "v" )
        { // ���_���W�̓ǂݍ���
            stream >> vp.x >> vp.y >> vp.z;
            position.push_back( vp );
        }
        else if( command == "vt" )
        { // �e�N�X�`�����W�̓ǂݍ���
            stream >> vt.x >> vt.y;
            texcoord.push_back( vt );
        }
        else if( command == "vn" )
        { // �@���x�N�g���̓ǂݍ���
            stream >> vn.x >> vn.y >> vn.z;
            normal.push_back( vn );
        }
        else if( command == "f" )
        { // ��(�O�p�`�|���S��)�̓ǂݍ���
            index_for_buf.push_back( start_idx+ 2 );
            index_for_buf.push_back( start_idx+ 1 );
            index_for_buf.push_back( start_idx+ 0 );

            start_idx += 3;
        
            std::string str;
            int pos_idx;
            int uv_idx;
            int norm_idx;
            for( int i = 0; i < 3; ++i )
            { // �|���S�����`������R���_��ǂݍ���
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
    D3D11_BUFFER_DESC desc {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    ID3D11Buffer* position_buffer = ::createBufferFromData(device_.Get(), &desc, position_for_buf );
    if( position_buffer == nullptr )
    { // �o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s
        return RetTy( false, nullptr, "���_���W�p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }

    ID3D11Buffer* texcoord_buffer = ::createBufferFromData(device_.Get(), &desc, texcoord_for_buf );
    if( texcoord_buffer == nullptr )
    { // �o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s
        position_buffer->Release();
        return RetTy( false, nullptr, "UV���W�p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }

    ID3D11Buffer* normal_buffer = ::createBufferFromData(device_.Get(), &desc, normal_for_buf );
    if( normal_buffer == nullptr )
    { // �o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s
        position_buffer->Release();
        texcoord_buffer->Release();
        return RetTy( false, nullptr, "�@���x�N�g���p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }
    

    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ID3D11Buffer* index_buffer = ::createBufferFromData(device_.Get(), &desc, index_for_buf );
    if( index_buffer == nullptr )
    { // �o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s
        position_buffer->Release();
        texcoord_buffer->Release();
        normal_buffer->Release();
        return RetTy( false, nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s" );
    }
    
    // ���b�V���f�[�^�̍쐬
    Mesh* mesh = new Mesh();
    mesh->setVertexBuffer( kVertexPositionSemantic, position_buffer );
    mesh->setVertexBuffer( kVertexUVSemantic, texcoord_buffer );
    mesh->setVertexBuffer( kVertexNormalSemantic, normal_buffer );
    mesh->setIndexBuffer( index_buffer );
    mesh->setNumVertices( index_for_buf.size() );
    position_buffer->Release();
    texcoord_buffer->Release();
    normal_buffer->Release();
    index_buffer->Release();

    return RetTy(true, std::unique_ptr<Mesh>(mesh) );
}

END_EGEG

namespace
{
    template <class VertexDataType>
    ID3D11Buffer* createBufferFromData( ID3D11Device* Device, D3D11_BUFFER_DESC* Desc,  const std::vector<VertexDataType>& Source )
    {
        ID3D11Buffer* buffer = nullptr;
        Desc->ByteWidth = sizeof( VertexDataType ) * Source.size();
        D3D11_SUBRESOURCE_DATA srd{};
        srd.pSysMem = Source.data();

        Device->CreateBuffer( Desc, &srd, &buffer );
        return buffer;
    }
} // unnamed namespace
// EOF
