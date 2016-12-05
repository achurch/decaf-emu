#ifdef __linux__
#define _GNU_SOURCE 1  // required for pthread_setaffinity_np(); must be 1 (and not empty) due to spdlog bug
#endif

#include "platform.h"
#include "platform_scheduler.h"

#ifdef PLATFORM_POSIX
#include "bitutils.h"
#include "log.h"
#include <cstdlib>
#include <pthread.h>

#ifdef PLATFORM_LINUX
#include <fstream>
#include <sched.h>
#endif

namespace platform
{

void
getCpuCoreMap(std::vector<int> &map)
{
   map.clear();

#ifdef PLATFORM_LINUX

   std::ifstream f("/proc/cpuinfo");

   int currentCpu = -1, coreId = -1;
   for (char buf[1000]; f.getline(buf, sizeof(buf)); ) {

      if (!*buf) {  // blank line
         if (currentCpu >= 0) {
            if (coreId < 0) {
               gLog->error("Missing core ID field for CPU {}", currentCpu);
            } else {
               if (map.size() <= static_cast<size_t>(currentCpu)) {
                  map.resize(currentCpu + 1, -1);
               }
               map[currentCpu] = coreId;
            }
            currentCpu = -1;
            coreId = -1;
         }
         continue;
      }

      char *colon = strchr(buf+1, ':');
      if (!colon) {  // should never happen
         continue;
      }
      char *s;
      for (s = colon - 1; s > buf && (*s == ' ' || *s == '\t'); --s) { }
      s[1] = '\0';
      const char *fieldName = buf;
      const char *valueStr = colon+1 + strspn(colon+1, " \t");
      auto value = static_cast<int>(strtol(valueStr, &s, 10));

      if (strcmp(fieldName, "processor") == 0) {
         if (value < 0 || *s) {
            gLog->error("Invalid processor field in /proc/cpuinfo: {}", valueStr);
            continue;
         }
         currentCpu = value;
      } else if (strcmp(fieldName, "core id") == 0) {
         if (value < 0 || *s) {
            gLog->error("Invalid core ID field in /proc/cpuinfo: {}", valueStr);
            continue;
         }
         coreId = value;
      }

   }

   if (map.empty()) {
      gLog->error("Failed to parse /proc/cpuinfo");
   }

#else  // !PLATFORM_LINUX
   // TODO: not yet implemented for non-Linux
#endif
}

void
setThreadCpuMask(std::thread *thread, uint64_t cpuMask)
{
#ifdef PLATFORM_LINUX

   cpu_set_t cpuSet;
   CPU_ZERO(&cpuSet);

   while (cpuMask) {
      int cpu = ctz64(cpuMask);
      cpuMask ^= UINT64_C(1) << cpu;
      CPU_SET(cpu, &cpuSet);
   }

   pthread_setaffinity_np(thread->native_handle(), sizeof(cpuSet), &cpuSet);

#else  // !PLATFORM_LINUX
   // TODO: not yet implemented for non-Linux
#endif
}

} // namespace platform

#endif
