struct VSOutput
{
  float4 Position : SV_POSITION;
  float3 Normal : NORMAL;
  float4 Color : COLOR;
};

cbuffer DirectionLightCb : register(b2)
{
	float3 ligDirection;
	float3 ligColor;
	float3 eyePos;
	float3 ligPower;
};

float4 main(VSOutput In) : SV_TARGET
{
	float t = dot(In.Normal, ligDirection);
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	float DiffuseLig = t * ligPower.x;

	float3 refVec = reflect(ligDirection, In.Normal);
	float3 toEyeVec = eyePos - In.Position;
	toEyeVec = normalize(toEyeVec);

	t = dot(refVec, toEyeVec);
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	t = pow(t, ligPower.y);
	float SpecularLig = t;

	float AmbientLig = ligPower.z;

	t = DiffuseLig + SpecularLig + AmbientLig;
	float4 finalColor = (t,t,t,t);
	return finalColor;
}