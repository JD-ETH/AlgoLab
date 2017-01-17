# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( snippets_ )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "cancer_therapy.cpp" )
  create_single_source_cgal_program( "investment.cpp" )
  create_single_source_cgal_program( "minimize.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

