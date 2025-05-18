set(SRCS secinput.h                        strcat_s.c     vsscanf_s.c
fscanf_s.c          securecutil.c          strcpy_s.c     vswprintf_s.c
fwscanf_s.c         securecutil.h          strncat_s.c    vswscanf_s.c
gets_s.c            secureinput_a.c        strncpy_s.c    vwscanf_s.c
input.inl           secureinput_w.c        strtok_s.c     wcscat_s.c
memcpy_s.c          secureprintoutput_a.c  swprintf_s.c   wcscpy_s.c
memmove_s.c         secureprintoutput.h    swscanf_s.c    wcsncat_s.c
memset_s.c          secureprintoutput_w.c  vfscanf_s.c    wcsncpy_s.c
output.inl          snprintf_s.c           vfwscanf_s.c   wcstok_s.c
print.c             sprintf_s.c            vscanf_s.c     wmemcpy_s.c
prt_reset_vector.S  sscanf_s.c             vsnprintf_s.c  wmemmove_s.c
scanf_s.c           start.S                vsprintf_s.c   wscanf_s.c
)
add_library(bsp OBJECT ${SRCS})  # OBJECT类型只编译生成.o目标文件，但不实际链接成库