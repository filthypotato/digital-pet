#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include "proc.hpp"



// TODO: Write function to read memory usage from /proc/meminfo
// TODO: Write function to read disk space (use statvfs or df command)
// TODO: Write function to read uptime from /proc/uptime


// function to read CPU usage from /proc/stat

bool readProcStats(CpuTimes& cpuOut) {
    std::ifstream file("/proc/stat");
    if (!file.is_open()) return false;

    std::string line;
    if (!std::getline(file, line)) return false;

    std::stringstream ss(line);
    std::string cpuLabel;

    ss >> cpuLabel
       >> cpuOut.user
       >> cpuOut.nice
       >> cpuOut.system
       >> cpuOut.idle
       >> cpuOut.iowait
       >> cpuOut.irq
       >> cpuOut.softirq
       >> cpuOut.steal
       >> cpuOut.guest
       >> cpuOut.guestNice;

// TODO PHASE 1: Read system stats and update pet needs
        if (readProcStats(cpuOut)) {
          move(1, 0);
          clrtoeol();
          mvprintw(1, 2,
              "CPU user:%lu System:%lu Idle:%lu",
              cpuOut.user, cpuOut.system, cpuOut.idle);

}
    return true;
}

