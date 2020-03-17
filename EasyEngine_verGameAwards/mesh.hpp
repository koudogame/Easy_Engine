///
/// @file   mesh.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MESH_HEADER_
#define INCLUDED_EGEG_MESH_HEADER_
#include <type_traits>
#include <string>
#include <unordered_map>
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "egeg.hpp"
BEGIN_EGEG
static constexpr LPCSTR kVertexPositionSemantic = "POSITION";
static constexpr LPCSTR kVertexUVSemantic       = "TEXCOORD";
static constexpr LPCSTR kVertexNormalSemantic   = "NORMAL";
using VertexPositionType = DirectX::XMFLOAT3;
using VertexUVType       = DirectX::XMFLOAT2;
using VertexNormalType   = DirectX::XMFLOAT3;
///
/// @class  Mesh
/// @brief  ���_�f�[�^
///
class Mesh
{
public :
    Mesh() = default;

    ///< ���_���̃Z�b�g
    void setNumVertices( UINT Num ) noexcept { num_vertices_ = Num; }
    ///< ���_���̎擾
    UINT getNumVertices() const noexcept { return num_vertices_; }

    ///
    /// @brief  ���_�o�b�t�@�̃Z�b�g
    ///
    /// @param[in] Semantic : ���_�o�b�t�@�̃Z�}���e�B�b�N
    /// @param[in] Buffer   : �ݒ肷�钸�_�o�b�t�@
    ///
    template <class StringType, class BufferType>
    void setVertexBuffer( StringType&& Semantic, BufferType&& Buffer ) 
    {
        auto buffer_itr = vertex_buffers_.find( Semantic );
        if( buffer_itr != vertex_buffers_.end() )
            buffer_itr->second = std::forward<BufferType>( Buffer );
        else
            vertex_buffers_.emplace( std::forward<StringType>(Semantic), std::forward<BufferType>(Buffer) );
    }
    ///< �C���f�b�N�X�o�b�t�@�̃Z�b�g
    template <class BufferType>
    void setIndexBuffer( BufferType&& Buffer ) 
    {
        index_buffer_ = std::forward<BufferType>( Buffer ); 
    }
    ///
    /// @brief   ���_�o�b�t�@�̎擾
    /// @details �Ή��������_�o�b�t�@���Ȃ��ꍇ�A�߂�l��nullptr�ł��B
    ///
    /// @param[in] Semantic : �擾���钸�_�o�b�t�@�̃Z�}���e�B�b�N
    ///
    /// @return �Z�}���e�B�b�N�ɑΉ��������_�o�b�t�@
    ///
    Microsoft::WRL::ComPtr<ID3D11Buffer> getVertexBuffer( const char* Semantic ) const
    {
        auto buffer_itr = vertex_buffers_.find( Semantic );
        if( buffer_itr == vertex_buffers_.end() ) return nullptr;
        
        return buffer_itr->second;
    }
    ///< �C���f�b�N�X�o�b�t�@�̎擾
    Microsoft::WRL::ComPtr<ID3D11Buffer> getIndexBuffer() const noexcept
    {
        return index_buffer_;
    }

private :
    UINT num_vertices_;
    std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>> vertex_buffers_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_MESH_HEADER_
/// EOF
