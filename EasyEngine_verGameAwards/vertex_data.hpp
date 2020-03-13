///
/// @file   vertex_data.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_VERTEX_DATA_HEADER_
#define INCLUDED_EGEG_VERTEX_DATA_HEADER_
#include <unordered_map>
#include <d3d11.h>
#include <DirectXMath.h>
#include "egeg.hpp"
BEGIN_EGEG
static LPCSTR kVertexPositionSemantic = "POSITION";
static LPCSTR kVertexUVSemantic       = "TEXCOORD";
static LPCSTR kVertexNormalSemantic   = "NORMAL";
using VertexPositionType = DirectX::XMFLOAT3;
using VertexUVType       = DirectX::XMFLOAT2;
using VertexNormalType   = DirectX::XMFLOAT3;
///
/// @class  VertexData
/// @brief  頂点データ
///
class VertexData
{
public :
    ~VertexData()
    {
        for( auto& buffer : vertex_buffers_ )
            buffer.second->Release();
        index_buffer_->Release();
    }

    void setVertexBuffer( const char* Semantic, ID3D11Buffer* Buffer ) { Buffer->AddRef(); vertex_buffers_[Semantic] = Buffer; }
    void setIndexBuffer( ID3D11Buffer* Buffer ) { Buffer->AddRef(); index_buffer_ = Buffer; }
    ID3D11Buffer* getVertexBuffer( const char* Semantic )
    {
        auto buffer_itr = vertex_buffers_.find( Semantic );
        if( buffer_itr == vertex_buffers_.end() ) return nullptr;
        
        buffer_itr->second->AddRef();
        return buffer_itr->second;
    }
    ID3D11Buffer* getIndexBuffer() noexcept
    {
        index_buffer_->AddRef();
        return index_buffer_;
    }

private :
    std::unordered_map<const char*, ID3D11Buffer*> vertex_buffers_;
    ID3D11Buffer* index_buffer_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_DATA_HEADER_
/// EOF
