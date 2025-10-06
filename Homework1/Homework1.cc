// Simion Cartis
#include<iostream>
using std:: cout;
using std:: endl;
#include<vector>
using std:: vector;
#include<pthread.h>
#include<semaphore.h>

struct shared { // make a shared struct so that you can pass in all of these values
  long global_count= 0; // to the pthread_create()
  int n_threads= 2;
  int sloppiness= 10;
  int work_time= 10;
  int work_iteration= 100;
  bool cpu_bound= false;
  bool do_logging= false;
  vector<int> local_buckets;
  sem_t mutex;
};

void* do_work(void* arg) {
  shared* sh = (shared*) arg;
  //continue code here
}

int main(int argc, char* argv[]) {
  shared sh;
  using std:: string;
  using std:: stoi;

  try {
    if (argc > 1) sh.n_threads = stoi(argv[1]);
    if (argc > 2) sh.sloppiness = stoi(argv[2]);
    if (argc > 3) sh.work_time = stoi(argv[3]);
    if (argc > 4) sh.work_iteration = stoi(argv[4]);
    if (argc > 5 && string(argv[5]) == "true") sh.cpu_bound = true;
    if (argc > 6 && string(argv[6]) == "true") sh.do_logging = true;
  } catch (const std:: exception& e) {
    std::cerr << "invalid arguments. the order should be number of threads, sloppiness, " <<
    "work time,\nwork iterations, cpu bound (true or false), and then logging (true or false)." << endl;
    return 1;
  }
  sem_init(&sh.mutex,0,1);

  pthread_t threads[sh.n_threads];
  for (int i = 0; i < sh.n_threads; ++i) {
    sh.local_buckets.push_back(0);
  }

  for(int i = 0; i < work_iteration; ++i) {
    pthread_create(&threads[i],NULL,do_work,&sh);
  }

  return 0;
}