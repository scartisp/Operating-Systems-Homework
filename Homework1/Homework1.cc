// Simion Cartis
#include<iostream>
using std:: cout;
using std:: endl;
#include<vector>
using std:: vector;
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<random>

struct shared { // make a shared struct so all threads have same info to work with
  long global_count= 0;
  int n_threads= 2;
  int sloppiness= 10;
  int work_time= 10;
  int work_iteration= 100;
  bool cpu_bound= false;
  bool do_logging= false;
  vector<int> local_buckets;
  sem_t mutex;
};

struct targs { // make an additional struct so that you can differentiate the index of the buckets
  shared* sh; // for each thread
  int index;
};

void* do_work(void* arg) {
  targs* ta = (targs*) arg;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(.5*ta->sh->work_time, 1.5*ta->sh->work_time);
  for (int i = 0; i < ta->sh->work_iteration; ++i) {
    long increments = dis(gen)*1000000;
    if(ta->sh->cpu_bound) {
      for (long j = 0; j < increments; ++j)//NOT SURE IF THIS AMOUNT OF INCRIMINTATION IS WRONG
        ;//wait
      } else {
        usleep(dis(gen)*1000);// NOT SURE IF THIS AMOUNT OF TIME IS WRONG
      }
      ++ta->sh->local_buckets[ta->index];
    if(ta->sh->local_buckets[ta->index] == ta->sh->sloppiness) {
      sem_wait(&(ta->sh->mutex));
      ta->sh->global_count += ta->sh->local_buckets[ta->index];
      ta->sh->local_buckets[ta->index] = 0;
      sem_post(&(ta->sh->mutex));
    }
  }
  return  nullptr;

}

int main(int argc, char* argv[]) {
  using std:: string;
  using std:: stoi;
  shared sh;

  try {
    if (argc > 1) sh.n_threads = stoi(argv[1]);
    if (argc > 2) sh.sloppiness = stoi(argv[2]);
    if (argc > 3) sh.work_time = stoi(argv[3]);
    if (argc > 4) sh.work_iteration = stoi(argv[4]);
    if (argc > 5 && string(argv[5]) == "true") sh.cpu_bound = true;
    if (argc > 6 && string(argv[6]) == "true") sh.do_logging = true;
  } catch (const std:: exception &e) {
    std::cerr << "invalid arguments. the order should be number of threads, sloppiness, " <<
    "work time,\nwork iterations, cpu bound (true or false), and then logging (true or false)." << endl;
    return 1;
  }

  cout << "starting sloppy counter sim with:\nnumber of threads: " << sh.n_threads;
  cout << "\nsoppiness: " << sh.sloppiness <<"\nwork time (in ms): " << sh.work_time;
  cout << "\nwork iteration (per thread): " << sh.work_iteration << "\nCPU bound: ";
  cout << sh.cpu_bound << "\nlogging: " << sh.do_logging << "\n" << endl;


  sem_init(&sh.mutex,0,1);
  for (int i = 0; i < sh.n_threads; ++i) {
    sh.local_buckets.push_back(0);
  }

  targs all_targs[sh.n_threads];
  // for (int i = 0; i< sh.n_threads; ++i) {
  // }
  
  pthread_t threads[sh.n_threads];
  for (int i = 0; i < sh.n_threads; ++i) {
      all_targs[i].sh=&sh;
      all_targs[i].index = i;
      pthread_create(&threads[i],NULL,do_work,&all_targs[i]);
    }
  
 if (sh.do_logging) {
    cout << "displaying outcome every 1000 milisecond: " << endl;
    for (int i = 0; i < 9; ++i) {
      usleep(1000000);
      cout << "Global count: " << sh.global_count << " local buckets [";
      for (int j = 0; j < sh.n_threads; ++j) {
        cout << sh.local_buckets[j] << (j+1==sh.n_threads? "" : ", ");
      }
      cout << "]" << endl;
    }
  }

  for(int i = 0; i< sh.n_threads; ++i) {
    pthread_join(threads[i],nullptr);
    sh.global_count+= all_targs[i].sh->local_buckets[i];
     all_targs[i].sh->local_buckets[i] = 0; // put anything that remains in the local buckets into
  } // the global count, empty the buckets

    cout << "global count " << sh.global_count << endl;

  return 0;
}