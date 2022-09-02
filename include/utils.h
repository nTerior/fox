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
 * @return unsigned long
 */
unsigned long min(unsigned long a, unsigned long b);

/**
 * @brief Get either a printable ascii char or `.`
 * 
 * @param c 
 * @return char 
 */
char get_printable_char(char c);