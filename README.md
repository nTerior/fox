# fox

fox is a command line hex-editor

## Usage
```
Usage: ./fox [options]
Options:
    -h, --help           prints this message
    -v, --version        prints the current version of fox
    -f, --file <PATH>    PATH to the to be edited file
    -b, --buffer <SIZE>  if no file is being specified, the created file will be SIZE bytes large

With no file specified, a new 1KiB (1024 bytes) large, zeroed file will be created,
unless specified otherwise.

Keyboard interactions:
 - arrow keys: cursor movement (also possible with mouse clicks)
 - i: insert byte after selected byte
 - del: delete selected byte
 - s: save file
 - q: quit

This software is being developed at https://github.com/nTerior/fox
License: MIT License
```

### Interaction
- cursor movement: `arrow keys` or clicking using your mouse
- inserting a byte: `i`
- deleting a byte: `del`
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

## Planned features

- [ ] Sidebar with additional information
  - [ ] File name
  - [ ] File size
  - [ ] Selected byte as ints/floats (`int8`, `int16`, `int32`, `int64`, `float32`, `float64`) -> signed/unsigned, litte endian, big endian
