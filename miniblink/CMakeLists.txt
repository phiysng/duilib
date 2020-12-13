# cmake file for duilib
#Author Qi Gao(monkgau@gmail.com)
#Created: 2012/09/16

# Author Wu Yuanshou(wu.yuanshou@foxmail.com)
#Created: 2020/12/13

project(mini-browser)

add_definitions(-DUILIB_EXPORTS -DUILIB_STATIC)

add_executable(mini-browser WIN32 main.cc)
target_link_libraries(mini-browser duilib)


# 复制布局xml
# https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake?rq=1
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/skin $<TARGET_FILE_DIR:${PROJECT_NAME}>/skin)
