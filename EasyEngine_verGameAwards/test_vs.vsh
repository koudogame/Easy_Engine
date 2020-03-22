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
    float4 world = mul( float4(Position, 1.0F), World );
    float4 view  = mul( world, View );
    float4 projection = mul( view, Projection );

    Output output;
    output.position = view;
    output.z = Position.z;

    return output;
}
