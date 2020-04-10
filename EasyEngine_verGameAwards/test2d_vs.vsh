cbuffer cb : register( b0 )
{
    float4x4 World;
}

struct Output2D
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

Output2D main( float3 Position : POSITION, float2 TexCoord : TEXCOORD )
{
    Output2D output;
    output.position = mul(float4( Position, 1.0F), World);
    output.texcoord = TexCoord;

    return output;
}
