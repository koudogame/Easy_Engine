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
    matrix affine = mul( World, View );
    affine = mul(affine, Projection);

    Output output;
    output.position = mul( float4(Position, 1.0F), affine);
    output.z = Position.z;

    return output;
}
