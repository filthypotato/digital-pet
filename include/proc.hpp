// proc.hpp
// Functions for reading system information from /proc filesystem
#pragma once
#include <cstdint>

// Holds raw CPU time values from /proc/stat
// All values are in "jiffies" (ticks of the system clock)
struct CpuTimes {
    unsigned long long user{};       // Time spent in user mode
    unsigned long long nice{};       // Time spent in user mode with low priority
    unsigned long long system{};     // Time spent in kernel mode
    unsigned long long idle{};       // Time spent idle
    unsigned long long iowait{};     // Time waiting for I/O to complete
    unsigned long long irq{};        // Time servicing interrupts
    unsigned long long softirq{};    // Time servicing soft interrupts
    unsigned long long steal{};      // Time spent in other OS (virtual machines)
    unsigned long long guest{};      // Time spent running a guest OS
    unsigned long long guestNice{};  // Time spent running a low priority guest
};

struct MemInfo {
  unsigned long long memTotalKb{};
  unsigned long long memAvailableKb{};
};

struct UptimeInfo {
  double uptimeSeconds{};
};

struct DiskInfo {
  std::uint64_t totalBytes{};
  std::uint64_t freeBytes{};
};


// Simplified system metrics as percentages (0-100)
struct SystemMetrics {
    int cpuPet{};          // CPU usage percentage
    int memPet{};       // Memory usage percentage
    int diskPet{};    // Disk space used percentage
    int uptimeSeconds{}; // System uptime in seconds
};

// Fwd declarations

bool readCpuStats(CpuTimes& cpuOut);
bool readMemStats(MemInfo& memOut);
bool readUptime(UptimeInfo& uptimeOut);
bool readDiskInfo(const char *path, DiskInfo& diskOut);

// TODO: Add function to calculate CPU percentage from two CpuTimes readings
int calcCpuPercent(const CpuTimes& prev, const CpuTimes& cur);

// Implemented calcMemPercent()
int calcMemPercent(const MemInfo& memOut);

// TODO: Implement calcDiskPercent()
int calcDiskPercent(const DiskInfo& diskOut);

// TODO: Implement readDiskInfo() using statvfs
// TODO: Implement readUptime() to read from /proc/uptime
