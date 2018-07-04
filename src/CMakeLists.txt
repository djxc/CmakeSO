project(soTest)

# 搜索本目录搜索源码并赋值给变量
aux_source_directory(. DIR_LIB_SRCS)

# set make to a shared library
add_library(djso SHARED ${DIR_LIB_SRCS})
