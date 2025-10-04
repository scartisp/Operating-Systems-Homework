// Simion Cartis
#include<iostream>
using std:: cout;
using std:: endl;
#include<vector>
using std:: vector;
#include<pthread.h>

int main(int argc, char* argv[]) {
  using std:: string;
  using std:: stoi;
  int n_threads = 2;
  int sloppiness = 10;
  int work_time = 10;
  int work_iteration = 100;
  bool cpu_bound = false;
  bool do_logging = false;

  try {
    if (argc > 1) n_threads = stoi(argv[1]);
    if (argc > 2) sloppiness = stoi(argv[2]);
    if (argc > 3) work_time = stoi(argv[3]);
    if (argc > 4) work_iteration = stoi(argv[4]);
    if (argc > 5 && string(argv[5]) == "true") cpu_bound = true;
    if (argc > 6 && string(argv[6]) == "true") do_logging = true;
  } catch (const std:: exception& e) {
    std::cerr << "invalid arguments. the order should be number of threads, sloppiness, " <<
    "work time,\nwork iterations, cpu bound (true or false), and then logging (true or false)." << endl;
    return 1;
  }

  

  return 0;
}