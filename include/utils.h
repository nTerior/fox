#pragma once

/**
 * @brief checks if a string is a number
 *
 * @param str
 * @return int
 */
int is_number(char *str);

/**
 * @brief returns the smaller value
 *
 * @param a
 * @param b
 * @return long
 */
long min(long a, long b);

/**
 * @brief returns the larger value
 *
 * @param a
 * @param b
 * @return long
 */
long max(long a, long b);

/**
 * @brief Get either a printable ascii char or `.`
 *
 * @param c
 * @return char
 */
char get_printable_char(char c);