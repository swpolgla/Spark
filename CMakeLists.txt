project("SparkCalc")

cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.5)
endif()

# wxWidgets Setup
set(wxWidgets_USE_STATIC TRUE)
find_package(wxWidgets COMPONENTS core base richtext html xml REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT")

include(${wxWidgets_USE_FILE})
include(sourcelist.cmake)

if(WIN32)
	add_executable("${PROJECT_NAME}" WIN32 "${sources}")
else()
	add_executable("${PROJECT_NAME}" "${sources}")
endif()

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
