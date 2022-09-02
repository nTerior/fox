#pragma once

#include <ncurses.h>

struct fox_ui
{
  int (*key_callbacks[KEY_MAX])(int);
};

/**
 * @brief Initialize the ui
 *
 * @param ui
 */
struct fox_ui *ui_init();
void ui_cleanup(struct fox_ui *ui);

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

/**
 * @brief Prints a line
 *
 * @param line the line
 * @param format
 * @param ...
 */
void ui_print_line(int line, char *format, ...);

/**
 * @brief Prints a line after clearing it
 *
 * @param line
 * @param format
 * @param ...
 */
void ui_print_clear_line(int line, char *format, ...);

/**
 * @brief Prints a line using va_list
 *
 * @param line the line
 * @param format
 * @param arg
 */
void ui_vprint_line(int line, char *format, va_list arg);

/**
 * @brief Prints a line after clearing it using va_list
 *
 * @param line
 * @param format
 * @param arg
 */
void ui_vprint_clear_line(int line, char *format, va_list arg);