
# Yocto Setup Guide
---

## **1. Clone the Yocto Repository**

### **Steps**
1. Clone the `poky` repository (Yocto's core):
   ```bash
   git clone git://git.yoctoproject.org/poky
   ```
2. Navigate into the `poky` directory:
   ```bash
   cd poky
   ```

### **Why?**
- The `poky` repository contains the core components of the Yocto Project, including BitBake (the build tool) and metadata layers.
- Cloning it is the first step to start working with Yocto.

---

## **2. Check Out the Kirkstone Release**

### **Steps**
1. Check out the `kirkstone` branch (a long-term support release):
   ```bash
   git checkout kirkstone
   ```

### **Why?**
- The `kirkstone` release is a stable, long-term support (LTS) version of Yocto, ensuring reliability and compatibility.

---

## **3. Set Up the Build Environment**

### **Steps**
1. Initialize the build environment:
   ```bash
   source oe-init-build-env build-rpi3
   ```
   This creates a build directory named `build-rpi3`.

2. Verify the build directory structure:
   ```bash
   ls
   ```
   You should see `conf` and `tmp` directories.

### **Why?**
- The `oe-init-build-env` script sets up the environment variables and paths required for Yocto builds.
- The `build-rpi3` directory will contain all build artifacts and configuration files.

---

## **4. Clone Required Layers**

### **Steps**
1. Clone the `meta-raspberrypi` layer (for Raspberry Pi support):
   ```bash
   git clone git://git.yoctoproject.org/meta-raspberrypi ../sources/meta-raspberrypi
   ```

2. Clone the `meta-openembedded` layers (for additional recipes like `tcpdump`):
   ```bash
   git clone git://git.openembedded.org/meta-openembedded ../sources/meta-openembedded
   ```

3. Verify the cloned layers:
   ```bash
   ls ../sources
   ```
   You should see `meta-raspberrypi` and `meta-openembedded`.

### **Why?**
- `meta-raspberrypi` provides Raspberry Pi-specific configurations, device trees, and kernel support.
- `meta-openembedded` contains additional recipes for networking, Python, and more.

---

## **5. Configure `BBLAYERS`**

### **Steps**
1. Open the `conf/bblayers.conf` file:
   ```bash
   nano conf/bblayers.conf
   ```

2. Add the following layers to `BBLAYERS`:
   ```bash
   BBLAYERS ?= " \
     /home/ahmed/yocto/poky/meta \
     /home/ahmed/yocto/poky/meta-poky \
     /home/ahmed/yocto/poky/meta-yocto-bsp \
     /home/ahmed/yocto/sources/meta-raspberrypi \
     /home/ahmed/yocto/sources/meta-openembedded/meta-oe \
     /home/ahmed/yocto/sources/meta-openembedded/meta-python \
     /home/ahmed/yocto/sources/meta-openembedded/meta-networking \
     /home/ahmed/yocto/sources/meta-custom \
   "
   ```
   ###change them with your Absolute Paths – Ensure the paths match your actual directory structure. 


### **Why?**
- `BBLAYERS` specifies which layers are included in the build.
- Adding these layers ensures you have access to Raspberry Pi support, networking tools, and custom recipes.

---

## **6. Configure `local.conf`**  

### **Steps**  

1. Open the `conf/local.conf` file: 
   ```bash
   nano conf/local.conf
   ``` 

2. Add or modify the following lines: 

   - **Set the machine type to Raspberry Pi 3 (64-bit):** 
     ```bash
     MACHINE = "raspberrypi3-64"
     ``` 

   - **Enable UART for debugging:** 
     ```bash
     ENABLE_UART = "1"
     ``` 

   - **Include `tcpdump` and `hello-world` in the image:** 
     ```bash
     IMAGE_INSTALL:append = " tcpdump hello-world "
     ``` 

   - **Set the downloads directory (optional but recommended for caching sources):** 
     ```bash
     DL_DIR = "/home/ahmed/yocto/downloads/"
     ``` 

This ensures -->
- `MACHINE` specifies the target hardware (Raspberry Pi 3 in 64-bit mode).
- `ENABLE_UART` enables the serial console for debugging.
- `IMAGE_INSTALL:append` adds `tcpdump` and `hello-world` to the image.
- `DL_DIR` specifies a centralized location for downloaded source files, saving time in future builds.

---

## **7. Build a Minimal Image**  

### **Steps**  

1. **Start the build process** for the minimal image (`core-image-minimal`): 
   ```bash
   bitbake core-image-minimal -k
   
###if you want to do a singl task not all the build tasks which are 
   *****
   Here’s a general  order for BitBake tasks: 
1. **`do_fetch`** → Downloads source code. 
2. **`do_unpack`** → Extracts the downloaded sources. 
3. **`do_patch`** → Applies patches to the source. 
4. **`do_configure`** → Configures the source for building. 
5. **`do_compile`** → Compiles the source code. 
6. **`do_install`** → Installs compiled files into a temporary destination. 
7. **`do_package`** → Prepares packaged output files. 
8. **`do_rootfs`** → Creates the root filesystem (for images). 
9. **`do_image`** → Generates the final image (for images). 

Each task depends on the previous ones. For example, `do_compile` won’t work unless `do_fetch`, `do_unpack`, `do_patch`, and `do_configure` are done first. 
so you have to make sure that u already done the task before 
******
    if u want to download the source codes which is the first task then build the img in your home, you can run 
   ****************************************************
          bitbake core-image-minimal --runonly=fetch   * 
   ****************************************************
    then you can run ```bitbake core-image-minimal -k ```
   ``` 
   The `-k` flag ensures that the build continues even if some tasks fail. 

2. **Wait for the build to complete.** 
   - This may take several hours depending on your system’s performance. 
   - If you experience high CPU usage or overheating, consider limiting parallel tasks in `local.conf`: 
     ```bash
     BB_NUMBER_THREADS = "6"
     PARALLEL_MAKE = "-j6"
     ``` 
     (Adjust the numbers based on your CPU cores bs dah sha8al ya3ny ana el lab kan hymot abl ma a3mloh.) 

Once the build finishes, the final image will be available in: 
```bash
tmp/deploy/images/raspberrypi3-64/
```
---

## **8. Create a Custom Layer**

### **Steps**
1. Create a custom layer named `meta-custom`:
   ```bash
   bitbake-layers create-layer ../sources/meta-custom
   ```

2. Add the custom layer to your build configuration:
   ```bash
   bitbake-layers add-layer ../sources/meta-custom
   ```

3. Verify the layer is added:
   ```bash
   bitbake-layers show-layers
   ```

### **Why?**
- Custom layers allow you to add your own recipes, configurations, and modifications without altering the base Yocto layers.
- This keeps your changes organized and maintainable.

---

## **9. Add a Custom Recipe**

### **Steps**
1. Create a recipe directory for a simple "Hello, Yocto!" program:
   ```bash
   mkdir -p ../sources/meta-custom/recipes-custom/hello-world
   ```

2. Create a `files` directory and add a `hello.c` file:
   ```bash
   mkdir -p ../sources/meta-custom/recipes-custom/hello-world/files
   nano ../sources/meta-custom/recipes-custom/hello-world/files/hello.c
   ```
   Add the following code:
   ```c
   #include <stdio.h>

   int main() {
       printf("Hello, Yocto!\n");
       printf("  Not Today.\n");
       return 0;
   }
   ```

3. Create a recipe file (`hello-world_1.0.bb`):
   ```bash
   nano ../sources/meta-custom/recipes-custom/hello-world/hello-world_1.0.bb
   ```
   Add the following content:
   
   ```bitbake
   DESCRIPTION = "A simple Hello, Yocto! program"
   LICENSE = "MIT"
   LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

   SRC_URI = "file://hello.c"

   S = "${WORKDIR}"

   do_compile() {
       ${CC} ${CFLAGS} ${LDFLAGS} hello.c -o hello
   }

   do_install() {
       install -d ${D}${bindir}
       install -m 0755 hello ${D}${bindir}
   }
   ```

4. Rebuild the image:
   ```bash
   bitbake core-image-minimal
   ```

### **Why?**
- The recipe defines how to build and install the "Hello, Yocto!" program.
- Adding it to `IMAGE_INSTALL` ensures the program is included in the final image.

---

## **10. Flash the Image to an SD Card**

### **Steps**
1. Locate the built image:
   ```bash
   ls tmp/deploy/images/raspberrypi3-64/
   ```
   The image file will be named something like `core-image-minimal-raspberrypi3-64.wic`.

2. Flash the image to an SD card using `dd` or a tool like `balenaEtcher`:
   ```bash
   sudo dd if=tmp/deploy/images/raspberrypi3-64/core-image-minimal-raspberrypi3-64.wic of=/dev/sda bs=4M status=progress
   ```
   Replace `/dev/sda` with the correct device for your SD card.

### **Why?**
- Flashing the image to an SD card allows you to boot the Raspberry Pi with your custom Yocto image.

---

## **11. Verify the Image on the Raspberry Pi**

### **Steps**
1. Insert the SD card into the Raspberry Pi and power it on.
2. Log in to the system (default username: `root`).
3. Verify the "Hello, Yocto!" program:
   ```bash
   hello
   ```
   Output:
   ```
   Hello, Yocto!
    not today.
   ```

4. Verify `tcpdump` is installed:
   ```bash
   tcpdump 
   or
   tcpdump --version
   ```

### **Why?**
- Verifying the programs ensures that your customizations were successfully included in the image.

---

## **Conclusion**
You have successfully set up the Yocto Project, built a minimal image, created a custom layer, added a recipe, and included `tcpdump`. 
