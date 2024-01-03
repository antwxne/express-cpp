include(FetchContent)

FetchContent_Declare(picohttpparser
        GIT_REPOSITORY https://github.com/h2o/picohttpparser.git
        GIT_TAG master
)
FetchContent_GetProperties(picohttpparser)
if (NOT picohttpparser_POPULATED)
    FetchContent_Populate(picohttpparser)
endif ()
add_library(picohttpparser ${picohttpparser_SOURCE_DIR}/picohttpparser.c)
target_include_directories(picohttpparser INTERFACE ${picohttpparser_SOURCE_DIR}/)
