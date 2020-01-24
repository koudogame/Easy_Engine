struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD;
    float4 color    : COLOR;
};

VS_OUTPUT vs_main( float4 Position : POSITION,
                   float2 UV       : TEXCOORD,
                   float4 Color    : COLOR )
{
    VS_OUTPUT output;
    
    output.position = Position;
    output.uv = UV;
    output.color = Color;

    return output;
}
