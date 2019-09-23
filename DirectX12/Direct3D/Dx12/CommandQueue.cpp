#include "CommandQueue.hpp"

namespace meigetsusoft {
	namespace DirectX {
		namespace Dx12 {
			D3D12_COMMAND_QUEUE_DESC CreateDefaultCommandQueueDesc() {
				D3D12_COMMAND_QUEUE_DESC desc{};
				desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
				desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
				return desc;
			}

			CommandQueue::CommandQueue(const Device& Dx12Device) 
				: CommandQueue(Dx12Device, CreateDefaultCommandQueueDesc()) {}

			CommandQueue::CommandQueue(const Device& Dx12Device, const D3D12_COMMAND_QUEUE_DESC& CmdQueueDesc) 
				: COM::ComPtr<ID3D12CommandQueue>([&Dx12Device, &CmdQueueDesc](MSComPtr<ID3D12CommandQueue>& CmdQueue) { return Dx12Device->CreateCommandQueue(&CmdQueueDesc, IID_PPV_ARGS(CmdQueue.ReleaseAndGetAddressOf())); }) {}
		}
	}
}
