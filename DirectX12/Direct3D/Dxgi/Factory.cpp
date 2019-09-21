#include "Factory.hpp"
#include <dxgi1_5.h>
#ifdef _DEBUG
#include "../Dx12/Debug.hpp"
#endif

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			inline HRESULT CreateFactory(MSComPtr<IDXGIFactory4>& factory, const DWORD& DxgiFactoryFlag, unsigned int& Options) {
				if (const HRESULT hr = CreateDXGIFactory2(DxgiFactoryFlag, IID_PPV_ARGS(factory.ReleaseAndGetAddressOf())); FAILED(hr))
					return hr;
				if (Options & Factory::AllowTearing) {
					BOOL allowTearing = FALSE;
					MSComPtr<IDXGIFactory5> Factory5{};
					HRESULT hr = factory.As(&Factory5);
					if (SUCCEEDED(hr)) hr = Factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
					if (FAILED(hr) || !allowTearing) {
						Options &= ~Factory::AllowTearing;
#ifdef _DEBUG
						OutputDebugStringA("WARNING: Variable refresh rate displays not supported");
#endif
					}
				}
				return S_OK;
			}
#ifdef _DEBUG
			Factory::Factory(const unsigned int flags) 
				: Options(flags), 
				DxgiFactoryFlags(Dx12::EnableDebugController()), 
				COM::ComPtr<IDXGIFactory4>(
					[this](MSComPtr<IDXGIFactory4>& factory) {
						return CreateFactory(factory, this->DxgiFactoryFlags, this->Options);
					}
				) {}
#else
			Factory::Factory(const unsigned int flags) 
				: DxgiFactoryFlags(), 
				COM::ComPtr<IDXGIFactory4>(
					[this](MSComPtr<IDXGIFactory4>& factory) {
						return CreateFactory(factory, this->DxgiFactoryFlags, this->Options);
					}
				) {}
#endif
		}
	}
}
