struct VSOutput
{
	float4 Position : SV_POSITION;
	float2 UV : TEXCOORD0;
};

cbuffer EffectParameter : register(b0)
{
	float2 windowSize;
	float  blockSize;
	uint   frameCount;
	float  ripple;
	float  speed;
	float  distortion;
	float  brightness;
	float  monoPower;
}

SamplerState texSampler : register(s0);
Texture2D renderedTexture : register(t0);


float4 main(VSOutput In) : SV_TARGET
{
	float2 uv = In.UV;
	float4 color = renderedTexture.Sample(texSampler, uv);
	float Y = 0.299 * color.r + 0.587f * color.b + 0.114f * color.g;
	color.rgb = float3(Y, Y, Y) * monoPower;
	return color;
}