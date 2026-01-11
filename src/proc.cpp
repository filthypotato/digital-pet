// proc.cpp
// Implementation of system monitoring functions
#include "proc.hpp"
#include <fstream>
#include <sstream>
#include <string>

// Read CPU usage statistics from /proc/stat
// The first line of /proc/stat contains aggregate CPU times
bool readCpuStats(CpuTimes& cpuOut) {
    // Try to open /proc/stat
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        return false;  // Failed to open file
    }

    // Read the first line (starts with "cpu")
    std::string line{};
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


// Reads memory statistics from /proc/meminfo
// Looks for MemTotal and MemAvailable to calculate usage percentage
bool readMemStats(MemInfo& memOut) {

  std::ifstream memProc("/proc/meminfo");
  if (!memProc.is_open()) {
    return false;
  }
  std::string label{};
  unsigned long long value{};
  std::string unit{};

  while (memProc >> label >> value >> unit) {
    if (label == "MemTotal:") {
      memOut.memTotalKb = value;
    } else if (label == "MemAvailable:") {
      memOut.memAvailableKb = value;
    }
  }

  return true;
}

// Calculates memory usage percentage
int calcMemPercent(const MemInfo& memOut) {
  if (memOut.memTotalKb == 0) return 0;
  return static_cast<int>(
      100.00 * (memOut.memTotalKb - memOut.memAvailableKb) / memOut.memTotalKb
  );
}



// TODO: Write function to read disk space using statvfs() system call
//       Example: statvfs("/", &stat) to get root filesystem info
//       Calculate: used = (total - free) / total * 100

// TODO: Write function to read uptime from /proc/uptime
//       First number is total uptime in seconds
//       Parse it and store in UptimeInfo struct
