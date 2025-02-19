#include "System/Operator.h"

#include <string>

#include "MultiExtend.h"

#ifdef _WINDOWS
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#else
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#endif

// 静态成员初始化
std::mutex MultiExtend::Operator::instanceMutex;

MultiExtend::Operator::Operator()
{

// GetMacAddress

#ifdef _WINDOWS
	PIP_ADAPTER_ADDRESSES pAddresses = nullptr;
	ULONG outBufLen = 0;

	// 首次获取所需缓冲区大小
	if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
		pAddresses = (PIP_ADAPTER_ADDRESSES)malloc(outBufLen);
		if (pAddresses) {
			if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, pAddresses, &outBufLen) == ERROR_SUCCESS) {
				for (PIP_ADAPTER_ADDRESSES pCurr = pAddresses; pCurr != nullptr; pCurr = pCurr->Next) {
					// 过滤条件：已连接、有物理地址、非回环、非虚拟适配器
					if (pCurr->OperStatus == IfOperStatusUp &&
						pCurr->PhysicalAddressLength == 6 &&
						pCurr->IfType != IF_TYPE_SOFTWARE_LOOPBACK &&
						(pCurr->IfType >= IF_TYPE_ETHERNET_CSMACD &&
							pCurr->IfType <= IF_TYPE_IEEE1394))
					{
						char buffer[18];
						sprintf_s(buffer, "%02X:%02X:%02X:%02X:%02X:%02X",
							pCurr->PhysicalAddress[0], pCurr->PhysicalAddress[1],
							pCurr->PhysicalAddress[2], pCurr->PhysicalAddress[3],
							pCurr->PhysicalAddress[4], pCurr->PhysicalAddress[5]);
						this->m_macAddress = buffer;
						break;
					}
				}
			}
			free(pAddresses);
		}
	}
#else
	// Linux/macOS实现
	DIR* dir = opendir("/sys/class/net/");
	if (dir) {
		struct dirent* entry;
		while ((entry = readdir(dir)) != nullptr) {
			std::string iface = entry->d_name;
			// 排除虚拟接口
			if (iface == "." || iface == ".." ||
				iface.find("lo") != std::string::npos ||
				iface.find("docker") != std::string::npos ||
				iface.find("veth") != std::string::npos)
			{
				continue;
			}

			std::ifstream file("/sys/class/net/" + iface + "/address");
			if (file.good()) {
				std::getline(file, this->m_macAddress);
				if (!this->m_macAddress.empty()) {
					// 转换为大写
					for (auto& c : this->m_macAddress) {
						if (c >= 'a' && c <= 'f') c -= 32;
					}
					break;
				}
			}
		}
		closedir(dir);
	}
#endif
}

MultiExtend::Operator& MultiExtend::Operator::Get() {
	std::lock_guard<std::mutex> lock(instanceMutex);

	static Operator* instance;

	if (!instance) 
	{
		instance = new Operator();
	}
	
	return *instance;
}

MULTIEXTEND_API int MultiExtend::Operator::Init()
{
	MULTIEXTEND_MESSAGE_CLIENT_INFO("Operator Init");
	
	std::string Mac = this->GetMacAddress();
	MULTIEXTEND_MESSAGE_CLIENT_INFO("Mac Address");
	MULTIEXTEND_MESSAGE_CLIENT_INFO("{0}", Mac);

	return 0;
}

std::string MultiExtend::Operator::GetMacAddress() const {
	return m_macAddress;
}