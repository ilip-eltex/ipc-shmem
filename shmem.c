#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main() 
{
  char parent_message[] = "hello";  
  char child_message[] = "goodbye"; 

  void* shmem = mmap (NULL, 128, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  memcpy(shmem, parent_message, sizeof(parent_message));

  int pid = fork();

  if (pid == 0) {
    printf("Child read: %s\n", shmem);
    memcpy(shmem, child_message, sizeof(child_message));
    printf("Child wrote: %s\n", shmem);

  } else {
    printf("Parent read: %s\n", shmem);
    sleep(1);
    printf("After 1s, parent read: %s\n", shmem);
  }
	return 0;
}
