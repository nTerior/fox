#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int file_is_dir(char *path)
{
  DIR *dir = opendir(path);
  if (dir != NULL)
  {
    closedir(dir);
    return IO_DIRECTORY;
  }

  return IO_FAIL;
}

int file_exists(char *path)
{
  int res = access(path, F_OK);
  if (res != 0)
    return IO_FAIL;

  if (file_is_dir(path) == IO_DIRECTORY)
    return IO_DIRECTORY;

  return IO_OK;
}

int can_read(char *path)
{
  int res = access(path, R_OK);
  if (res != 0)
    return IO_FAIL;
  return IO_OK;
}

int can_write(char *path)
{
  int res = access(path, W_OK);
  if (res != 0)
    return IO_FAIL;
  return IO_OK;
}

int read_file(char *path, unsigned char **buffer, unsigned long *buffer_size)
{
  // basic checks
  int res = file_exists(path);
  if (res != IO_OK)
    return res;

  if (!can_read(path))
    return IO_MISSING_PERMS;

  FILE *fp = fopen(path, "rb");
  // get file size
  fseek(fp, 0, SEEK_END);
  *buffer_size = ftell(fp);
  rewind(fp);

  *buffer = (unsigned char *)malloc(*buffer_size);

  // reading the file
  unsigned done = 0;
  do
  {
    size_t x = fread(*buffer + done, 1, *buffer_size - done, fp);
    if (x <= 0)
      break;
    done += x;
  } while (done < *buffer_size);

  fclose(fp);
  return IO_OK;
}

int write_file(char *path, unsigned char *buffer, unsigned long buffer_size)
{
  // basic checks
  int res = file_is_dir(path);
  if (res == IO_DIRECTORY)
    return res;

  if (!can_write(path) && file_exists(path))
    return IO_MISSING_PERMS;

  FILE *fp = fopen(path, "wb+");

  unsigned long done = 0;
  do
  {
    size_t x = fwrite(buffer + done, 1, buffer_size - done, fp);
    if (x <= 0)
      break;
    done += x;
  } while (done < buffer_size);

  fclose(fp);
  return IO_OK;
}