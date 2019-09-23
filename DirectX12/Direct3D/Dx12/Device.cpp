#include "Device.hpp"

namespace meigetsusoft {
	namespace DirectX {
		namespace Dx12 {
			inline HRESULT CreateDevice(IUnknown* Adapter, MSComPtr<ID3D12Device>& Dx12Device, const D3D_FEATURE_LEVEL& MinFeatureLevel, D3D_FEATURE_LEVEL& FeatureLevel) {
				if (const HRESULT hr = D3D12CreateDevice(Adapter, MinFeatureLevel, IID_PPV_ARGS(Dx12Device.ReleaseAndGetAddressOf())); FAILED(hr))
					return hr;
#ifdef _DEBUG
				MSComPtr<ID3D12InfoQueue> InfoQueue;
				if (SUCCEEDED(Dx12Device.As(&InfoQueue))) {
					InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
					InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
					std::vector<D3D12_MESSAGE_ID> Hide = {
						D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
						D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE
					};
					D3D12_INFO_QUEUE_FILTER Filter{};
					Filter.DenyList.NumIDs = static_cast<unsigned int>(Hide.size());
					Filter.DenyList.pIDList = Hide.data();
					InfoQueue->AddStorageFilterEntries(&Filter);
				}
#endif
				static const D3D_FEATURE_LEVEL FeatureLevelList[] = {
					D3D_FEATURE_LEVEL_12_1,
					D3D_FEATURE_LEVEL_12_0,
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0
				};
				D3D12_FEATURE_DATA_FEATURE_LEVELS FeatureLevels = { _countof(FeatureLevelList), FeatureLevelList, D3D_FEATURE_LEVEL_11_0 };
				HRESULT hr = Dx12Device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &FeatureLevels, sizeof(FeatureLevels));
				FeatureLevel = SUCCEEDED(hr) ? FeatureLevels.MaxSupportedFeatureLevel : MinFeatureLevel;
			}

			Device::Device(const Dxgi::Factory& factory) 
				: ComPtr<ID3D12Device>([&factory, this](MSComPtr<ID3D12Device>& Dx12Device) { return CreateDevice(Dxgi::GetWarpAdapter(factory).Get(), Dx12Device, D3D_FEATURE_LEVEL_11_0, this->FeatureLevel); }) {}

			Device::Device(const Dxgi::Factory& factory, const D3D_FEATURE_LEVEL& MinFeatureLevel)
				: Device(Dxgi::GetFirstHardwareAdapterAvailableDirect3D12(factory, MinFeatureLevel).Adapter) {}

			Device::Device(const Dxgi::HardwareAdapter& Adapter, const D3D_FEATURE_LEVEL& MinFeatureLevel) 
				: ComPtr<ID3D12Device>([&Adapter, &MinFeatureLevel, this](MSComPtr<ID3D12Device>& Dx12Device) { return CreateDevice(Adapter.Get(), Dx12Device, MinFeatureLevel, this->FeatureLevel); }) {}			
		}
	}
}
