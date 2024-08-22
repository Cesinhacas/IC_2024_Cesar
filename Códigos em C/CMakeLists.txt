project(IC_2024 C)

add_executable(ETS ETS.c)
target_link_libraries(ETS m)

add_executable(NLLS NLLS.c)
target_link_libraries(NLLS m)

add_executable(execution_time_NLLS execution_time_NLLS.c)
target_link_libraries(execution_time_NLLS m)

add_executable(execution_time_ETS execution_time_ETS.c)
target_link_libraries(execution_time_ETS m)


add_executable(teste teste.c)