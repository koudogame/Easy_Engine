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

struct Output
{
    float4 position : SV_POSITION;
    float  z : COORD_Z;
};

Output main( float3 Position : POSITION )
{
    matrix transform = mul( World, View );
    transform = mul(transform, Projection);

    Output output;
    output.position = mul( float4(Position, 1.0F), transform);
    output.z = Position.z;

    return output;
}
