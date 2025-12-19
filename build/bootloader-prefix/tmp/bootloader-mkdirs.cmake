# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/v5.1.2/esp-idf/components/bootloader/subproject"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/tmp"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/src"
  "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/18452/Documents/GitHub-young-whites/esp32-sWatch/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
