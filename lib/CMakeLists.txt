add_library( Region Region.cxx Region.h )
target_include_directories( Region PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( JSEG JSEG.cxx JSEG.h )
target_include_directories( JSEG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( JSEG LINK_PUBLIC Region )
