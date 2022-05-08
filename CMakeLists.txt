CMAKE_MINIMUM_REQUIRED (VERSION 3.20)

project (ShaOne)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
endif()
	
string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

file (GLOB ShaOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src")
if(BUILD_SHARED_LIBS)
add_library(ShaOne SHARED ${ShaOnce_SRC})
else()
add_library(ShaOne ${ShaOnce_SRC})
endif()
target_include_directories(
    ShaOne PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
)
#target_link_libraries(ShaOne bsd)
set_property(TARGET ShaOne PROPERTY C_STANDARD 11)

install(
    TARGETS ShaOne
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/src"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

if(ShaOne_WithTest)
	if (IS_STANDALON_PROJECT)
		add_subdirectory(third-party/testly)
		include_directories(third-party/testly/src)
	else()
		find_package(Testly)
	endif()

	file(GLOB ShaOne_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (ShaOneTest ${ShaOne_Test_SRC})
	target_include_directories(ShaOneTest PUBLIC
	  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
	)
	target_link_libraries(ShaOneTest ShaOne Testly)
endif()