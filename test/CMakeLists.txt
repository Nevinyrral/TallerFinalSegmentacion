add_executable( jseg_test test.cxx )
target_link_libraries( jseg_test LINK_PUBLIC JSEG ${OpenCV_LIBS} )
