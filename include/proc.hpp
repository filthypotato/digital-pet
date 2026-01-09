// proc.hpp
#pragma once



struct CpuTimes {
    unsigned long user{},
                  nice{},
                  system{},
                  idle{},
                  iowait{},
                  irq{},
                  softirq{},
                  steal{},
                  guest{},
                  guestNice{};
};


struct SystemMetrics {
  int cpu{}, memory{}, diskSpace{}, currentUptime{};
};


bool readProcStats(CpuTimes& out);
