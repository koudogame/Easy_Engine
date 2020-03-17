///
/// @file   mesh.hpp
/// @author 板場
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
/// @brief  頂点データ
///
class Mesh
{
public :
    Mesh() = default;

    ///< 頂点数のセット
    void setNumVertices( UINT Num ) noexcept { num_vertices_ = Num; }
    ///< 頂点数の取得
    UINT getNumVertices() const noexcept { return num_vertices_; }

    ///
    /// @brief  頂点バッファのセット
    ///
    /// @param[in] Semantic : 頂点バッファのセマンティック
    /// @param[in] Buffer   : 設定する頂点バッファ
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
    ///< インデックスバッファのセット
    template <class BufferType>
    void setIndexBuffer( BufferType&& Buffer ) 
    {
        index_buffer_ = std::forward<BufferType>( Buffer ); 
    }
    ///
    /// @brief   頂点バッファの取得
    /// @details 対応した頂点バッファがない場合、戻り値はnullptrです。
    ///
    /// @param[in] Semantic : 取得する頂点バッファのセマンティック
    ///
    /// @return セマンティックに対応した頂点バッファ
    ///
    Microsoft::WRL::ComPtr<ID3D11Buffer> getVertexBuffer( const char* Semantic ) const
    {
        auto buffer_itr = vertex_buffers_.find( Semantic );
        if( buffer_itr == vertex_buffers_.end() ) return nullptr;
        
        return buffer_itr->second;
    }
    ///< インデックスバッファの取得
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
