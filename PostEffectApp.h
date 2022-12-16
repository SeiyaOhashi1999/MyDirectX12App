#pragma once
#include "D3D12AppBase.h"
#include <DirectXMath.h>
#include "math/Vector.h"

class PostEffectApp : public D3D12AppBase {
public:
  PostEffectApp();

  virtual void Prepare();
  virtual void Cleanup();

  virtual void Render();
  virtual void OnSizeChanged(UINT width, UINT height, bool isMinimized);

  struct SceneParameter
  {
    DirectX::XMFLOAT4X4 world;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 proj;
  };

  struct DirectionLight
  {
      Vector3 ligDirection;
      float pad1;
      Vector3 ligColor;
      float pad2;
      Vector3 eyePos;
      float pad3;
      Vector3 ligPower;
  };

  struct EffectParameter
  {
    DirectX::XMFLOAT2  screenSize;
    float mosaicBlockSize;

    UINT  frameCount;
    float ripple;
    float speed;      // ó¨ÇÍë¨ìx.
    float distortion; // òcÇ›ã≠ìx
    float brightness; // ñæÇÈÇ≥åWêî
    float monoPower;  // ÉÇÉmÉNÉçåWêî
    float bokeSize;   // É{ÉPÉTÉCÉY
  };
private:
  using Buffer = ComPtr<ID3D12Resource1>;
  using Texture = ComPtr<ID3D12Resource1>;

  void RenderToTexture();
  void RenderToMain();

  void UpdateImGui();
  void RenderImGui();

  void PrepareTeapot();
  void PreparePostEffectPlane();
  void PrepareRenderTextureResource();

  enum {
    InstanceCount = 200,
  };
  enum EffectType
  {
    EFFECT_TYPE_NONE,
    EFFECT_TYPE_MOSAIC,
    EFFECT_TYPE_WATER,
    EFFECT_TYPE_MONOCHROME,
    EFFECT_TYPE_DOFBOKE
  };

  struct InstanceData
  {
    DirectX::XMFLOAT4X4 world;
    DirectX::XMFLOAT4 Color;
  };
  struct InstanceParameter
  {
    InstanceData  data[InstanceCount];
  };

  struct ModelData
  {
    UINT indexCount;
    D3D12_VERTEX_BUFFER_VIEW vbView;
    D3D12_INDEX_BUFFER_VIEW  ibView;
    Buffer resourceVB;
    Buffer resourceIB;

    ComPtr<ID3D12RootSignature> rootSig;
    ComPtr<ID3D12PipelineState> pipeline;
    std::vector<Buffer> sceneCB;
    std::vector<Buffer> instanceCB;
    std::vector<Buffer> lightCB;
  };
  struct PlaneData
  {
    UINT vertexCount;
    D3D12_VERTEX_BUFFER_VIEW vbView;
    Buffer resourceVB;
  };

  Texture m_colorRT;
  Texture m_depthRT;
  DescriptorHandle m_hColorRTV;
  DescriptorHandle m_hDepthDSV;
  DescriptorHandle m_hColorSRV;
  DescriptorHandle m_hDepthSRV;

  ModelData m_model;
  PlaneData m_postEffect;

  UINT m_frameCount;

  EffectParameter m_effectParameter;
  std::vector<Buffer> m_effectCB;

  EffectType m_effectType;
  ComPtr<ID3D12RootSignature> m_effectRS;
  ComPtr<ID3D12PipelineState> m_nonePSO, m_mosaicPSO, m_waterPSO, m_monochromePSO,m_dofbokePSO;

  float m_cameraXOffset;
  float m_cameraYOffset;
  float m_cameraZOffset;
  float m_cameraFoV;

  float ligX;
  float ligY;
  float ligZ;

  float DiffPow;
  float SpecPow;
  float AmbiPow;
};