#include "Debug.hpp"
#include <dxgi1_4.h>
#include <dxgidebug.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dx12 {
			DWORD EnableDebugController() noexcept {
				DWORD DxgiFactoryFlags = 0;
				MSComPtr<ID3D12Debug> debugController{};
				if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.ReleaseAndGetAddressOf())))) {
					debugController->EnableDebugLayer();
					DxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
					MSComPtr<IDXGIInfoQueue> DxgiInfoQueue{};
					if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(DxgiInfoQueue.ReleaseAndGetAddressOf())))) {
						DxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
						DxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
					}
				}
				else OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
				return DxgiFactoryFlags;
			}
		}
	}
}
