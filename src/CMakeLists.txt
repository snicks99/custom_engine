if(DBO_SERVER)
    if(WIN32 AND MSVC)
      set(sources_windows
        ${CMAKE_SOURCE_DIR}/src/Base/Debug/WheatyExceptionReport.cpp
        ${CMAKE_SOURCE_DIR}/src/Base/Debug/WheatyExceptionReport.h
      )
    endif()
endif()

add_subdirectory(Base)
add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(GlassCannon)