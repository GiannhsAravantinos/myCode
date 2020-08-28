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

#define SPACES ("***********")

int main (){

  printf("%sHi, I will demonstrate how utmem works.%s",SPACES,SPACES)
  return 0;
}
