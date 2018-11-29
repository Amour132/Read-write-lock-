#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_rwlock_t rwlock;
int book = 0;

void* Read(void* arg)
{
  while(1)
  {
    pthread_rwlock_rdlock(&rwlock);
    cout << "read book :" << book << endl;
    pthread_rwlock_unlock(&rwlock);
    usleep(30000);
  }
}

void* Write(void* arg)
{
  while(1)
  {
    pthread_rwlock_wrlock(&rwlock);
    book++;
    pthread_rwlock_unlock(&rwlock);
    cout << "write book :" << book << endl;
    sleep(2);
  }
}

int main()
{
  pthread_t r,w;
  
  pthread_rwlock_init(&rwlock,NULL);

  pthread_create(&r,NULL,Read,NULL);
  pthread_create(&w,NULL,Write,NULL);

  pthread_join(r,NULL);
  pthread_join(w,NULL);

  pthread_rwlock_destroy(&rwlock);
}
