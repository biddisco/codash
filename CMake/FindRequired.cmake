
# generated by Buildyard, do not edit. Sets FOUND_REQUIRED if all required
# dependencies are found. Used by Buildyard.cmake
set(FIND_REQUIRED_FAILED)
find_package(dash 1.1.0 QUIET)
if(NOT dash_FOUND AND NOT DASH_FOUND)
  set(FIND_REQUIRED_FAILED "${FIND_REQUIRED_FAILED} dash")
endif()
find_package(Collage 1.1.0 QUIET)
if(NOT Collage_FOUND AND NOT COLLAGE_FOUND)
  set(FIND_REQUIRED_FAILED "${FIND_REQUIRED_FAILED} Collage")
endif()
find_package(Boost 1.41.0 COMPONENTS program_options serialization QUIET)
if(NOT Boost_FOUND AND NOT BOOST_FOUND)
  set(FIND_REQUIRED_FAILED "${FIND_REQUIRED_FAILED} Boost")
endif()
if(FIND_REQUIRED_FAILED)
  set(FOUND_REQUIRED FALSE)
else()
  set(FOUND_REQUIRED TRUE)
endif()
