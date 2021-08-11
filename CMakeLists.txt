CMAKE_MINIMUM_REQUIRED (VERSION 3.20)

project (ShaOne)
	
string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

file (GLOB ShaOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
file (GLOB ShaOne_ThirdParty_SRC
	"${PROJECT_SOURCE_DIR}/third-party/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/third-party")
add_library(ShaOne ${ShaOnce_SRC} ${ShaOne_ThirdParty_SRC})
target_include_directories(
    ShaOne PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
)

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