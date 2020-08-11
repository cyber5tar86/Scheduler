#include <iostream>

#include "Scheduler.h"
#include <unistd.h>

void message(const std::string &s) {
  std::cout << s << std::endl;
}

int main() {
  // number of tasks that can run simultaneously
  // Note: not the number of tasks that can be added,
  //       but number of tasks that can be run in parallel
  unsigned int max_n_threads = 12;

  // Make a new scheduling object.
  // Note: s cannot be moved or copied
  Bosma::Scheduler s(max_n_threads);

  // using https://github.com/staticlibs/ccronexpr
  // Note: uses UTC unless compiled with -DCRON_USE_LOCAL_TIME
  // Note: first field is seconds
  // Supports more advanced expressions:
  // expression           current time           next cron time
  // "*/15 * 1-4 * * *",  "2012-07-01_09:53:50", "2012-07-02_01:00:00"
  // "0 */2 1-4 * * *",   "2012-07-01_09:00:00", "2012-07-02_01:00:00"
  // "0 0 7 ? * MON-FRI", "2009-09-26_00:42:55", "2009-09-28_07:00:00"
  // "0 30 23 30 1/3 ?",  "2011-04-30_23:30:00", "2011-07-30_23:30:00"
  s.ccron("*/5 * 0-2 * * *", []() { std::cout << "every 5 seconds between 0:00-2:00 UTC" << std::endl; });

  Bosma::CCronTask cc1("0 30 11 * * *", [](){});
  std::cout << cc1.get_new_time().time_since_epoch().count() << std::endl;
  sleep(10);
  std::cout << cc1.get_new_time().time_since_epoch().count() << std::endl;  
  return 0;
}
