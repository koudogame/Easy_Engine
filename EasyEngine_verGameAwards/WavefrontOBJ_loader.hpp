///
/// @file   WavefrontOBJ_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_
#define INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_

#include <type_traits>
#include <memory>
#include <unordered_map>
#include <fstream>
#include "rendering_engine_child.hpp"
#include "detailed_returnvalue.hpp"
#include "mesh.hpp"

BEGIN_EGEG

///
/// @class  WavefrontOBJLoader
/// @brief  「WavefrontOBJ形式」ファイルのローダー
///
class WavefrontOBJLoader :
    public RenderingEngineChild
{
public :
    WavefrontOBJLoader();
    ~WavefrontOBJLoader() = default;

    DetailedReturnValue<bool> load( const std::string& FileName, Mesh* Output );
    
private :
    struct Group
    {
        std::string material_name;
        uint32_t start_index;
        uint32_t num_vertices;
    };
    struct TemporaryOutput
    {
        std::vector<VertexPositionType> position;
        std::vector<VertexUVType>       uv;
        std::vector<VertexNormalType>   normal;
        std::vector<VertexPositionType> position_for_buffer;
        std::vector<VertexUVType>       uv_for_buffer;
        std::vector<VertexNormalType>   normal_for_buffer;
        std::vector<uint32_t>           index_for_buffer;
        std::string curr_group_name;
        std::string curr_material_name;
        uint32_t    curr_vertex_index;
        std::unordered_map<std::string, Group>    group_list;
        std::unordered_map<std::string, Material> material_list;

        std::string loading_material_name;
    };

    void initialize();

    void loadVertexPosition( std::fstream& );
    void loadVertexUV( std::fstream& );
    void loadVertexNormal( std::fstream& );
    void loadFace( std::fstream& );
    void loadGroupName( std::fstream& );
    void loadUseMaterialName( std::fstream& );
    void loadMaterialFile( std::fstream& );
    void loadMaterialName( std::fstream& );
    void loadMaterialDiffuseColor( std::fstream& );
    void loadMaterialSpecularColor( std::fstream& );
    void loadMaterialAmbientColor( std::fstream& );
    void loadMaterialTransparency( std::fstream& );
    void loadMaterialRefractiveIndex( std::fstream& );
    void loadMaterialDiffiuseMap( std::fstream& );
    void loadMatarialSpecularMap( std::fstream& );
    void loadMaterialAmbientMap( std::fstream& );
    void loadMaterialBumpMap( std::fstream& );
    void loadMaterialTransparencyMap( std::fstream& );
    void loadmaterialReflectionMap( std::fstream& );


    std::unordered_map<std::string, void(WavefrontOBJLoader::*)(std::fstream&)> load_function_list_;
    TemporaryOutput temp_output_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MESH_LOADER_HEADER_
/// EOF
