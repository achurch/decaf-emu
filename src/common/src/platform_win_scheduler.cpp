#include "platform.h"
#include "platform_scheduler.h"

#ifdef PLATFORM_WINDOWS

namespace platform
{

void
getCpuCoreMap(std::vector<int> &map)
{
   map.clear();

   // TODO: not yet implemented
}

void
setThreadCpuMask(std::thread *thread, uint64_t cpuMask)
{
   // TODO: not yet implemented
}

} // namespace platform

#endif
