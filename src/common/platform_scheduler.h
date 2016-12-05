#pragma once
#include <thread>
#include <vector>

namespace platform
{

void
getCpuCoreMap(std::vector<int> &map);

void
setThreadCpuMask(std::thread *thread, uint64_t cpuMask);

} // namespace platform
