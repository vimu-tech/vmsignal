cmake_minimum_required(VERSION 3.14)

project(windowtest LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#head file path，头文件目录 ${CMAKE_SOURCE_DIR}
INCLUDE_DIRECTORIES(
            ../inc
            ../inc/window
            ../inc/fft
)

get_property(include_dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${include_dirs}") #打印一下目录情况

FILE (GLOB ALL_INCLUDE "../inc/*.hpp" "../inc/*.h" )

#link directories
if(${CMAKE_COMPILER_IS_GNUCXX})
    link_directories( ../SharedLibrary/${CMAKE_SYSTEM_NAME}/X64/Shared/$<$<CONFIG:Release>:Release>$<$<CONFIG:Debug>:Debug>)
else()
    if(${CMAKE_EXE_LINKER_FLAGS} STREQUAL "/machine:ARM64")
        link_directories( ../SharedLibrary/${CMAKE_SYSTEM_NAME}/AMR64/Shared/$<$<CONFIG:Release>:Release>$<$<CONFIG:Debug>:Debug>)
    elseif(${CMAKE_EXE_LINKER_FLAGS} STREQUAL "/machine:X86")
        link_directories( ../SharedLibrary/${CMAKE_SYSTEM_NAME}/X86/Shared/$<$<CONFIG:Release>:Release>$<$<CONFIG:Debug>:Debug>)
    else()
        link_directories( ../SharedLibrary/${CMAKE_SYSTEM_NAME}/X64/Shared/$<$<CONFIG:Release>:Release>$<$<CONFIG:Debug>:Debug>)
    endif()
endif()

message(">>> OUTPUT DIR=${OUTPUT_DIR}  ${CMAKE_EXE_LINKER_FLAGS}")

#4.source directory，源文件目录
aux_source_directory(./ SOURCE_LIST)
foreach(file IN LISTS SOURCE_LIST)
  message(STATUS ${file})
endforeach(file)

#FILE (GLOB ALL_SOURCE "../*.cpp" "../*.c") #不推荐

set ( ALL_SOURCES ${SOURCE_LIST}
                    )
message(">>> source_dirs=${ALL_SOURCES}") #打印一下目录情况



# 对inc src的源码分组到组里
#vs
source_group(inc FILES ${ALL_INCLUDE})
source_group(src FILES ${ALL_SOURCES})
#qt
add_custom_target(files SOURCES ${ALL_INCLUDE} ${ALL_SOURCES})

#
add_executable(${PROJECT_NAME} ${ALL_INCLUDE} ${ALL_SOURCES})

target_link_libraries(${PROJECT_NAME} vmsignal)
