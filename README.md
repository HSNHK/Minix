# Minix

[![HSNHK - Minix](https://img.shields.io/static/v1?label=HSNHK&message=Minix&color=blue&logo=github)](https://github.com/HSNHK/Minix)
[![stars - Minix](https://img.shields.io/github/stars/HSNHK/Minix?style=social)](https://github.com/HSNHK/Minix)
[![forks - Minix](https://img.shields.io/github/forks/HSNHK/Minix?style=social)](https://github.com/HSNHK/Minix) [![GitHub release](https://img.shields.io/github/release/HSNHK/Minix?include_prereleases=&sort=semver)](https://github.com/HSNHK/Minix/releases/)
[![License](https://img.shields.io/badge/License-MIT-blue)](#license)
[![issues - Minix](https://img.shields.io/github/issues/HSNHK/Minix)](https://github.com/HSNHK/Minix/issues)

An example of a small Kernel

kernel type: monolithic

> A monolithic kernel is an operating system architecture where the entire operating system is working in kernel space. The monolithic model differs from other operating system architectures (such as the microkernel architecture) in that it alone defines a high-level virtual interface over computer hardware.

<p align="center">
<img src="./resources/images/Kernel.png">
</p>

## Build
```
build.sh 
```

```
qemu-system-x86_64 -cdrom iso/build/Minix.iso
```
## Tree
- drivers
    - keyboard
    - vga
        - console
- kernel
    - io

## License

Released under [MIT](/LICENSE) by [@HSNHK](https://github.com/HSNHK).
