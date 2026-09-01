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
Download the latest release from the [Releases](https://github.com/Charles4804/vector/releases) section.
And then extract the zip file. 
> [!CAUTION]
> Version 1.1.4 down to the first version does not have any optimization, and has multiple critical bugs

**Linux**
---
Put the **include** folder to /usr/local/include/Vector/ _Needs Elevated Privileges_
And then put the lib folder's contents to /usr/local/lib/

## Implementation
To use the library, add the installation path to your system's environment variables (PATH).

### CMake Configuration
Add the following to your `CMakeLists.txt`:

```cmake
list(APPEND CMAKE_PREFIX_PATH "<path_to_extracted_library>") # NOT THE bin/ THE WHOLE FOLDER OR THE PARENT
find_package(Vector REQUIRED)
target_link_libraries(<target> PUBLIC Vector::Vector)
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
