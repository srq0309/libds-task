file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/include/threadsafe/tf_queue.hpp
    ${PROJECT_SOURCE_DIR}/include/threadsafe/tf_stack.hpp
    ${PROJECT_SOURCE_DIR}/include/threadsafe/lf_queue.hpp
	${PROJECT_SOURCE_DIR}/include/threadsafe/lf_stack.hpp
    main.cpp
)

add_executable(threadsafe_tester ${SRCS})