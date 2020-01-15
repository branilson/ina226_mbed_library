cmake_minimum_required(VERSION 2.8.3)
project(ina226_mbed_library)

install(DIRECTORY src DESTINATION src/ina226_mbed_library)
install(DIRECTORY include DESTINATION src/ina226_mbed_library)
install(FILES DESTINATION src/ina226_mbed_library/src)
install(FILES DESTINATION src/ina226_mbed_library/include)