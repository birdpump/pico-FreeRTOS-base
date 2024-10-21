# Add the executable
add_executable(pico-rtos
        pico-rtos.cpp
)

# Include directories
target_include_directories(pico-rtos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

# Link libraries
target_link_libraries(pico-rtos
        pico_stdlib
        FreeRTOS-Kernel-Heap4
)

pico_set_program_name(pico-rtos "pico-rtos")
pico_set_program_version(pico-rtos "0.1")

# Enable USB output, disable UART output
pico_enable_stdio_usb(pico-rtos 1)
pico_enable_stdio_uart(pico-rtos 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(pico-rtos)
