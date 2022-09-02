#pragma once

#define IO_NO_FILE -3
#define IO_DIRECTORY -2
#define IO_MISSING_PERMS -1
#define IO_FAIL 0
#define IO_OK 1

int file_is_dir(char *path);
int file_exists(char *path);

int can_read(char *path);
int can_write(char *path);

int read_file(char *path, unsigned char **buffer, unsigned long *buffer_size);
int write_file(char *path, unsigned char *buffer, unsigned long buffer_size);