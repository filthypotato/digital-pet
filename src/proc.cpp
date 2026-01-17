// proc.cpp
// Implementation of system monitoring functions
#include "proc.hpp"
#include "Pet.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <sys/statvfs.h>


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
       >> cpuOut.steal;       // Stolen time (VMs)

    return true;  // Successfully read all values
}

unsigned long totalJiffies(const CpuTimes& c) {
    return c.user
         + c.nice
         + c.system
         + c.idle
         + c.iowait
         + c.steal;
}

unsigned long idleJiffies(const CpuTimes& c) {
    return c.idle + c.iowait;
}

// Function that calculate CPU percentage from two CpuTimes readings
int calcCpuPercent(const CpuTimes& prev, const CpuTimes& curr) {
    unsigned long prevTotal = totalJiffies(prev);
    unsigned long currTotal = totalJiffies(curr);

    unsigned long totalDiff = currTotal - prevTotal;
    unsigned long idleDiff  = idleJiffies(curr) - idleJiffies(prev);

    if (totalDiff == 0) return 0;

    // % busy = 1 - idle
    return (int)(100UL * (totalDiff - idleDiff) / totalDiff);
}



// Reads memory statistics from /proc/meminfo
bool readMemStats(MemInfo& memOut) {

  std::ifstream memProc("/proc/meminfo");
  if (!memProc.is_open()) {
    return false;
  }
  std::string label{};
  unsigned long long value{};
  std::string unit{};

// Looks for MemTotal and MemAvailable to calculate usage percentage
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
  return static_cast<int>(100.00 *
                         (memOut.memTotalKb - memOut.memAvailableKb) / memOut.memTotalKb);
}

// Disk function
bool readDiskInfo(const std::vector<const char*>& paths, DiskInfo& diskOut) {
    if (paths.empty()) {
        return false;
    }

    std::uint64_t totalTotal{};
    std::uint64_t totalAvail{};
    std::uint64_t totalUsed{};
    int successCount{};

    for (const char* path : paths) {
        struct statvfs stat{};

        if (statvfs(path, &stat) != 0) {
            continue; // Skip this path if statvfs fails
        }

        const std::uint64_t total =
            static_cast<std::uint64_t>(stat.f_blocks) * stat.f_frsize;

        const std::uint64_t avail =
            static_cast<std::uint64_t>(stat.f_bavail) * stat.f_frsize;

        const std::uint64_t used = total - avail;

        totalTotal += total;
        totalAvail += avail;
        totalUsed += used;
        successCount++;
    }

    if (successCount == 0) {
        return false; // None of the paths succeeded
    }

    diskOut.totalBytes = totalTotal;
    diskOut.availBytes = totalAvail;
    diskOut.usedBytes = totalUsed;

    diskOut.percentUsed =
        (totalTotal == 0) ? 0 : static_cast<int>((totalUsed * 100) / totalTotal);

    return true;
}

void readHardwareStats(PetState& state) {
  // Read current system stats from /proc/stat
  if (readCpuStats(state.cpuOut)) {
    // reads CPU times
    if (state.hasPrevCpu) {
      state.sMetrics.cpuPet = calcCpuPercent(state.prevCpu, state.cpuOut);
    }
      state.prevCpu = state.cpuOut;
      state.hasPrevCpu = true;
    }

    if (readMemStats(state.memOut)) {
      // Successfully read memory stats and calculates percentage
      state.sMetrics.memPet = calcMemPercent(state.memOut);
    }

    // Add file paths for ones you want to track specifically
    // This is for Linux only for now.
    const std::vector<const char*> diskPaths = {
        "/mnt",
        "/mnt/drive1",
        "/home"
    };

    if (readDiskInfo(diskPaths, state.diskOut)) {
      state.sMetrics.diskPet = state.diskOut.percentUsed;

    if (readUptime(state.uptimeOut)) {
      state.sMetrics.uptimePet = static_cast<int>(state.uptimeOut.uptimeSeconds);
    }
  }
}


bool readUptime(UptimeInfo& uptimeOut) {
  std::ifstream uptimeFile("/proc/uptime");
    if (!uptimeFile.is_open())
      return false;

    double uptimeSecRaw{};
    double idleSecRaw{}; // adding this just in case i want to do something
                      // with idle times later


    // /proc/uptime  <totalUptime>  <idle time>
    if (!(uptimeFile >> uptimeSecRaw >> idleSecRaw))
      return false;

    long uptimeSec = static_cast<long>(uptimeSecRaw);
    // to convers uptimeSec to HH:MM:SS for readability

    uptimeOut.uptimeSeconds = uptimeSec;
    uptimeOut.hours = uptimeSec / 3600;
    uptimeOut.minutes = (uptimeSec % 3600) / 60;
    uptimeOut.seconds = uptimeSec % 60;

    return true;

}


