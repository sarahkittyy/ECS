# https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(res "${CMAKE_SOURCE_DIR}/tests")
foreach(dir ${res})
	file(GLOB_RECURSE sources "${dir}/*.cpp")
	add_executable(${dir} ${sources})
	add_dependencies(${dir} ecs)
	target_include_directories(${dir} PUBLIC ${dir})
	target_link_libraries(${dir} ecs)
endforeach()