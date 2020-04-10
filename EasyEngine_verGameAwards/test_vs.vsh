//cbuffer cbNeverChanges : register( b0 )
//{
//    matrix Projection;
//}
//cbuffer cbChangesEveryFrame : register( b0 )
//{
//    float3x3 View;
//    float3 dummy0;
//}
cbuffer cbChangeEveryObject : register( b0 )
{
    float3x3 World;
}

struct Output
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

Output main( float3 Position : POSITION, float2 UV : TEXCOORD )
{
    //matrix transform = mul( World, View );
    //transform = mul(transform, Projection);

    float3x3 wor;
    wor._m00 = 0.1F; wor._m01 = 0.0F; wor._m02 = 0.0F;
    wor._m10 = 0.0F; wor._m11 = 0.35F; wor._m12 = 0.0F;
    wor._m20 = 0.0F; wor._m21 = 0.0F; wor._m22 = 1.0F;
    Output output;
    output.position = float4( mul(Position, World), 1.0F);// mul(float4(Position, 1.0F), World);
    output.uv = UV;
    return output;
}
