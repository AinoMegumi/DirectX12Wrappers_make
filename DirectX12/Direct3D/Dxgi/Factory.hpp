#pragma once
#include "../ComPtr.hpp"
#include <dxgi1_4.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			class Factory : public COM::ComPtr<IDXGIFactory4> {
			private:
				DWORD DxgiFactoryFlags;
				unsigned int Options;
			public:
				Factory(const unsigned int flags = 0);
				static constexpr unsigned int AllowTearing = 0x1;
			};
		}
	}
}
