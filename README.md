# DeepAlloc

## Directories

* bin : output executable files
* lib : output library files
* include : header files
* include/internal/deepalloc_internal.h : It includes all header files, and should be included by all source files.
* src : source files
* test/src: test source files


## System Requirements

1. 2nd Generation Intel Xeon Scalable Processors
2. Intel® Optane™ Persistent Memory 100 Series
3. cmake (version > 3.10)
4. libpmem
5. libjemalloc


## Build

```
autogen.sh [d/r]
autogen.sh [d/r] [testname]
```
autogen.sh encapsulates CMakeLists.txt:
* [**d/r**] : debug/release
* [**testname**] : build test/src/**testname**.cpp

## Other

Default pmem directory: /mnt/pmem/deepalloc_files/ /mnt/pmem0.1/deepalloc_files/

## Example

```
./autogen.sh r example    # test/src/example.cpp
./bin/example
```