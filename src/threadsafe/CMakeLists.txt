file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/include/threadsafe/ts_queue.hpp
    ${PROJECT_SOURCE_DIR}/include/threadsafe/ts_stack.hpp
    main.cpp
)

add_executable(threadsafe_tester ${SRCS})