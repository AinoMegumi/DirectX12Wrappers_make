#pragma once
#include "Factory.hpp"
#include <d3dcommon.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			using HardwareAdapter = MSComPtr<IDXGIAdapter1>;
			using WarpAdapter = MSComPtr<IDXGIAdapter>;

			struct HardwareAdapterInformation : public DXGI_ADAPTER_DESC1 {
				HardwareAdapterInformation() = default;
				HardwareAdapterInformation(std::nullptr_t) : Adapter(nullptr), DXGI_ADAPTER_DESC1() {}
				HardwareAdapterInformation(HardwareAdapter&& AdapterData, const DXGI_ADAPTER_DESC1& desc)
					: DXGI_ADAPTER_DESC1(std::move(desc)), Adapter(std::move(AdapterData)) {}
				HardwareAdapter Adapter;
				bool operator == (std::nullptr_t) const noexcept { return this->Adapter == nullptr; }
				bool operator != (std::nullptr_t) const noexcept { return this->Adapter != nullptr; }
			};

			std::vector<HardwareAdapterInformation> GetHardwareAdaptersAvailableDirect3D12(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
			HardwareAdapterInformation GetFirstHardwareAdapterAvailableDirect3D12(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
			WarpAdapter GetWarpAdapter(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel = D3D_FEATURE_LEVEL_11_0);
		}
	}
}
