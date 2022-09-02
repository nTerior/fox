#pragma once

#include <ncurses.h>

struct fox_ui
{
  int (*key_callbacks[KEY_MAX])(int);
  int a[4];
};

/**
 * @brief Initialize the ui
 *
 * @param ui
 */
struct fox_ui *ui_init();

/**
 * @brief Adds a key event callback for each key
 *
 * @param key the key on which the callback is being triggered (e.g. KEY_BACKSPACE)
 * @param callback the callback function: parameters: the pressed key, returns: 0 if the program should end, 1 if the program should continue. Note that executing the callback is not non-blocking
 */
void ui_key_callback(int key, int (*callback)(int), struct fox_ui *ui);

/**
 * @brief Beings the loop of the ui
 *
 * @param ui
 */
void ui_loop(struct fox_ui *ui);