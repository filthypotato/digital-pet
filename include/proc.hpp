// proc.hpp
// Functions for reading system information from /proc filesystem
#pragma once

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

// Simplified system metrics as percentages (0-100)
struct SystemMetrics {
    int cpu{};          // CPU usage percentage
    int memory{};       // Memory usage percentage
    int diskSpace{};    // Disk space used percentage
    int currentUptime{}; // System uptime in seconds
};

// Read CPU times from /proc/stat
// Returns true if successful, false if file can't be read
bool readProcStats(CpuTimes& cpuOut);


// TODO: Add function to calculate CPU percentage from two CpuTimes readings
// TODO: Add function to read memory from /proc/meminfo
// TODO: Add function to read disk space (maybe using statvfs)
// TODO: Add function to read uptime from /proc/uptime
