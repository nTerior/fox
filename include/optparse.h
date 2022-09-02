#pragma once

struct fox_options
{
  char *filename;
  int buffer_size;
};

void parse_opts(int argc, char **argv, struct fox_options *opt);