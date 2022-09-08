# This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

CollectSourceFiles(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE_SOURCES
  # Exclude
  ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

list(APPEND PRIVATE_SOURCES ${sources_windows})

if(WIN32)
  if(MSVC)
    list(APPEND PRIVATE_SOURCES Client.rc)
  endif()
endif()

if(USE_COREPCH)
  set(PRIVATE_PCH_HEADER PrecompiledHeaders/clientPCH.h)
endif()

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${DBO_LINK_DIRECTORIES})

add_executable(Client WIN32
  ${PRIVATE_SOURCES}
)

if(OPTIONS_BUILD_TARGET)
	add_compile_definitions(BUILD_TARGET=${OPTIONS_BUILD_TARGET})
endif()

if(OPTIONS_COMMAND_ARGUMENTS)
	set_target_properties(Client PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS ${OPTIONS_COMMAND_ARGUMENTS})
endif()

if(DBO_CLIENT_DIR)
	set_target_properties(Client PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${DBO_CLIENT_DIR}")
	set_target_properties(Client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${DBO_CLIENT_DIR}")
	set_target_properties(Client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${DBO_CLIENT_DIR}")
endif()

target_link_libraries(Client
  PRIVATE
    trinity-core-interface
  PUBLIC
    Presentation

    debug OptickCored.lib optimized OptickCore.lib

    # Render libraries
    ddraw.lib
    Ws2_32.lib
    Winmm.lib
    Imm32.lib

    d3dx9.lib
    d3d9.lib

    # RenderWare libraries
    # rwcore.lib
    rtdict.lib
    rtcharse.lib
    rtfsyst.lib
    rtbmp.lib
    rtpng.lib
    rtintsec.lib
    rtpick.lib
    # rttoc.lib
    # rpworld.lib
    rtanim.lib
    rphanim.lib
    rtquat.lib
    # rplogo.lib
    rpusrdat.lib
    rpid.lib
    rpmatfx.lib
    rpuvanim.lib
    rpprtstd.lib
    rpprtadv.lib
    rpptank.lib
    rpskintoon.lib
    rprandom.lib
    rtimport.lib
    rtgcond.lib
    rtwing.lib
    rtray.lib
    # rplodatm.lib
    rppvs.lib
    rpltmap.lib
    rtltmap.lib
    rpmipkl.lib
    # rtpitexd.lib
    rtbary.lib
)

CollectIncludeDirectories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC_INCLUDES
  # Exclude
  ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

target_include_directories(Client
  PUBLIC
    ${PUBLIC_INCLUDES}
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(Client
    PROPERTIES
      FOLDER
        "DBO")

# Add all dynamic projects as dependency to the Client
if(WORLDSERVER_DYNAMIC_SCRIPT_MODULES_DEPENDENCIES)
  add_dependencies(Client ${WORLDSERVER_DYNAMIC_SCRIPT_MODULES_DEPENDENCIES})
endif()

# Generate precompiled header
if(USE_COREPCH)
  add_cxx_pch(Client ${PRIVATE_PCH_HEADER})
endif()
