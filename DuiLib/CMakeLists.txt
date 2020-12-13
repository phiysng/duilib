# cmake file for duilib
#Author Qi Gao(monkgau@gmail.com)
#Created: 2012/09/16

# Author Wu Yuanshou(wu.yuanshou@foxmail.com)
#Created: 2020/12/13

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} Root_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Control Control_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Core Core_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Layout Layout_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Utils Utils_src)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(duilib STATIC ${Control_src} ${Core_src} ${Layout_src} ${Utils_src} ${Root_src})

target_include_directories(duilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(duilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Control)
target_include_directories(duilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(duilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Layout)
target_include_directories(duilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utils)

# 静态库需要宏定义 UILIB_STATIC
add_definitions(-DUILIB_EXPORTS -DUILIB_STATIC)
target_link_libraries(duilib comctl32)
set_target_properties(duilib PROPERTIES OUTPUT_NAME "duilib")

# use static LINK
#add_custom_command(TARGET duilib POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different
#  ${PROJECT_BINARY_DIR}/lib/duilib.dll ${PROJECT_SOURCE_DIR}/bin/duilib.dll)
