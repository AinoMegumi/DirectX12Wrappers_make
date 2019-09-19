#pragma once
#include "../DxBase.hpp"
#include <dxgi1_4.h>

namespace meigetsusoft {
	namespace DirectX {
		namespace Dxgi {
			class Factory : public DxBase<IDXGIFactory4> {
			public:
				Factory();
			};
		}
	}
}
