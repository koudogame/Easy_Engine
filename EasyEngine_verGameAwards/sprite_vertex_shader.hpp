///
/// @file   sprite_vertex_shader.hpp
/// @author 板場
///
#ifndef INCLUDED_SPRITE_VERTEX_SHADER_HEADER_
#define INCLUDED_SPRITE_VERTEX_SHADER_HEADER_

#include "vertex_shader.hpp"

///
/// @class  SpriteVertexShader
/// @brief  スプライト用頂点シェーダ―
///
class SpriteVertexShader :
    public EGEG VertexShader
{
public :
    static constexpr D3D11_INPUT_ELEMENT_DESC kInputElementDescs[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            1,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };
    static constexpr const char* kVSFileName = "sprite_vs.cso";

    template <class ShaderType,
        class InputLayoutType>
    SpriteVertexShader( ShaderType&& VS, InputLayoutType&& IL ) :
        VertexShader( std::forward<ShaderType>(VS), std::forward<InputLayoutType>(IL) )
    {
    }

    EGEG DetailedResult<EGEG BindedVertexData> bindVertices( const EGEG Vertex& ) const override;
    void setShaderOnPipeline( ID3D11DeviceContext* ) override;
    void setShaderResourcesOnPipeline( ID3D11DeviceContext* ) override;
    void setConstantBuffersOnPipeline( ID3D11DeviceContext* ) override;
    void setSamplersOnPipeline( ID3D11DeviceContext* ) override;
    void setMaterial( const EGEG Material& ) override;
};

#endif /// !INCLUDED_SPRITE_VERTEX_SHADER_HEADER_
/// EOF
