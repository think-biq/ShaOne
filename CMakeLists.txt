CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (ShaOne)

file (GLOB ShaOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
file (GLOB ShaOne_ThirdParty_SRC
	"${PROJECT_SOURCE_DIR}/third-party/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/third-party")
add_library(ShaOne ${ShaOnce_SRC} ${ShaOne_ThirdParty_SRC})

if(ShaOne_WithTest)	
	string(
	    COMPARE EQUAL
	    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
	    IS_STANDALON_PROJECT
	)

	if (IS_STANDALON_PROJECT)
		add_subdirectory(third-party/testly)
		include_directories(third-party/testly/src)
	else()
		if (NOT Testly_DIR)
			message(FATAL_ERROR "Could not find Testly in 'Testly_DIR'.")
		endif()
	endif()

	file(GLOB ShaOne_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (ShaOneTest ${ShaOne_Test_SRC})
	target_link_libraries(ShaOneTest ShaOne Testly)
endif()