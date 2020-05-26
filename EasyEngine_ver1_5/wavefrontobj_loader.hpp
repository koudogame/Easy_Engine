///
/// @file   wavefrontobj_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_
#define INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_

#include <unordered_map>
#include <fstream>
#include "model_loader.hpp"

BEGIN_EGEG

///
/// @class WavefrontobjLoader
/// @brief 「WavefrontOBJ形式(.obj)」ファイル用ローダー
///
class WavefrontobjLoader :
    public ModelLoader
{
public :  
    void loadVertexPosition( std::istream& );
    void loadVertexUV( std::istream& );
    void loadVertexNormal( std::istream& );
    void loadFace( std::istream& );
    void loadGroupName( std::istream& );
    void loadUseMaterialName( std::istream& );
    void loadMaterialFile( std::istream& );
    void loadMaterialName( std::istream& );
    template <class MaterialType>
    void loadMaterialFloat( std::istream& Stream )
    {
        float value;
        Stream >> value;

        temp_output_.materials[temp_output_.loading_material_name].
            set<MaterialType>( value );
    }
    template <class MaterialType>
    void loadMaterialColor( std::istream& Stream )
    {
        DirectX::XMFLOAT3 color;
        Stream >> color.x >> color.y >> color.z;

        temp_output_.materials[temp_output_.loading_material_name].
            set<MaterialType>( color );
    }
    template <class MaterialType>
    void loadMaterialTexture( std::istream& Stream )
    {
        std::string filename;
        Stream >> filename;
        temp_output_.materials[temp_output_.loading_material_name].
            set<MaterialType>( loadTexture(filename) );
    }

// override
    DetailedReturnValue<bool> load( const std::string&, CoordinateSystem, Mesh* ) override;

private :
    struct Group
    {
        std::string material_name;
        uint32_t start_index;
        uint32_t num_vertices;
    };
    struct TemporaryOutput
    {
        CoordinateSystem coordinate_system;
        std::vector<VertexPositionType> positions;
        std::vector<VertexUVType>       uvs;
        std::vector<VertexNormalType>   normals;
        std::vector<VertexPositionType> positions_buf;
        std::vector<VertexUVType>       uvs_buf;
        std::vector<VertexNormalType>   normals_buf;
        std::vector<uint32_t>           index_buf;
        std::string loading_group_name;
        std::unordered_map<std::string, Group> groups;
        std::string loading_material_name;
        std::unordered_map<std::string, Material> materials;
    };

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> loadTexture( const std::string& );
    
    TemporaryOutput temp_output_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_
/// EOF
