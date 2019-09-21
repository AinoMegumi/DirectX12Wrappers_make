#pragma once
#include "Factory.hpp"
#include <d3dcommon.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			using HardwareAdapter = COM::ComPtr<IDXGIAdapter1>;
			using WarpAdapter = COM::ComPtr<IDXGIAdapter>;

			struct HardwareAdapterInformation : public DXGI_ADAPTER_DESC1 {
				HardwareAdapterInformation(HardwareAdapter&& AdapterData, const DXGI_ADAPTER_DESC1& desc, const D3D_FEATURE_LEVEL& FeatureLevel)
					: DXGI_ADAPTER_DESC1(std::move(desc)), Adapter(std::move(AdapterData)), SupportedFeatureLevel(FeatureLevel) {}
				HardwareAdapter Adapter;
				D3D_FEATURE_LEVEL SupportedFeatureLevel;
			};

			std::vector<HardwareAdapterInformation> GetHardwareAdapters(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
			WarpAdapter GetWarpAdapter(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
		}
	}
}
