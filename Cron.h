#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "croncpp.h"

namespace Bosma {
using Clock = std::chrono::system_clock;

inline void add(std::tm &tm, Clock::duration time) {
  auto tp = Clock::from_time_t(std::mktime(&tm));
  auto tp_adjusted = tp + time;
  auto tm_adjusted = Clock::to_time_t(tp_adjusted);
  tm = *std::localtime(&tm_adjusted);
}

class Cron {
 public:
  explicit Cron(const std::string &expression) {
    cronexpr_ = cron::make_cron(expression);
  }

  Clock::time_point cron_to_next(const Clock::time_point from = Clock::now()) const {
    std::time_t now = std::time(0);
    std::time_t next = cron::cron_next(cronexpr_, now);
    return std::chrono::system_clock::from_time_t(next);
  }

  cron::cronexpr cronexpr_;
};
}