// proc.hpp
// Functions for reading system information from /proc filesystem
#pragma once
#include <cstdint>
#include <string> // for pet.hpp
#include <vector>
// Holds raw CPU time values from /proc/stat
// All values are in "jiffies" (ticks of the system clock)
struct CpuTimes {
    unsigned long long user{};       // Time spent in user mode
    unsigned long long nice{};       // Time spent in user mode with low priority
    unsigned long long system{};     // Time spent in kernel mode
    unsigned long long idle{};       // Time spent idle
    unsigned long long iowait{};     // Time waiting for I/O to complete
    unsigned long long steal{};      // Time stolen from VMs
};

struct MemInfo {
    unsigned long long memTotalKb{};
    unsigned long long memAvailableKb{};
};

struct UptimeInfo {
    double uptimeSeconds{};
    long hours{};
    long minutes{};
    long seconds{};
};

struct DiskInfo {
    std::uint64_t totalBytes{};
    std::uint64_t availBytes{};
    std::uint64_t usedBytes{};
    int percentUsed{};
};


// Simplified system metrics as percentages (0-100)
struct SystemMetrics {
    int cpuPet{};          // CPU usage percentage
    int memPet{};       // Memory usage percentage
    int diskPet{};    // Disk space used percentage
    int uptimePet{}; // System uptime in seconds
};


// Fwd declarations from proc.cpp
bool readCpuStats(CpuTimes& cpuOut);
bool readMemStats(MemInfo& memOut);
bool readUptime(UptimeInfo& uptimeOut);
bool readDiskInfo(const std::vector<const char*>& paths, DiskInfo& diskOut);
bool readUptime(UptimeInfo& uptimeOut);
int calcCpuPercent(const CpuTimes& prev, const CpuTimes& cur);
int calcMemPercent(const MemInfo& memOut);
int calcDiskPercent(const DiskInfo& diskOut);
unsigned long totalJiffies(const CpuTimes& c);
struct PetState;
void readHardwareStats(PetState& state);
