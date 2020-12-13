# cmake file for duilib
#Author Qi Gao(monkgau@gmail.com)
#Created: 2012/09/16

# Author Wu Yuanshou(wu.yuanshou@foxmail.com)
#Created: 2020/12/13

project(mini-browser)

add_definitions(-DUILIB_EXPORTS -DUILIB_STATIC)

add_executable(mini-browser WIN32 main.cc)
target_link_libraries(mini-browser duilib)