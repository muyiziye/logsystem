project(ut)

include_directories(
    .
    ${SRC_PATH}/lib/
)

set(${PROJECT_NAME}_SRC
    main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

add_executable(${PROJECT_NAME}_static ${${PROJECT_NAME}_SRC})


target_link_libraries(${PROJECT_NAME} logsystem)

target_link_libraries(${PROJECT_NAME}_static logsystem_static)

install(
    TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static
    DESTINATION ${OUTPUT_PATH}
)
