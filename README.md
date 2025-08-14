# PokeCIn - Infrastructure hardware-software Course project
This repository contains the structure, scripts, and documentation to develop the **IF817 course project** - a C++ game Pokémon like for the DE2i-150 FPGA board, integrating hardware-mapped peripherals (switches, buttons, LEDs, and 7-segment displays) via a custom PCI character driver. The project uses Quartus II for FPGA mapping, Raylib for rendering via HDMI, and real-time interaction through the board’s I/O components.

| Gameplay |  FPGA DE2i-150  |
|--------------------------------|------------------|
| <img src="https://github.com/user-attachments/assets/2aa637e0-b757-4ccb-959d-1b2f771c2101" width="400"> | <img src="https://github.com/user-attachments/assets/ed2309d3-5dc9-4cba-8f10-6994ca743b21" width="400"> |

The project is divided into four main stages, as specified in the course requirements:

1. **Peripheral Mapping** – All DE2i-150 peripherals (switches, buttons, LEDs, and 7-segment displays) are mapped in Quartus II for PCI read/write access.
2. **Driver Development** – Implementation of a PCI character driver in C/C++ for Linux, enabling communication between the Atom CPU and FPGA-mapped devices.
3. **Application Development** – The game is implemented in C++ using Raylib for rendering via HDMI, with real-time interaction through mapped hardware inputs and outputs.
4. **Optional Enhancements** – Possible additions include sound interaction, OpenMP parallelization, or C/Assembly integration for performance boosts.

**Reminder**: This layout includes a simple Makefile for those who want to develop a straightforward C/C++/Assembly project without complex configuration. **Do not remove the Makefile inside the `driver` folder**, as it is essential for building the driver/module.

## Contributors
<table>
  <tr>
   <td align="center"><a href="https://github.com/alyssonramos"><img src="https://avatars.githubusercontent.com/u/84824614?v=4" width="100px;" alt=""/><br /><sub><b>Alysson Ramos</b></sub></a><br/></td>
   <td align="center"><a href="https://github.com/LucasTorres96"><img src="https://avatars.githubusercontent.com/u/84953349?v=4" width="100px;" alt=""/><br /><sub><b>Lucas Torres</b></sub></a><br/></td>
   <td align="center"><a href="https://github.com/Shellyda"><img src="https://avatars.githubusercontent.com/u/69990297?v=4" width="100px;" alt=""/><br /><sub><b>Shellyda Barbosa</b></sub></a><br/></td>
</table>

## Content

### Game Overview 

* **Raylib-based rendering** via HDMI for smooth 2D graphics.
* **Real hardware interaction** using switches, buttons, and LEDs on the FPGA.
* **Custom game loop** controlling player movement, map collisions, and animations.
* **Music and sound effects** for an immersive experience.

Players can explore a pixel-art map, control their character in real time, and interact with the environment through the FPGA’s I/O peripherals.

### Current Project Tree

```
.
├── src
│   ├── assets/           # Images, sounds, and other game resources
│   ├── game/             # Game logic and components
│   │   ├── game.cpp/.h   # Manages game states and main loop
│   │   ├── map.cpp/.h    # Map rendering and collision logic
│   │   ├── player.cpp/.h # Player movement, animations, and interactions
│   ├── main.cpp          # Application entry point
│   └── Makefile          # Game compilation
├── include/
│   ├── display.h
│   └── ioctl_cmds.h
├── driver/
│   ├── char/
│   │   ├── dummy.c
│   │   └── Makefile
│   └── pci/
│       ├── de2i-150.c
│       └── Makefile
├── exemples/
│   ├── c/
│   │   ├── app-char.c
│   │   └── app-pci.c
│   └── python/
│       ├── app-char.py
│       └── app-pci.py
├── docs/
│   └── commands.md
├── LICENSE
├── Makefile              # Root makefile
├── README.md
└── setup.sh
```
 
## How to Run & Debug

### Using `setup.sh`

1. Give execution permission:

   ```bash
   chmod +x setup.sh
   ```

2. Run:

   ```bash
   ./setup.sh
   ```

Check [Useful Commands](docs/commands.md) for more details.

### Step-by-step Manual Setup

#### 1. Compile the driver

```bash
cd driver/pci
make
```

#### 2. Insert the module into the kernel

```bash
sudo insmod de2i-150.ko
```

#### 3. Set device permissions

```bash
sudo chmod 666 /dev/mydev
```

#### 4. (Optional) Verify device creation

```bash
ls -l /dev/mydev
```

#### 5. Compile the Main Application

```bash
make
```

This will create the `target/` directory:

```
target/
├── release/
│    ├── app        # final executable
│    └── obj/       # .o object files
├── debug/          # created if you run make DEBUG=1
└── app.lst         # disassembly dump
```

#### 6. Run the Application

```bash
./app /dev/mydev
```

> `/dev/mydev` is the device node created by the driver. The application communicates with the hardware via `ioctl`, `read`, and `write`.


## Debugging & Maintenance

* Check kernel logs:

```bash
dmesg | tail -n 30
```

* Remove the module:

```bash
sudo rmmod de2i-150
```

* Reinsert the module:

```bash
sudo rmmod de2i-150
sudo insmod de2i-150.ko
```

* Verify module load:

```bash
lsmod | grep de2i
```

## Course Requirements Summary

* **Mandatory peripheral mapping** in Quartus II (switches, buttons, LEDs, displays).
* **Custom PCI character driver** in C/C++ for Ubuntu.
* **C++ game application** using FPGA-mapped I/O for interaction.
* **Deliverables**: Incremental submissions for mapping, driver, and final application.
* **Optional bonus**: Sound interaction, OpenMP usage, C/Assembly integration, LCD mapping.
