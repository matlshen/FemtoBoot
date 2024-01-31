add_library(bootutil STATIC)

target_include_directories(bootutil
    PUBLIC
        inc
    PRIVATE
        src
)

target_sources(bootutil
    PRIVATE
        src/crc32.c
)