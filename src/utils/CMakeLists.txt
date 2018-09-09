file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/include/utils/path_monitor.hpp
    main.cpp
)

add_executable(utils_tester ${SRCS})