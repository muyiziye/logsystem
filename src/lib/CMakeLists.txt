project(logsystem)

include_directories(
    .
)

set(${PROJECT_NAME}_SRC
    logSystem.cpp
)


add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SRC})
add_library(${PROJECT_NAME}_static STATIC ${${PROJECT_NAME}_SRC})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static
        DESTINATION ${OUTPUT_PATH}/lib/
)

install(FILES logSystem.hpp
        DESTINATION ${OUTPUT_PATH}/include/
)
