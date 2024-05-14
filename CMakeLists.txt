cmake_minimum_required(VERSION 3.25)
project(ZJU_Ds_Lectures C)

set(CMAKE_C_STANDARD 11)

add_executable(ZJU_Ds_Lectures main.c lec1.1_a.c lec1.1_b.c lec.1.1-c.c Binary_search.c DSBook_exe1.5.c PTA01-a.c PTA01-a-RightMethod.c "PTA01-b___.c" PTA01-b_HELP.c lec1.3.c union_test.c lec2.1-a.c lec2.1-b.c lec2.2-a.c lec2.2-b.c lec2.3-a.c lec2.3-b.c lec2.3-b-recite.c lec2.3-a-recite.c lec2.4.c lec2.4-b.c lec2.1_reverseList.c PTA02-3.c PTA02-2.c PTA02_Func-1.c PTA01_Func-3.c)
# 遍历项目根目录下所有的 .cpp 文件
file (GLOB_RECURSE files *.c)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
