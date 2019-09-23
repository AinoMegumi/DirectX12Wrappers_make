#pragma once
#include "../Dxgi/Adapter.hpp"
#include "d3dx12.h"

namespace meigetsusoft {
	namespace DirectX {
		namespace Dx12 {
			class Device : public COM::ComPtr<ID3D12Device> {
			private:
				D3D_FEATURE_LEVEL FeatureLevel;
			public:
				// Warp Deviceを作成する
				Device(const Dxgi::Factory& factory);
				// Direct3D 12を使用可能な１つ目のGPUを使ってデバイスを作成する
				Device(const Dxgi::Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
				// 選択されたGPUでデバイスを作成する
				Device(const Dxgi::HardwareAdapter& Adapter, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
				D3D_FEATURE_LEVEL GetFeatureLevel() const noexcept { return this->FeatureLevel; }
			};
		}
	}
}
