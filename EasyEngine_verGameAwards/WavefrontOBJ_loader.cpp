// �쐬�� : ��
#include "WavefrontOBJ_loader.hpp"
#include "texture_loader.hpp"

BEGIN_EGEG

// WavefrontOBJLoader �֐���`
/*===========================================================================*/
// �R���X�g���N�^
WavefrontOBJLoader::WavefrontOBJLoader() 
{
    initialize();
}

// ������
void WavefrontOBJLoader::initialize()
{
    // �ǂݍ��݊֐����Z�b�g
    //  �L�[ �̓R�}���h
    //  �v�f �̓R�}���h�ɑΉ������֐��̃A�h���X
    load_function_list_.emplace( "v", &WavefrontOBJLoader::loadVertexPosition );
    load_function_list_.emplace( "vt", &WavefrontOBJLoader::loadVertexUV );
    load_function_list_.emplace( "vn", &WavefrontOBJLoader::loadVertexNormal );
    load_function_list_.emplace( "f", &WavefrontOBJLoader::loadFace );
    load_function_list_.emplace( "g", &WavefrontOBJLoader::loadGroupName );
    load_function_list_.emplace( "mtllib", &WavefrontOBJLoader::loadMaterialFile );
    load_function_list_.emplace( "usemtl", &WavefrontOBJLoader::loadUseMaterialName );
    load_function_list_.emplace( "newmtl", &WavefrontOBJLoader::loadMaterialName );
    load_function_list_.emplace( "Kd", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialDiffuseColor> );
    load_function_list_.emplace( "Ks", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialSpecularColor> );
    load_function_list_.emplace( "Ka", &WavefrontOBJLoader::loadMaterialColor<Tag_MaterialAmbientColor> );
    load_function_list_.emplace( "d", &WavefrontOBJLoader::loadMaterialFloat<Tag_MaterialTransparency> );
    load_function_list_.emplace( "Ni", &WavefrontOBJLoader::loadMaterialFloat<Tag_MaterialRefractiveIndex> );
    load_function_list_.emplace( "map_Kd", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialDiffuseTexture> );
    load_function_list_.emplace( "map_Ks", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialSpecularTexture> );
    load_function_list_.emplace( "map_Ka", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialAmbientTexture> );
    load_function_list_.emplace( "map_Bump", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialBumpTexture> );
    load_function_list_.emplace( "map_D", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialTransparencyTexture> );
    load_function_list_.emplace( "refl", &WavefrontOBJLoader::loadMaterialTexture<Tag_MaterialreflectionTexture> );
}

// �t�@�C���ǂݍ���
DetailedResult<bool> WavefrontOBJLoader::load( const std::string& FileName, Mesh* Output, const CoordinateSystem CoorSys )
{
    using RetTy = DetailedResult<bool>;

    // �t�@�C���I�[�v��
    std::fstream stream( FileName );
    if( !stream )
    { // ���s
        return RetTy( Failure(), "�t�@�C���I�[�v���Ɏ��s" );
    }

    // �O��ǂݍ��ݎ��̃f�[�^���N���A
    //  std::vector::clear()�̌v�Z�ʂ͐��`���ԁB�O��̃f�[�^���N���A�����������x�I�ɖ��ʂ������B
    temp_output_.position.clear();
    temp_output_.uv.clear();
    temp_output_.normal.clear();
    temp_output_.position_for_buffer.clear();
    temp_output_.uv_for_buffer.clear();
    temp_output_.normal_for_buffer.clear();
    temp_output_.index_for_buffer.clear();
    temp_output_.curr_vertex_index = 0U;
    temp_output_.group_list.clear();
    temp_output_.material_list.clear();

    // ���W�n�̑I��
    temp_output_.coordinate_system = CoorSys;

    // �t�@�C���ǂݍ���
    std::string command;
    while( stream >> command )
    { // �t�@�C���I�[�܂œǂݍ���
        auto func_itr = load_function_list_.find( command.c_str() );
        if( func_itr != load_function_list_.end() )
        { // �Ή�����R�}���h�̏ꍇ�A�������s��
            (this->*func_itr->second)(stream);
        }
    }
    stream.close();

    // �o�b�t�@�I�u�W�F�N�g�̐���
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    // �o�͗p�f�[�^�̍쐬
    using namespace Microsoft::WRL;
    ComPtr<ID3D11Buffer> position_buffer;
    ComPtr<ID3D11Buffer> uv_buffer;
    ComPtr<ID3D11Buffer> normal_buffer;
    ComPtr<ID3D11Buffer> index_buffer;
    if( !engine_->createBuffer(&desc, temp_output_.position_for_buffer, &position_buffer) )
    { // ���s
        return RetTy( Failure(), "���W�p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.uv_for_buffer, &uv_buffer) )
    { // ���s
        return RetTy( Failure(), "UV���W�p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }
    if( !engine_->createBuffer(&desc, temp_output_.normal_for_buffer, &normal_buffer) )
    { // ���s
        return RetTy( Failure(), "�@���x�N�g���p���_�o�b�t�@�̍쐬�Ɏ��s" );
    }
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    if( !engine_->createBuffer(&desc, temp_output_.index_for_buffer, &index_buffer ) )
    { // ���s
        return RetTy( Failure(), "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s" );
    }

    // ���_�f�[�^���Z�b�g
    Output->vertices.set<Tag_VertexPosition>( position_buffer );
    Output->vertices.set<Tag_VertexUV>( uv_buffer );
    Output->vertices.set<Tag_VertexNormal>( normal_buffer );
    Output->vertices.set<Tag_VertexIndex>( index_buffer );
    // �T�u���b�V�����Z�b�g
    SubMesh submesh;
    for( auto& group : temp_output_.group_list )
    { // �O���[�v����T�u���b�V�����R�s�[
        auto mtl_itr = temp_output_.material_list.find(group.second.material_name);
        if( mtl_itr != temp_output_.material_list.end() )
            submesh.material = std::move( mtl_itr->second );
        submesh.start_index = group.second.start_index; 
        submesh.num_vertices = group.second.num_vertices;

        Output->submesh_list.push_back( submesh );
    }

    return Success();
}

// ���_���W�̓ǂݍ���
void WavefrontOBJLoader::loadVertexPosition( std::fstream& Stream )
{
    temp_output_.position.emplace_back();
    auto& pos = temp_output_.position.back();
    Stream >>
        pos.x >>
        pos.y >>
        pos.z;

    // �E����W�n�̃c�[���ō쐬���ꂽ���f���͕ϊ�����
    if( temp_output_.coordinate_system == CoordinateSystem::kRightHand )
    {
        pos.z *= -1.0F;
    }
}

// ���_UV���W�̓ǂݍ���
void WavefrontOBJLoader::loadVertexUV( std::fstream& Stream )
{
    temp_output_.uv.emplace_back();
    auto& uv = temp_output_.uv.back();
    Stream >>
        uv.x >>
        uv.y;
}

// ���_�@���x�N�g���̓ǂݍ���
void WavefrontOBJLoader::loadVertexNormal( std::fstream& Stream )
{
    temp_output_.normal.emplace_back();
    auto& normal = temp_output_.normal.back();
    Stream >>
        normal.x >>
        normal.y >>
        normal.z;
}

// �ʂ̓ǂݍ���
void WavefrontOBJLoader::loadFace( std::fstream& Stream )
{
    // �ʂ���������O���[�v
    auto group_itr = temp_output_.group_list.find(temp_output_.curr_group_name);
    if( group_itr == temp_output_.group_list.end() )
    { // �V�K�O���[�v�̏ꍇ�A���X�g�ɃO���[�v��ǉ�
        // Attention : �}�e���A���͈ꎞ�o�͂���R�s�[���Ă���B
        //             ���[�u�̕������������A���[�u�ɂ��s��������_�ŗ\�z�ł��Ȃ��B
        Group g;
        g.material_name = temp_output_.curr_material_name;
        g.start_index = temp_output_.curr_vertex_index;
        g.num_vertices = 0U;
        temp_output_.group_list.emplace(temp_output_.curr_group_name, std::move(g));
       
        group_itr = temp_output_.group_list.find(temp_output_.curr_group_name);
    }

    // �ʂ̒ǉ�( �C���f�b�N�X )
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index + 2U );
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index + 1U );
    temp_output_.index_for_buffer.push_back( temp_output_.curr_vertex_index );
    temp_output_.curr_vertex_index += 3U;
    group_itr->second.num_vertices += 3U;

    // �ʂ̒ǉ�( ���_ )
    std::string data;
    int pos_idx;
    int uv_idx;
    int nml_idx;
    for( int i = 0; i < 3; ++i )
    { // �ʂ��`�����钸�_��ǂݍ��� : 3���_��
        Stream >> data;
        sscanf_s( data.c_str(),
            "%d/%d/%d",
            &pos_idx,
            &uv_idx,
            &nml_idx
        );

        temp_output_.position_for_buffer.push_back( temp_output_.position.at(pos_idx - 1U) );
        temp_output_.uv_for_buffer.push_back( temp_output_.uv.at(uv_idx - 1U) );
        temp_output_.normal_for_buffer.push_back( temp_output_.normal.at(nml_idx - 1U) );
    }
}

// �O���[�v���ǂݍ���
void WavefrontOBJLoader::loadGroupName( std::fstream& Stream )
{
    Stream >> temp_output_.curr_group_name;
}

// �g�p�}�e���A�����ǂݍ���
void WavefrontOBJLoader::loadUseMaterialName( std::fstream& Stream )
{
    auto curr_group_itr = temp_output_.group_list.find( temp_output_.curr_group_name );
    if( curr_group_itr != temp_output_.group_list.end() )
    { // �O���[�v�Ɏg�p����}�e���A������ݒ�
        Stream >> curr_group_itr->second.material_name;
    }
}

// �}�e���A���t�@�C���̓ǂݍ���
void WavefrontOBJLoader::loadMaterialFile( std::fstream& Stream )
{
    std::string filename;
    Stream >> filename;

    // �t�@�C���I�[�v��
    std::fstream stream( filename );
    if( !stream ) return;

    // �t�@�C���ǂݍ���
    std::string command;
    while( stream >> command )
    { // �t�@�C���I�[�܂œǂݍ���
        auto func_itr = load_function_list_.find( command.c_str() );
        if( func_itr != load_function_list_.end() )
        { // �Ή�����R�}���h�̏ꍇ�A�������s��
            (this->*func_itr->second)(stream);
        }
    }
    stream.close();
}

// �}�e���A�����̓ǂݍ���
void WavefrontOBJLoader::loadMaterialName( std::fstream& Stream )
{
    Stream >> temp_output_.loading_material_name;
}

END_EGEG
// EOF
