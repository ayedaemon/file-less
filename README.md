>> Basic program to read a binary and copy it to a new in memory file.

### idea?

1. Create an in-memory file (that means this new file will not be present in the harddisk and can't be found with commands like ls').
2. read a local binary (1024 bytes a time) and write it to the mem file (already created in-memory file).
3. execute the in-memory file.



### method?

1. Create an in-memory file using `memfd_create()` syscall.	[man 2 memfd_create](https://man7.org/linux/man-pages/man2/memfd_create.2.html)
2. Read a local file using `open()` syscall.			[man 2 open](https://man7.org/linux/man-pages/man2/open.2.html)
3. Write data to mem file using `write()` syscall.		[man 2 write](https://man7.org/linux/man-pages/man2/write.2.html)
4. executes the file using `fexecve()` library call.     	[man 3 fexecve](https://man7.org/linux/man-pages/man3/fexecve.3.html)


### Why?

> To understand what file-less malwares are and how they work.


### How to run?

```
make  					## To make the binary - main.o
	
./main.o `which file` `which ls` 	## will execute - /path/to/file /path/to/ls

## OR

./main.o `which mkdir` $PWD/NEW_FOLDER	## Use this to create a new folder in current directory

echo $?					## Check the status in bash
```

## DISCLAIMER
This repo is for educational purpose; usage of this for attacking targets without prior mutual consent is illegal. It is the end user's responsibility to obey all applicable local, state, and federal laws. Developers assume no liability and are not responsible for any misuse of this program.
