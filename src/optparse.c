#include "optparse.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_help(char *name)
{
  printf(
      "Usage: %s [options]\n"
      "Options:\n"
      "    -h, --help           prints this message\n"
      "    -f, --file <PATH>    PATH to the to be edited file\n"
      "    -b, --buffer <SIZE>  if no file is being specified, the created file will be SIZE bytes large\n"
      "\n"
      "With no file specified, a new 1KiB (1024 bytes) large, zeroed file will be created,\n"
      "unless specified otherwise.\n"
      "\n"
      "This software is being developed at https://github.com/nTerior/fox"
      "License: MIT License\n",
      name);
}

void parse_opts(int argc, char **argv, struct fox_options *opt)
{
  opt->filename = 0;
  opt->buffer_size = 1024;

  struct option options[] = {
      {"help", no_argument, 0, 'h'},
      {"file", required_argument, 0, 'f'},
      {"buffer", required_argument, 0, 'b'},
      {0, 0, 0, 0},
  };

  int current;

  while (1)
  {
    int opt_index = 0;
    current = getopt_long(argc, argv, "hf:b:", options, &opt_index);

    if (current == -1)
      break;

    switch (current)
    {
    case 'h':
      print_help(argv[0]);
      exit(0);
      return;

    case 'f':
      break;

    case 'b':
      break;

    default:
      break;
    }
  }
}