#include "Adapter.hpp"
#include <d3d12.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			std::vector<HardwareAdapterInformation> GetHardwareAdaptersAvailableDirect3D12(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel) {
				std::vector<HardwareAdapterInformation> RetArr{};
				HardwareAdapter Adapter{};
				const D3D_FEATURE_LEVEL FeatureLevelList[] = {
					D3D_FEATURE_LEVEL_12_1,
					D3D_FEATURE_LEVEL_12_0,
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0
				};
				for (unsigned int DeviceID = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(DeviceID, Adapter.ReleaseAndGetAddressOf()); DeviceID++) {
					DXGI_ADAPTER_DESC1 desc{};
					Adapter->GetDesc1(&desc);
					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
					if (SUCCEEDED(D3D12CreateDevice(Adapter.Get(), MinFeatureLevel, __uuidof(ID3D12Device), nullptr)))
						RetArr.emplace_back(HardwareAdapterInformation(std::move(Adapter), desc));
				}
				return RetArr;
			}
			
			HardwareAdapterInformation GetFirstHardwareAdapterAvailableDirect3D12(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel) {
				const auto Adapters = GetHardwareAdaptersAvailableDirect3D12(factory, MinFeatureLevel);
				return Adapters.size() == 0 ? nullptr : Adapters.front();
			}

			WarpAdapter GetWarpAdapter(const Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel) {
				WarpAdapter Adapter{};
				factory->EnumWarpAdapter(IID_PPV_ARGS(Adapter.ReleaseAndGetAddressOf()));
				return SUCCEEDED(D3D12CreateDevice(Adapter.Get(), MinFeatureLevel, __uuidof(ID3D12Device), nullptr))
					? Adapter : nullptr;
			}
		}
	}
}
