# fox

fox is a command line hex-editor

## Usage
```bash
./cedit [options]

# for help message
./cedit --help #or
./cedit -h
```

### Keyboard interaction
- Quit: `q` (Note that `Ctrl + C` won't kill the process)

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
