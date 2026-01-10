// proc.cpp
// Implementation of system monitoring functions
#include "proc.hpp"
#include <fstream>
#include <sstream>
#include <string>

// Read CPU usage statistics from /proc/stat
// The first line of /proc/stat contains aggregate CPU times
bool readProcStats(CpuTimes& cpuOut) {
    // Try to open /proc/stat
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        return false;  // Failed to open file
    }

    // Read the first line (starts with "cpu")
    std::string line;
    if (!std::getline(file, line)) {
        return false;  // Failed to read line
    }

    // Parse the line into individual values
    std::stringstream ss(line);
    std::string cpuLabel;  // This will be "cpu"

    // Read all the CPU time values in order
    ss >> cpuLabel           // "cpu" label
       >> cpuOut.user        // User mode time
       >> cpuOut.nice        // Nice user mode time
       >> cpuOut.system      // System mode time
       >> cpuOut.idle        // Idle time
       >> cpuOut.iowait      // I/O wait time
       >> cpuOut.irq         // Hardware interrupt time
       >> cpuOut.softirq     // Software interrupt time
       >> cpuOut.steal       // Stolen time (VMs)
       >> cpuOut.guest       // Guest OS time
       >> cpuOut.guestNice;  // Nice guest OS time

    return true;  // Successfully read all values
}


// TODO: Write function to calculate CPU percentage
//       Hint: Take two CpuTimes readings, compare the differences
//       Formula: 100 * (total_diff - idle_diff) / total_diff

// TODO: Write function to read memory from /proc/meminfo
//       Look for MemTotal and MemAvailable lines
//       Calculate percentage used

// TODO: Write function to read disk space
//       You can use statvfs() system call or parse df command output

// TODO: Write function to read uptime from /proc/uptime
//       First number is total uptime in seconds
