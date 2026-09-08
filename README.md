```
 _    ________________________  ____ 
| |  / / ____/ ____/_  __/ __ \/ __ \
| | / / __/ / /     / / / / / / /_/ /
| |/ / /___/ /___  / / / /_/ / _, _/ 
|___/_____/\____/ /_/  \____/_/ |_|  
```                                     
A C library providing dynamic array functionality.

## Table of Contents
- [About](#about)
- [Installation](#installation)

## About
This library provides a dynamic array implementation for C.

**Dependencies:**
- `stddef.h`
- `string.h`
- `stdlib.h`

## BUILDING THE LIBRARY

**Prerequisites**:
- `CMake`
- `Ninja`

## Linux build instructions
You can build the library either static (.a) or shared (.so)

Replace `vN` in `-DARCH_LEVEL=vN` with your target microarchitecture (native, v1, v2, etc.)

**Static**
```bash

cmake -G Ninja -B build \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DARCH_LEVEL=v2
```

**Shared**
```bash 

cmake -G Ninja -B build \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DARCH_LEVEL=v2
```

**Compile and Install**
```bash

cmake --build build
cmake --install build --prefix release/
```


## Windows build instructions
You can build the library as a dynamic link library(.dll) or a static library (.lib/.a)

```bash

cmake -G Ninja -B build -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DARCH_LEVEL=native
cmake --build build
cmake --install build --prefix release/mingw
```
