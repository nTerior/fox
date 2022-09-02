#pragma once

struct fox_options
{
  char *filename;
  int buffer_size;
};

/**
 * @brief Parses command line options
 *
 * @param argc argument count
 * @param argv argument vector
 * @param opt pointer to options struct
 */
void parse_opts(int argc, char **argv, struct fox_options *opt);