///
/// @file   WavefrontOBJ_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_
#define INCLUDED_EGEG_WAVEFRONTOBJ_LOADER_HEADER_
#include <type_traits>
#include <memory>
#include <unordered_map>
#include "loader.hpp"
#include "detailed_returnvalue.hpp"
#include "mesh.hpp"
BEGIN_EGEG
///
/// @class  WavefrontOBJLoader
/// @brief  「WavefrontOBJ形式」ファイルのローダー
///
class WavefrontOBJLoader :
    public Loader
{
public :
    template <class DeviceType>
    WavefrontOBJLoader( DeviceType&& Device ) :
        Loader( std::forward<DeviceType>(Device) )
    {}
    
    ///
    /// @brief  「.obj」ファイルからメッシュデータをロード
    ///
    /// @param[in] FileName : 読み込むファイル名( ファイル名.obj )
    ///
    /// @return ロードしたメッシュデータ
    ///
    DetailedReturnValue<std::shared_ptr<const Mesh>> loadMesh( std::string FileName );
    
    // TODO : 定義
    ///
    /// @brief  「.mtl」ファイルからマテリアルデータをロード
    ///
    /// @param[in] FileName : 読み込むファイル名( ファイル名.mtl )
    ///
    /// @return ロードしたマテリアルデータ
    ///
    DetailedReturnValue<bool> loadMaterial( std::string FileName );

    // TODO : 定義
    ///
    /// @brief  「.obj」ファイルからメッシュデータとマテリアルデータをロード
    ///
    /// @param[in] FileName : 読み込むファイル名( ファイル名.obj )
    ///
    DetailedReturnValue<bool> loadModel( std::string FileName );

private :
    DetailedReturnValue<std::shared_ptr<const Mesh>> loadMeshFromFile( const char* FileName );

    std::unordered_map<std::string, std::weak_ptr<const Mesh>> mesh_cache_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_LOADER_HEADER_
/// EOF
