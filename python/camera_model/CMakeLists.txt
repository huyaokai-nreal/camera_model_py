find_package(Eigen3 REQUIRED)
set(PYTHON_VERSION 3.10)
set(Python_EXECUTABLE "/usr/bin/python${PYTHON_VERSION}")
find_package(Python ${PYTHON_VERSION} COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)
find_package(camera_model REQUIRED)
include_directories(${camera_model_INCLUDE_DIRS})
set(target_name _pycamera_model)
pybind11_add_module(${target_name} camera_model.cpp)
target_link_libraries(${target_name} PRIVATE  Eigen3::Eigen camera_model::camera_model)
set_target_properties(${target_name} PROPERTIES  
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
