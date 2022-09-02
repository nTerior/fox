#pragma once

#define IO_NO_FILE -3
#define IO_DIRECTORY -2
#define IO_MISSING_PERMS -1
#define IO_FAIL 0
#define IO_OK 1

/**
 * @brief checks if a path leads to a directory
 *
 * @param path
 * @return IO_DIRECTOY on success, IO_FAIL on fail
 */
int file_is_dir(char *path);

/**
 * @brief checks if a file exists or is a directory
 *
 * @param path to the file
 * @return IO_DIRECTORY on directory, IO_OK on success, IO_FAIL on fail
 */
int file_exists(char *path);

/**
 * @brief checks if the user has permissions to read the file. DOES NOT CHECK IF THE FILE EXISTS!
 *
 * @param path to the file
 * @return IO_OK on success, IO_FAIL on fail
 */
int can_read(char *path);

/**
 * @brief checks if the user has permissions to write to the file. DOES NOT CHECK IF THE FILE EXISTS!
 *
 * @param path to the file
 * @return IO_OK on success, IO_FAIL on fail
 */
int can_write(char *path);

/**
 * @brief Reads the given file
 *
 * @param path to the file
 * @param buffer pointer to the buffer, no initialisation needed. free() upon disposal
 * @param buffer_size pointer to the buffer size, no initialisation needed.
 * @return IO_OK on success, IO_DIRECTORY on file is actually a directory, IO_MISSING_PERMS on missing permissions
 */
int read_file(char *path, unsigned char **buffer, unsigned long *buffer_size);

/**
 * @brief Writes to the given file
 *
 * @param path to the file
 * @param buffer the buffer
 * @param buffer_size the buffer size
 * @return IO_OK on success, IO_DIRECTORY on file is actually a directory, IO_MISSING_PERMS on missing permissions
 */
int write_file(char *path, unsigned char *buffer, unsigned long buffer_size);