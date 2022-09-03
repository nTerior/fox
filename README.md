# fox

fox is a command line hex-editor

## Usage
```
Usage: fox [options]
Options:
    -h, --help           printsw this message
    -v, --version        prints the current version of fox
    -f, --file <PATH>    PATH to the to be edited file
    -b, --buffer <SIZE>  if no file is being specified, the created file will be SIZE bytes large

With no file specified, a new 1KiB (1024 bytes) large, zeroed file will be created,
unless specified otherwise.

Keyboard interactions:
 - arrow keys: cursor movement (also possible with mouse clicks)
 - s: save file
 - q: quit

This software is being developed at https://github.com/nTerior/fox
License: MIT License
```

### Interaction
- cursor movement: `arrow keys` or clicking using your mouse
- saving: `s`
- quitting: `q` (Note that `Ctrl + C` won't kill the process)

## Installation

### Requirements

Libraries:
```
- ncurses
- pthread
```

Build tools:
```
- gcc
- make
```

### Building & Installing

```bash
git clone https://github.com/nTerior/fox
cd fox
make
make install

# to uninstall
make uninstall
```
