project("SparkCalc")

cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.3)
endif()

set(wxWidgets_USE_STATIC TRUE)
find_package(wxWidgets COMPONENTS core base richtext html xml REQUIRED)

include(${wxWidgets_USE_FILE})

if(WIN32)
add_executable( "${PROJECT_NAME}"
		WIN32
		"src/minimal.cpp"
		"src/SparkCalc.cpp"
		"src/SparkUI.cpp"
		"src/operation-tree/OperationTree.cpp"
		"src/operation-tree/nodes/OperationNode.cpp"
		"src/operation-tree/nodes/MathNode.cpp"
		"src/operation-tree/nodes/ValueNode.cpp"
		)
else()
add_executable( "${PROJECT_NAME}" 
		"src/minimal.cpp"
		"src/SparkCalc.cpp"
		"src/SparkUI.cpp"
		"src/operation-tree/OperationTree.cpp"
		"src/operation-tree/nodes/OperationNode.cpp"
		"src/operation-tree/nodes/MathNode.cpp"
		"src/operation-tree/nodes/ValueNode.cpp"
		)
endif()

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
