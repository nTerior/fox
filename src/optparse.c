#include "optparse.h"

#include "utils.h"
#include "io.h"

#include <string.h>
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
      "Keyboard interactions:\n"
      " - q: Quit\n"
      "\n"
      "This software is being developed at https://github.com/nTerior/fox\n"
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
      int res = file_exists(optarg);
      if (res == IO_DIRECTORY)
      {
        fprintf(stderr, "%s is not a file!\n", optarg);
        exit(1);
        return;
      }
      else if (res == IO_FAIL)
      {
        fprintf(stderr, "The file %s does not exist!\n", optarg);
        exit(1);
        return;
      }
      opt->filename = malloc(strlen(optarg));
      strcpy(opt->filename, optarg);
      break;

    case 'b':
      if (!is_number(optarg))
      {
        fprintf(stderr, "The passed buffer size is not a number!\n");
        exit(1);
        return;
      }

      opt->buffer_size = atol(optarg);

      if (opt->buffer_size <= 0)
      {
        fprintf(stderr, "The buffer has to be at least size 1!\n");
        exit(1);
        return;
      }
      break;

    default:
      break;
    }
  }
}