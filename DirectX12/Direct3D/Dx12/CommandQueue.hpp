#pragma once
#include "Device.hpp"

namespace meigetsusoft {
	namespace DirectX {
		namespace Dx12 {
			class CommandQueue : public COM::ComPtr<ID3D12CommandQueue> {
			public:
				CommandQueue(const Device& Dx12Device);
				CommandQueue(const Device& Dx12Device, const D3D12_COMMAND_QUEUE_DESC& CmdQueueDesc);
			};
		}
	}
}
