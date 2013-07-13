if (NOT DEFINED DEFAULT_C_FLAGS_SET OR RESET_FLAGS)

  if(CMAKE_C_COMPILER_ID MATCHES GNU)
    set(CMAKE_C_FLAGS         "-std=c99 -DRESTRICT=restrict -DFUNDERSCORE=1 -fPIC")
    set(CMAKE_C_FLAGS_DEBUG   "-O0 -g3 -Wall")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -ffast-math -funroll-loops -ftree-vectorize -Wno-unused")
  endif()
  
  if(CMAKE_C_COMPILER_ID MATCHES Intel)
    set(CMAKE_C_FLAGS         "-g -vec-report0 -restrict -DRESTRICT=restrict -std=c99 -fPIC")
    set(CMAKE_C_FLAGS_DEBUG   "-O0 -g -w3 -vec-report")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -ip")
    set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -shared-intel -fPIC")
  endif()
  
  if(CMAKE_C_COMPILER_ID MATCHES PGI)
    set(CMAKE_C_FLAGS         "-g")
    set(CMAKE_C_FLAGS_DEBUG   "-O0")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -fast -Munroll -Mvect=idiom -c9x -DRESTRICT=restrict")
  endif()
  
  if(CMAKE_C_COMPILER_ID MATCHES XL)
    set(CMAKE_C_FLAGS         "-qcpluscmt")
    set(CMAKE_C_FLAGS_DEBUG   " ")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
  endif()

  save_compiler_flags(C)

endif()