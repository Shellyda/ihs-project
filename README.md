# Project layout helper and Scripts/Documentations for developing IF817 Course project

**REMIDER**: This project layout it's not mandatory! You can feel free to use whatever build system you use for developing a user application. This has only a simple Makefile for people who don't need to setup a complex build system and just want to develop a simple C/C++/Assembly application. BUT be careful with the 'driver' folder, inside it has a Makefile that is vital for building the driver/module and one must not remove it.

## Content

## Current project tree

    .
    ├── src
    │   └── main.cpp
    ├── include
    │   ├── display.h
    │   └── ioctl_cmds.h
    ├── driver
    │   ├── char
    │   │   ├── dummy.c
    │   │   └── Makefile
    │   └── pci
    │       ├── de2i-150.c
    │       └── Makefile
    ├── exemples
    │   ├── c
    │   │   ├── app-char.c
    │   │   └── app-pci.c
    │   └── python
    │       ├── app-char.py
    │       └── app-pci.py
    ├── docs
    │   └── commands.md
    ├── LICENSE
    ├── Makefile
    ├── README.md
    └── setup.sh

## How to Run & Debug

### How use `setup.sh` script

1. Give execution permission:

   ```bash
   chmod +x setup.sh
   ```

2. Run:

   ```bash
   ./setup.sh
   ```

Check commands to help run and debug here:

- [Useful Commands](docs/commands.md)

You can also build the **setup** by following these steps below

### Step by step to build setup

1. **Compile the driver**

   ```bash
   cd driver/pci
   make
   ```

2. **Insert the module into the kernel**

   ```bash
   sudo insmod de2i-150.ko
   ```

3. **Set device permissions**

   > Required so non-root users can access the device.

   ```bash
   sudo chmod 666 /dev/mydev
   ```

4. **(Optional) Verify that the device was created**

   ```bash
   ls -l /dev/mydev
   ```

5. **Compile the Main Application**
   Go to the root folder and compile it:

   ```bash
   make
   ```

   After that, the following structure will be created in the root file:

   ```bash
   target/
   ├── release/
   │    ├── app        # final executable
   │    └── obj/       # .o object files
   ├── debug/          # created if you run make DEBUG=1
   └── app.lst         # disassembly dump
   ```

6. **Run the Application**
   Go to `target` folder created in the last step and run:

   ```bash
   ./app /dev/mydev
   ```

> The argument `/dev/mydev` is the device node created by your driver.
> The program will communicate with the hardware via **ioctl**, `read`, and `write`.

## Debugging & Maintenance

- **Check kernel logs** (useful to confirm successful load or see error messages):

  ```bash
  dmesg | tail -n 30
  ```

- **Remove the module**:

  ```bash
  sudo rmmod de2i-150
  ```

- **Reinsert the module after changes**:

  ```bash
  sudo rmmod de2i-150
  sudo insmod de2i-150.ko
  ```

- **Verify the module is loaded**:

  ```bash
  lsmod | grep de2i
  ```
