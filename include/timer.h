#pragma once

#include <time.h>

struct timer
{
  unsigned long delay_ms;
  void (*callback)(void);
};

/**
 * @brief Adds a timer to run the callback after delay_ms usecs. Runs in separate thread.
 *
 * @param delay_ms
 * @param callback
 */
void add_timer(unsigned long delay_ms, void (*callback)(void));