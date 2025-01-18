# README: Testing AVR Cross Compiler with crosstool-ng

This document outlines the steps to build and test an AVR cross-compiler using crosstool-ng and to compile a test program using the generated compiler.

## Steps to Build the Cross Compiler

1. **Install crosstool-ng**
   - Install crosstool-ng using your package manager or by downloading and building from the source:
     ```bash
     sudo apt-get install crosstool-ng
     ```
     OR
     ```bash
     git clone https://github.com/crosstool-ng/crosstool-ng.git
     cd crosstool-ng
     ./bootstrap
     ./configure --enable-local
     make
     sudo make install
     ```

2. **Configure crosstool-ng for AVR target**
   - Create a working directory and initialize crosstool-ng:
     ```bash
     mkdir -p ~/ctng/avr
     cd ~/ctng/avr
     ct-ng menuconfig
     ```
   - In the `menuconfig`, set the target architecture as AVR (e.g., `avr`), and configure other options as needed.

3. **Build the toolchain**
   - Start the build process:
     ```bash
     ct-ng build
     ```
   - After the build is complete, the toolchain will be located in the `~/x-tools/avr/` directory (or the directory you specified during configuration).

4. **Add the toolchain to your PATH**
   - Add the following line to your `~/.bashrc` file:
     ```bash
     export AVR_TOOLCHAIN=~/x-tools/avr/bin/
     export PATH=$AVR_TOOLCHAIN:$PATH
     ```
   - Restart your terminal:
     ```bash
     source ~/.bashrc
     ```

## Steps to Test the Compiler

1. **Create a test project directory**
   ```bash
   mkdir test_compiler
   cd test_compiler
   ```

2. **Create a test program**
   - Create and edit a simple C file:
     ```bash
     touch main.c
     vi main.c
     ```
   - Add the following code to `main.c`:
     ```c
     #include <stdio.h>

     int main() {
         int a = 5, b = 3;
         int sum = a + b;
         printf("Sum of %d and %d is: %d\n", a, b, sum);
         return 0;
     }
     ```

3. **Verify the toolchain installation**
   - Check if the compiler binaries are available:
     ```bash
     ls ~/x-tools/avr/bin/
     ```
   - The binaries should include `avr-gcc` and other related tools.

4. **Alias the compiler**
   - Optionally, add the following alias to your `~/.bashrc` file:
     ```bash
     alias avr-gcc=$AVR_TOOLCHAIN/avr-gcc
     ```
   - Reload your terminal to apply the alias:
     ```bash
     source ~/.bashrc
     ```

5. **Compile the test program**
   - Use the AVR compiler to generate an ELF file for the test program:
     ```bash
     avr-gcc -mmcu=atmega328p -Os -o main.elf main.c
     ```

6. **Run or flash the compiled program**
   - Depending on your setup, you can use an AVR emulator or upload the compiled ELF file to a microcontroller using appropriate tools (e.g., `avrdude`).

