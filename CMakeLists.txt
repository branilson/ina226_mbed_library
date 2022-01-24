cmake_minimum_required(VERSION 2.8.3)
project(ina226_mbed_library)

include(CMakePackageConfigHelpers)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

foreach(SOURCE_PATH ${SOURCES})
  get_filename_component(FILE_NAME "${SOURCE_PATH}" NAME)
  list(APPEND SOURCES_INSTALLED "${FILE_NAME}")
endforeach()

list(TRANSFORM SOURCES_INSTALLED PREPEND "src/${PROJECT_NAME}/src/")

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
  INTERFACE
    "$<BUILD_INTERFACE:${SOURCES}>"
    "$<INSTALL_INTERFACE:${SOURCES_INSTALLED}>"
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/src/${PROJECT_NAME}/include>"
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
)

install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION share/${PROJECT_NAME}/cmake
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src
        DESTINATION src/${PROJECT_NAME}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
        DESTINATION src/${PROJECT_NAME}
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION share/${PROJECT_NAME}/cmake
)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION share/${PROJECT_NAME}/cmake
)
