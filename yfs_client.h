#ifndef yfs_client_h
#define yfs_client_h

#include <string>
//#include "yfs_protocol.h"
#include "extent_client.h"
#include <vector>
#include <sys/stat.h>

#include "lock_protocol.h"
#include "lock_client.h"

class yfs_client {
  extent_client *ec;
  lock_client   *lc;
 public:

  typedef unsigned long long inum;
  enum xxstatus { OK, RPCERR, NOENT, IOERR, EXIST };
  typedef int status;

  struct fileinfo {
    unsigned long long size;
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirinfo {
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirent {
    std::string name;
    yfs_client::inum inum;
  };

 private:
  static std::string filename(inum);
 public:
  static inum n2i(std::string);

  yfs_client(std::string, std::string);

  bool isfile(inum);
  bool isdir(inum);

  int getfile(inum, fileinfo &);
  int getdir(inum, dirinfo &);
  int get(inum, std::string &);
  int put(inum, std::string);
  inum rand_inum(bool isfile = true);
  int create(inum parent, const char * name, bool isfile, unsigned long &);
  bool lookup(inum parent, const char * name, unsigned long &);
  int read(inum ino, size_t size, off_t off, std::string &ret);
  int write(inum ino, const char *buf, size_t size, off_t off);
  int setattr(inum ino, struct stat * attr);
  int unlink(inum parent, const char *name);
  void lock(inum);
  void unlock(inum);
};

class ScopedLockClient {
private:
    lock_client * _lc;
    uint64_t _ino;
public:
    ScopedLockClient(lock_client *lc, uint64_t ino): _lc(lc), _ino(ino) {
        _lc->acquire(_ino);
    }
    ~ScopedLockClient() {
        _lc->release(_ino);
    }
};


#endif 
