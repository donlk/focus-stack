cmake_minimum_required(VERSION 2.8)
 
PROJECT(focus-stack)

set(CMAKE_CXX_STANDARD 17)

# ===================================================================
# Build options
# ===================================================================
OPTION(BUILD_TESTS "Build tests." ON)

# ===================================================================
# Sources
# ===================================================================
file(GLOB_RECURSE
    LIB_SOURCES
    "src/focusstack.cc"
    "src/worker.cc"
    "src/options.cc"
    "src/logger.cc"
    "src/radialfilter.cc"
    "src/histogrampercentile.cc"
    "src/task_3dpreview.cc"
    "src/task_align.cc"
    "src/task_denoise.cc"
    "src/task_depthmap.cc"
    "src/task_depthmap_inpaint.cc"
    "src/task_focusmeasure.cc"
    "src/task_grayscale.cc"
    "src/task_loadimg.cc"
    "src/task_merge.cc"
    "src/task_reassign.cc"
    "src/task_saveimg.cc"
    "src/task_wavelet.cc"
    "src/task_wavelet_opencl.cc"
)

file(GLOB_RECURSE
    BIN_SOURCE
    "src/main.cc"
)

file(GLOB_RECURSE
    TEST_SOURCES
    "src/gtest_main.cc"
    "src/task_grayscale_tests.cc"
    "src/task_wavelet_tests.cc"
    "src/task_wavelet_opencl_tests.cc"
    "src/radialfilter_tests.cc"
)

file(GLOB
    headers
    "src/*.hh"
)
 
# ===================================================================
# External dependencies
# ===================================================================

set(
    REQUIRED_OPENCV_LIBS
    opencv_video
    opencv_imgcodecs
    opencv_photo
    opencv_imgproc
    opencv_core
)
find_package(
    OpenCV REQUIRED
    ${REQUIRED_OPENCV_LIBS}
)
find_package(OpenMP)

# ===================================================================
# Use OpenMP if available
# ===================================================================
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    option(USE_OPENMP "Use OpenMP for parallelization" ON)
    add_definitions(-DUSE_OPENMP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
endif(OPENMP_FOUND)

# ===================================================================
# Build
# ===================================================================
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_library(focus_stack ${LIB_SOURCES})
add_executable(focus_stack_main ${BIN_SOURCE})
target_link_libraries(
    focus_stack_main
    focus_stack
    ${REQUIRED_OPENCV_LIBS}
)

# ===================================================================
# Build
# ===================================================================
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIR})
    add_executable(focus_stack_test ${TEST_SOURCES})
    target_link_libraries(focus_stack_test focus_stack GTest::GTest GTest::Main ${REQUIRED_OPENCV_LIBS})
endif()

# ===================================================================
# Install
# ===================================================================
install(TARGETS focus_stack DESTINATION lib)
install(TARGETS focus_stack_main DESTINATION bin)
