#ifndef lock_server_cache_h
#define lock_server_cache_h

#include <string>


#include <map>
#include "lock_protocol.h"
#include "rpc.h"
#include "lock_server.h"
#include "lock.h"
#include <pthread.h>

using namespace std;

class lock_server_cache {
 private:
  int nacquire;
  pthread_mutex_t server_mutex;
  map<lock_protocol::lockid_t, CacheLock> locks;
 public:
  lock_server_cache();
  lock_protocol::status stat(lock_protocol::lockid_t, int &);
  int acquire(lock_protocol::lockid_t, std::string id, int &);
  int release(lock_protocol::lockid_t, std::string id, int &);
};

#endif