cbuffer cbNeverChanges : register( b0 )
{
    matrix Projection;
}
cbuffer cbChangesEveryFrame : register( b1 )
{
    matrix View;
}
cbuffer cbChangeEveryObject : register( b2 )
{
    matrix World;
}

struct OutputData
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

OutputData main( float3 Position : POSITION, float2 TexCoord : TEXCOORD )
{
    OutputData output;
    output.position = mul( float4(Position, 1.0F), World );
    output.uv = TexCoord;

    return output;
}
// EOF
