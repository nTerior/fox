#include "optparse.h"

int main(int argc, char **argv)
{
  struct fox_options options;

  parse_opts(argc, argv, &options);
}