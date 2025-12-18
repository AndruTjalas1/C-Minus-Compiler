# Installation Guide

Complete setup instructions for building and running the c-minus-compiler.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Linux/macOS](#linuxmacos)
- [Windows](#windows)
- [Verification](#verification)
- [Troubleshooting](#troubleshooting)

---

## Prerequisites

The compiler requires three key tools:

| Tool | Purpose | Version |
|------|---------|---------|
| **GCC** | C compiler | 7.0+ |
| **Flex** | Lexer generator | 2.6+ |
| **Bison** | Parser generator | 3.0+ |
| **SPIM** | MIPS simulator (optional) | Any |

### Purpose of Each Tool

- **GCC:** Compiles the compiler itself (written in C)
- **Flex:** Generates the lexical analyzer from `lexer.l`
- **Bison:** Generates the parser from `parser.y`
- **SPIM:** Runs the generated MIPS assembly output (optional but recommended)

---

## Linux/macOS

### Ubuntu/Debian

#### Install Prerequisites
```bash
sudo apt-get update
sudo apt-get install build-essential flex bison
```

This installs:
- `build-essential` (includes GCC and Make)
- `flex` (lexer generator)
- `bison` (parser generator)

#### Optional: Install SPIM
```bash
sudo apt-get install spim
```

#### Verify Installation
```bash
gcc --version
flex --version
bison --version
spim -v
```

### macOS (Homebrew)

#### Install Prerequisites
```bash
brew install gcc flex bison
```

#### Optional: Install SPIM
```bash
brew install spim
```

#### Verify Installation
```bash
gcc --version
flex --version
bison --version
spim -v
```

### Build the Compiler
```bash
cd /path/to/c-minus-compiler
make clean
make
```

Expected output:
```
flex lexer.l
bison parser.y
gcc -g -Wall -c main.c
gcc -g -Wall -c AST.c
...
gcc -g -Wall -o Compiler lex.yy.o parser.tab.o main.o ...
```

---

## Windows

### Option 1: MinGW with MSYS2 (Recommended)

#### Step 1: Install MSYS2
1. Download MSYS2 from [msys2.org](https://www.msys2.org/)
2. Run the installer and follow prompts
3. Launch **MSYS2 MinGW 64-bit** terminal

#### Step 2: Install Tools
```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S flex
pacman -S bison
pacman -S mingw-w64-x86_64-make
```

If prompted, press `Y` to proceed with installations.

#### Step 3: Verify Installation
```bash
gcc --version
flex --version
bison --version
make --version
```

#### Step 4: Install SPIM (Optional)
```bash
pacman -S mingw-w64-x86_64-spim
```

#### Step 5: Build the Compiler
```bash
cd /path/to/c-minus-compiler
make clean
make
```

### Option 2: Cygwin

#### Step 1: Install Cygwin
1. Download setup from [cygwin.com](https://www.cygwin.com/)
2. Run `setup-x86_64.exe`
3. Select packages during installation

#### Step 2: Select Required Packages
During installation, search for and select:
- `gcc-core` (C compiler)
- `flex` (lexer generator)
- `bison` (parser generator)
- `make` (build tool)

#### Step 3: Verify and Build
```bash
gcc --version
flex --version
bison --version
cd /cygdrive/c/path/to/c-minus-compiler
make
```

### Option 3: Windows Subsystem for Linux (WSL2)

#### Step 1: Install WSL2
Follow Microsoft's [WSL installation guide](https://docs.microsoft.com/en-us/windows/wsl/install)

#### Step 2: Inside WSL2 Ubuntu
```bash
sudo apt-get update
sudo apt-get install build-essential flex bison
```

#### Step 3: Navigate and Build
```bash
cd /mnt/c/path/to/c-minus-compiler
make
```

---

## Verification

### Test Basic Build
```bash
make clean
make
./Compiler --help
```

Expected: Shows usage information or error (compiler may not have --help)

### Run Included Test
```bash
# Create a simple test file
echo "int x = 5; int y = 3; write(x + y);" > test_simple.c

# Compile it
./Compiler test_simple.c output.s

# Verify output was generated
ls -la output.s
```

### Execute Output with SPIM
```bash
spim -file output.s
```

Expected output: `8` (5 + 3)

### Full Test Suite
```bash
make test
```

Runs all included test files.

---

## Troubleshooting

### Error: "flex: command not found"

**Solution:** Flex is not installed or not in PATH

```bash
# Ubuntu/Debian
sudo apt-get install flex

# macOS
brew install flex

# Windows (MSYS2)
pacman -S flex
```

### Error: "bison: command not found"

**Solution:** Bison is not installed or not in PATH

```bash
# Ubuntu/Debian
sudo apt-get install bison

# macOS
brew install bison

# Windows (MSYS2)
pacman -S bison
```

### Error: "make: command not found"

**Solution:** Make is not installed

```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
brew install make

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-make
```

### Error: "gcc: command not found"

**Solution:** GCC is not installed

```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
brew install gcc

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-gcc
```

### Error During Make: "parser.tab.h: No such file or directory"

**Solution:** Bison didn't run properly. Try:

```bash
make clean
make
```

Or explicitly generate parser:
```bash
bison -d parser.y
```

### Warning: "'main' redefined" or Similar Linker Errors

**Solution:** Files in `obj/` directory may be stale

```bash
make clean
rm -rf obj/
make
```

### Executable Works But Can't Find SPIM

**Solution:** SPIM is not installed (it's optional)

```bash
# Ubuntu/Debian
sudo apt-get install spim

# macOS
brew install spim

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-spim
```

Alternatively, use online SPIM simulator or alternative MIPS simulator.

### MIPS Assembly Generation Works but SPIM Won't Run It

**Possible issues:**

1. **Wrong SPIM version:** Try with a different MIPS simulator
2. **File permission:** Ensure output file is readable
3. **Invalid MIPS:** Check if compiler generated valid MIPS (check output.s)

**Debug steps:**
```bash
# View generated assembly
cat output.s

# Try with verbose SPIM
spim -file output.s -dump
```

### Windows Path Issues (MSYS2/Cygwin)

If you get errors about file paths not found:

```bash
# MSYS2: Use forward slashes
./Compiler /c/Users/Username/file.c output.s

# Or convert path to MSYS2 format
cd /c/path/to/project
./Compiler file.c output.s

# Cygwin: Use /cygdrive prefix
cd /cygdrive/c/path/to/project
./Compiler file.c output.s
```

---

## System-Specific Notes

### Linux
- Most straightforward installation via package managers
- GCC typically pre-installed
- SPIM available in most repositories

### macOS
- Homebrew makes installation simple
- May need Xcode command-line tools: `xcode-select --install`
- Consider creating an alias: `alias spim='/usr/local/bin/spim'`

### Windows
- MSYS2 recommended for best compatibility
- WSL2 provides full Linux environment if preferred
- SPIM support may be limited; consider online simulators as fallback

---

## Advanced Configuration

### Custom Build Flags

Edit `Makefile` to customize compiler flags:

```makefile
# For optimization
CFLAGS = -g -Wall -O2

# For maximum debugging info
CFLAGS = -g -Wall -O0 -DDEBUG

# For smaller binary
CFLAGS = -Wall -s
```

### Custom Output Directory

To generate object files in a specific directory, modify the Makefile:

```makefile
OBJDIR = obj/
OBJS = $(OBJDIR)lex.yy.o $(OBJDIR)parser.tab.o ...
```

---

## Verification Checklist

- [ ] GCC installed and in PATH
- [ ] Flex installed and in PATH
- [ ] Bison installed and in PATH
- [ ] Make works (`make --version`)
- [ ] `make clean` succeeds
- [ ] `make` succeeds and generates `Compiler` executable
- [ ] `./Compiler test.c output.s` works
- [ ] `output.s` file is generated
- [ ] SPIM installed (optional)
- [ ] `spim -file output.s` runs generated code (if SPIM available)

---

## Next Steps

Once installed, check out:
- [README.md](README.md) - Project overview and examples
- [ARCHITECTURE.md](ARCHITECTURE.md) - Technical architecture
- [Usage guide](README.md#usage) - How to compile your code

Happy compiling! 🚀

