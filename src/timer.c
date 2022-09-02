#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *run_timer(void *arg)
{
  struct timer *timer = (struct timer *)arg;

  clock_t c0 = clock();
  double delta_ms = 0;
  while (delta_ms < timer->delay_ms)
  {
    clock_t c1 = clock();
    delta_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
  }

  (*timer->callback)();
  free(timer);
  return 0;
}

void add_timer(double delay_ms, void (*callback)(void))
{
  struct timer *timer = malloc(sizeof(struct timer));
  timer->callback = callback;
  timer->delay_ms = delay_ms;

  pthread_t tid;
  pthread_create(&tid, NULL, run_timer, (void *)timer);
  pthread_detach(tid);
}