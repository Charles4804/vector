 _    ________________________  ____ 
| |  / / ____/ ____/_  __/ __ \/ __ \
| | / / __/ / /     / / / / / / /_/ /
| |/ / /___/ /___  / / / /_/ / _, _/ 
|___/_____/\____/ /_/  \____/_/ |_|  
                                     
A C library providing dynamic array functionality.

## Table of Contents
- [About](#about)
- [Installation](#installation)
- [Implementation](#implementation)
- Also read this [Documentation](DOCUMENTATION.md)

## About
This library provides a dynamic array implementation for C.

**Tools Used**
- gcc
- cmake
- ninja
- nvim

**Dependencies:**
- `stddef.h`
- `string.h`
- `stdlib.h`

## Installation
Download the latest release from the [Releases]([##############################################]) section.

## Implementation
To use the library, add the installation path to your system's environment variables (PATH).

### CMake Configuration
Add the following to your `CMakeLists.txt`:

```cmake
find_package(vector REQUIRED)

target_link_libraries(<add_executable_name> PRIVATE vector::vector)
```

### Usage Example
```c
#include <vector/vector.h>

int main() {
    Vector v;
    VectorNew(&v, sizeof(char *));
    
    // API usage here
    
    VectorFree(&v);
    return 0;
}
```
