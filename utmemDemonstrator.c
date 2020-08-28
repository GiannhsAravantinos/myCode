#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


#include "tmem.h"

#define SP1 ("*******")
#define SP2 ("***********")

int main (){

  int ret = 0;

  printf("%sHi, I will demonstrate how utmem works.%s\n",SP1,SP2);

  int pid=getpid();
  int number=1000001;

  printf("My pid is %d\n",pid);
  printf("PUT: key:%d value:%d\n",pid,number);

  int fd=open(TMEM_PATH,O_WRONLY);
  printf("%sOpened %s %d %s\n",SP1,TMEM_PATH,fd,SP2);

  void *key=&pid;
  size_t key_len=sizeof(pid);
  void *value=&number;
  size_t value_len=sizeof(value);
  long flags=0;

  struct tmem_put_request tmem_put_request = {
      .key = key,
      .key_len = key_len,
      .value = value,
      .value_len = value_len,
  };

  struct tmem_request tmem_request1 = {
    .put = tmem_put_request,
    .flags = flags,
  };

  printf("%sWill now make a PUT request%s\n",SP1,SP2);
  ret = ioctl(fd, TMEM_PUT, &tmem_request1);
  if (ret){printf("ERROR! %d\n",ret);return 0;}

  size_t a=101;
  size_t *value_lenp=&a;
  struct tmem_get_request tmem_get_request = {
      .key = key,
      .key_len = key_len,
      .value = value,
      .value_lenp = value_lenp,
  };

  struct tmem_request tmem_request2 = {
.get = tmem_get_request,
.flags = flags,
  };

  printf("%sWill now make a GET request%s\n",SP1,SP2);
  ret = ioctl(fd, TMEM_GET, &tmem_request2);
  if (ret){printf("ERROR! %d\n",ret);return 0;}

  printf("Returned value size: %d\n",(int) *tmem_request2.get.value_lenp);
  printf("Returned value %d\n",* (int*) tmem_request2.get.value);

  close(fd);
  return 0;
}
