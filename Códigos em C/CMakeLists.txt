project(IC_2024 C)

add_executable(ETS ETS.c)
target_link_libraries(ETS m)

add_executable(NLLS NLLS.c)
target_link_libraries(NLLS m)

add_executable(functions.so functions.c)
target_link_libraries(functions.so m)

add_executable(functions.dll functions.c)
target_link_libraries(functions.dll m)

add_executable(teste teste.c)