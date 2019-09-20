#pragma once
#include <wrl/client.h>
#include <string>
#include <functional>
#include <stdexcept>

namespace meigetsusoft {
	namespace DirectX {
		template<class C>
		class DxBase : public Microsoft::WRL::ComPtr<C> {
		public:
			DxBase(const std::function<HRESULT(Microsoft::WRL::ComPtr<C>&)>& initFunction) {
				if (const HRESULT hr = initFunction(*this); FAILED(hr))
					throw std::runtime_error("Failed to init " + std::string(typeid(C).name) + "\nErrorCode : " + std::to_string(hr));
			}
			DxBase(const std::function<void(Microsoft::WRL::ComPtr<C>&)>& initFunction) {
				initFunction(*this);
			}
		};
	}
}