1. build kernel module
```
 make
```

2. build the userspace process
 ```
gcc mm_struct_multi_user.c -o mm_struct_multi_user -lpthread
 ```
3. run the userspace process
```
./mm_struct_multi_user
```
4. install the kernel modules
```
insmod mm_struct_kmod.ko pid_mem=`pidof <process_name>`
```
