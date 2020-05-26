Texture2D Texture : register( t0 );

struct InputData
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 main( InputData Input ) : SV_TARGET
{
    uint width, height;
    Texture.GetDimensions( width, height );
    float3 texcoord = float3( Input.uv.x*width, Input.uv.y*height, 0.0F );

    return Texture.Load( texcoord );
}
// EOF
