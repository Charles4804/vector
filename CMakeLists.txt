cmake_minimum_required(VERSION 3.21)
project(Vector VERSION 1.2.3 LANGUAGES C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_VISIBILITY_PRESET hidden)

set(ARCH_LEVEL "v2" CACHE STRING "Target x86-64 microarchitecture level")

if(ARCH_LEVEL STREQUAL "native")
    set(TARGET_MARCH "native")
elseif(ARCH_LEVEL STREQUAL "v1")
    set(TARGET_MARCH "x86-64")
else()
    set(TARGET_MARCH "x86-64-${ARCH_LEVEL}")
endif()

add_library(Vector src/vector.c)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(Vector PRIVATE "-march=${TARGET_MARCH}")
endif()

if(BUILD_SHARED_LIBS)
    target_compile_definitions(Vector PRIVATE WINDOWS_DLL)
endif()
target_include_directories(Vector 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(Vector PROPERTIES
    OUTPUT_NAME "Vector"     
    PREFIX ""
    IMPORT_PREFIX ""
)


include(GNUInstallDirs)

install(TARGETS Vector
    EXPORT VectorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}

)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

install(EXPORT VectorTargets
    FILE VectorTargets.cmake
    NAMESPACE Vector::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vector
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/VectorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/VectorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/VectorConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vector
)

install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/VectorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/VectorConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vector
)


include(CTest)
add_subdirectory(tests)
