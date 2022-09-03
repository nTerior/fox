#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *run_timer(void *arg)
{
  struct timer *timer = (struct timer *)arg;
  clock_t goal = timer->delay_ms * CLOCKS_PER_SEC / 1000 + clock();
  while (goal > clock())
    ;

  (*timer->callback)();
  free(timer);
  return 0;
}

void add_timer(unsigned long delay_ms, void (*callback)(void))
{
  struct timer *timer = malloc(sizeof(struct timer));
  timer->callback = callback;
  timer->delay_ms = delay_ms;

  pthread_t tid;
  pthread_create(&tid, NULL, run_timer, (void *)timer);
  pthread_detach(tid);
}