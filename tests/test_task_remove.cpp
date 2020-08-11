#include <iostream>

#include "Scheduler.h"
#include <unistd.h>
#include <chrono>

int main() {
  // number of tasks that can run simultaneously
  // Note: not the number of tasks that can be added,
  //       but number of tasks that can be run in parallel
  unsigned int max_n_threads = 12;

  // Make a new scheduling object.
  // Note: s cannot be moved or copied
  Bosma::Scheduler s(max_n_threads);

  auto f = [](std::string const& t){
	       std::cout << std::chrono::system_clock::now().time_since_epoch().count() << '\t' << t << std::endl;
	       return;
	   };
  s.ccron("*/5 * * * * *", f, 1, "task 1");
  s.ccron("*/5 * * * * *", f, 2, "task 2");
  s.ccron("*/5 * * * * *", f, 3, "task 3");
  sleep(20);
  std::cout << "remove task 2" << std::endl;
  s.remove_task(2);
  sleep(20);
  std::cout << "readd task 2" << std::endl;
  s.ccron("*/5 * * * * *", f, 2, "task 2");
  sleep(20);
  return 0;
}
