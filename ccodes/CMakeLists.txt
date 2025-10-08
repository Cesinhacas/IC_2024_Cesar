cmake_minimum_required(VERSION 3.30.2)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_BUILD_TYPE Debug)  # Define o modo de depuração
set(CMAKE_C_FLAGS_DEBUG "-g -O0")  # Flags para GCC no modo Debug

project(IC_2024 C)

add_executable(ETS ETS.c)
target_link_libraries(ETS m)

add_executable(NLLS NLLS.c)
target_link_libraries(NLLS m)

add_executable(NLLS2 NLLS2.c)
target_link_libraries(NLLS2 m)

add_executable(TWOSTEP TWOSTEP.c)
target_link_libraries(TWOSTEP m)

add_executable(functions.so functions.c)
target_link_libraries(functions.so m)

add_executable(functions.dll functions.c)
target_link_libraries(functions.dll m)

add_executable(functions_64.so functions_64.c)
target_link_libraries(functions_64.so m)

# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

#cmake_minimum_required(VERSION 3.30.3)
#project(IC_2024 C)

# Pega todos os arquivos .c no diretório atual
#file(GLOB SOURCES "*.c")

# Para cada arquivo fonte, cria um executável separado
#foreach(SOURCE_FILE ${SOURCES})
    # Obtém o nome do arquivo sem o caminho e a extensão
 #   get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)

    # Cria um executável com o nome baseado no arquivo .c
  #  add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
#endforeach()

