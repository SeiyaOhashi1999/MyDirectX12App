struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 UV : TEXCOORD0;
  //float depth : SV_Target1;
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
	float  bokeSize;
}

SamplerState texSampler : register(s0);
Texture2D renderedTexture : register(t0);
Texture2D depthTexture : register(t1);

float4 main(VSOutput In) : SV_TARGET
{
	float depth = depthTexture.Sample(texSampler, In.UV);

	float4 boke = renderedTexture.Sample(texSampler, In.UV);
	float offsetU = bokeSize / 800.0f;
	float offsetV = bokeSize / 600.0f;
	boke += renderedTexture.Sample(texSampler, In.UV + float2(offsetU, 0.0f));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(0.0f, offsetV));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(-offsetU, 0.0f));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(0.0f, -offsetV));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(offsetU, offsetV));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(-offsetU, offsetV));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(offsetU, -offsetV));
	boke += renderedTexture.Sample(texSampler, In.UV + float2(-offsetU, -offsetV));
	boke /= 9.0f;
	
	boke.a = min(1.0f, (depth - 100.0f) / 500.0f);
	return boke;
}