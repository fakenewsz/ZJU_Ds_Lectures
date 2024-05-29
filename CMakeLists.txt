cmake_minimum_required(VERSION 3.25)
project(ZJU_Ds_Lectures C)

set(CMAKE_C_STANDARD 11)

add_executable(ZJU_Ds_Lectures main.c lec1.1_a.c lec1.1_b.c lec.1.1-c.c Binary_search.c DSBook_exe1.5.c PTA01-a.c PTA01-a-RightMethod.c "PTA01-b___.c" PTA01-b_HELP.c lec1.3.c union_test.c lec2.1-a.c lec2.1-b.c lec2.2-a.c lec2.2-b.c lec2.3-a.c lec2.3-b.c lec2.3-b-recite.c lec2.3-a-recite.c lec2.4.c lec2.4-b.c lec2.1_reverseList.c PTA02-3.c PTA02-2_HELPed.c PTA02_Func-1.c PTA01_Func-3.c PTAxt2.2.c PTAxt2.8.c DSBook_3.11.c DSBook_3.12.c DSBook_3.13.c lec3.1.c lec3.2.c test.c lec3.4.c lec4.3.c lec4.2.c PAT04-5.c PAT04-5_Help.c lec5.1.c lec5.2.c lec4.1.c lec5.3.c lec6.1-a.c lec6.1-b.c lec6.2.c lec7.1-a.c lec7.1-b.c lec7.1-c.c lec6.1-c.c lec8.1-a.c lec8.1-b.c lec8.2.c lec9.4-a.c lec9.4-b.c lec9.4-c.c lec9.3.c lec9.2.c lec10.3-a.c lec10.3-b.c)
# 遍历项目根目录下所有的 .cpp 文件
file (GLOB_RECURSE files *.c)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
