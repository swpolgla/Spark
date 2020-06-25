project("SparkCalc")

cmake_minimum_required(VERSION "3.17.3")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets COMPONENTS core base richtext REQUIRED)

include(${wxWidgets_USE_FILE})

add_executable( "${PROJECT_NAME}" 
		"src/minimal.cpp"
		"src/SparkCalc.cpp"
		"src/SparkUI.cpp"
		"src/operation-tree/OperationTree.cpp"
		"src/operation-tree/nodes/OperationNode.cpp"
		"src/operation-tree/nodes/MathNode.cpp"
		"src/operation-tree/nodes/ValueNode.cpp"
		)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
