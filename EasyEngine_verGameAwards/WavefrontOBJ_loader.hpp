///
/// @file   WavefrontOBJ_loader.hpp
/// @author ��
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
/// @brief  �uWavefrontOBJ�`���v�t�@�C���̃��[�_�[
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
    /// @brief  �u.obj�v�t�@�C�����烁�b�V���f�[�^�����[�h
    ///
    /// @param[in] FileName : �ǂݍ��ރt�@�C����( �t�@�C����.obj )
    ///
    /// @return ���[�h�������b�V���f�[�^
    ///
    DetailedReturnValue<std::shared_ptr<const Mesh>> loadMesh( std::string FileName );
    
    // TODO : ��`
    ///
    /// @brief  �u.mtl�v�t�@�C������}�e���A���f�[�^�����[�h
    ///
    /// @param[in] FileName : �ǂݍ��ރt�@�C����( �t�@�C����.mtl )
    ///
    /// @return ���[�h�����}�e���A���f�[�^
    ///
    DetailedReturnValue<bool> loadMaterial( std::string FileName );

    // TODO : ��`
    ///
    /// @brief  �u.obj�v�t�@�C�����烁�b�V���f�[�^�ƃ}�e���A���f�[�^�����[�h
    ///
    /// @param[in] FileName : �ǂݍ��ރt�@�C����( �t�@�C����.obj )
    ///
    DetailedReturnValue<bool> loadModel( std::string FileName );

private :
    DetailedReturnValue<std::shared_ptr<const Mesh>> loadMeshFromFile( const char* FileName );

    std::unordered_map<std::string, std::weak_ptr<const Mesh>> mesh_cache_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_LOADER_HEADER_
/// EOF
