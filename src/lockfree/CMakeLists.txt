file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/include/lockfree/lf_queue.hpp
	${PROJECT_SOURCE_DIR}/include/lockfree/lf_stack.hpp
    main.cpp
)

add_executable(lockfree_tester ${SRCS})