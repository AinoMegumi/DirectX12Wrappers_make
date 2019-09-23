#pragma once
#include <wrl/client.h>
#include <string>
#include <functional>
#include <stdexcept>
template<class C> using MSComPtr = Microsoft::WRL::ComPtr<C>;

namespace meigetsusoft {
	namespace COM {
		template<class C>
		class ComPtr : public MSComPtr<C> {
		public:
			ComPtr() : MSComPtr<C>() {}
			ComPtr(std::nullptr_t) : MSComPtr<C>(nullptr) {}
			ComPtr(C* ptr) : MSComPtr<C>(ptr) {}
			ComPtr(const std::function<HRESULT(MSComPtr<C>&)>& initFunction) {
				if (const HRESULT hr = initFunction(*this); FAILED(hr))
					throw std::runtime_error("Failed to init " + std::string(typeid(C).name()) + "\nErrorCode : " + std::to_string(hr));
			}
			ComPtr(const ComPtr<C>&) = delete;
			ComPtr<C>& operator = (const ComPtr<C>&) = delete;
			ComPtr(ComPtr<C>&& c) : MSComPtr<C>(std::move(c)) { c = nullptr; }
			ComPtr<C>& operator = (ComPtr<C>&& c) { 
				*this = std::move(c);
				c = nullptr;
				return *this;
			}
		};
	}
}