$ uname -r
6.8.0-49-generic

# build the module
```
$ make -C /lib/modules/$(uname -r)/build M=$PWD modules
```

error log
```
make: Entering directory '/usr/src/linux-headers-6.8.0-49-generic' warning: the compiler differs from the one used to build the kernel The kernel was built by: x86_64-linux-gnu-gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0 
You are using: CC [M] /home/whoyouhow/Desktop/LDD3/ex01_simple_module.o 
/bin/sh: 1: gcc-12: not found 
make[2]: 
*** [scripts/Makefile.build:243: /home/whoyouhow/Desktop/LDD3/ex01_simple_module.o] Error 127 
make[1]: *** [/usr/src/linux-headers-6.8.0-49-generic/Makefile:1925: /home/whoyouhow/Desktop/LDD3] Error 2 
make: *** [Makefile:240: __sub-make] Error 2 make: Leaving directory '/usr/src/linux-headers-6.8.0-49-generic'
```

fix build system for gcc-12
```
$ sudo apt update
$ sudo apt install gcc-12 g++-12 build-essential
$ make -C /lib/modules/$(uname -r)/build M=$PWD clean
$ make -C /lib/modules/$(uname -r)/build M=$PWD modules
```

error log
```
make: Entering directory '/usr/src/linux-headers-6.8.0-49-generic' 
warning: the compiler differs from the one used to build the kernel The kernel was built by: x86_64-linux-gnu-gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0 You are using: gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04.2) 12.3.0 
CC [M] /home/whoyouhow/Desktop/LDD3/ex01_simple_module.o 
/home/whoyouhow/Desktop/LDD3/ex01_simple_module.c:4:5: warning: no previous prototype for ‘ex01_simple_module_init’ [-Wmissing-prototypes] 
4 | int ex01_simple_module_init(void) 
    | ^~~~~~~~~~~~~~~~~~~~~~~ 
/home/whoyouhow/Desktop/LDD3/ex01_simple_module.c:10:6: warning: no previous prototype for ‘ex01_simple_module_exit’ [-Wmissing-prototypes] 
10 | void ex01_simple_module_exit(void) 
     | ^~~~~~~~~~~~~~~~~~~~~~~ 
 MODPOST /home/whoyouhow/Desktop/LDD3/Module.symvers 
ERROR: modpost: missing MODULE_LICENSE() in /home/whoyouhow/Desktop/LDD3/ex01_simple_module.o 
make[2]: *** [scripts/Makefile.modpost:145: /home/whoyouhow/Desktop/LDD3/Module.symvers] Error 1 
make[1]: *** [/usr/src/linux-headers-6.8.0-49-generic/Makefile:1877: modpost] Error 2 
make: *** [Makefile:240: __sub-make] Error 2 
make: Leaving directory '/usr/src/linux-headers-6.8.0-49-generic'
```

fix bug for modpost that need to announce license (MODULE_LICENSE()), add the following announcement in .c file
``` =c
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple example kernel module");
```
```
$ make clean
$ make
```

# load the module
```
$ sudo insmod ex01_simple_module.ko
```

# remove the module
```
$ sudo rmmod ex01_simple_module
```

# check the module was loaded / removed
```
$ sudo tail -f /var/log/syslog 
or
$ sudo dmesg | tail -n 20
```

And you will see 
```
Nov 21 17:42:47 whoyouhow-VirtualBox kernel: [ 3288.336174] Inside the ex01_simple_module_init function
Nov 21 17:44:10 whoyouhow-VirtualBox kernel: [ 3371.596083] Inside the ex01_simple_module_exit function
```

Question : why __init & __initdata token not really decrease the kernel size when loading module?

Ans : 
These token will really decrease kernel size when the module is built-in module (built in vmlinux), when kernel finish all initialization when booting, kernel will call free_initmem() to free all init section.

ref : https://kernelnewbies.org/FAQ/InitExitMacros?utm_source=chatgpt.com

But for loadable module (.ko), kernel will not free the module .init section.
So __init in the module still exist in the memory of module.

ref : https://stackoverflow.com/questions/11680641/init-and-exit-macros-usage-for-built-in-and-loadable-modules

# Export Symbol
Symbol can be the addresses of global kernel items -- "functions" and "variables"

Note : sysmobs to be exported cannot be expressed by static, and should be placed outside of any functions.

Usage : 
    EXPORT_SYMBOL(name);

## If insmod a module that needs some symbols kernel don't has, you cannot  insert module
```
$ sudo insmod ./ex05_using_symbols.ko
```
insmod: ERROR: could not insert module ./ex05_using_symbols.ko: Unknown symbol in module
```
$ sudo dmesg
```
[ 1102.706836] ex05_using_symbols: loading out-of-tree module taints kernel.

[ 1102.706895] ex05_using_symbols: Unknown symbol ex05_simple_module_function (err -2)

## Insert modules with the correct order
```
$ sudo insmod ./ex05_exporting_symbols.ko
$ sudo insmod ./ex05_using_symbols.ko
```
```
$ lsmod
```
Module                  Size  Used by
ex05_using_symbols     49152  0
ex05_exporting_symbols    49152  1 ex05_using_symbols
$ sudo dmesg

[ 2525.396077] Inside the ex05_simple_module_init function     // in ex05_exporting_symbols

[ 2530.299534] Inside the ex05_simple_module_init function     // in ex05_using_symbols

[ 2530.304797] Inside the ex05_simple_module_function function // in ex05_using_symbols
