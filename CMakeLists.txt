project("SparkCalc")

cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT")
	set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/spark.rc")
	set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.5)
endif()

# wxWidgets Setup
set(wxWidgets_USE_STATIC TRUE)
find_package(wxWidgets COMPONENTS core base richtext html xml REQUIRED)

include(${wxWidgets_USE_FILE})
include(sourcelist.cmake)

if(WIN32)
	add_executable("${PROJECT_NAME}" WIN32 "${sources}" ${APP_ICON_RESOURCE_WINDOWS})
else()
	add_executable("${PROJECT_NAME}" "${sources}")
endif()

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
