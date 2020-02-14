#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#######################################################################
# Find all necessary and optional OGRE dependencies
#######################################################################

# OGRE_DEPENDENCIES_DIR can be used to specify a single base
# folder where the required dependencies may be found.
set(OGRE_DEPENDENCIES_DIR "" CACHE PATH "Path to prebuilt OGRE dependencies")
option(OGRE_BUILD_DEPENDENCIES "automatically build Ogre Dependencies (freetype, zzip)" TRUE)

include(FindPkgMacros)
getenv_path(OGRE_DEPENDENCIES_DIR)
if(OGRE_BUILD_PLATFORM_EMSCRIPTEN)
  set(OGRE_DEP_SEARCH_PATH
    ${OGRE_DEPENDENCIES_DIR}
    ${EMSCRIPTEN_ROOT_PATH}/system
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${PROJECT_BINARY_DIR}/EmscriptenDependencies"
    "${PROJECT_SOURCE_DIR}/EmscriptenDependencies"
    "${PROJECT_BINARY_DIR}/../EmscriptenDependencies"
    "${PROJECT_SOURCE_DIR}/../EmscriptenDependencies"
  )
elseif(APPLE_IOS)
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${PROJECT_BINARY_DIR}/iOSDependencies"
    "${PROJECT_SOURCE_DIR}/iOSDependencies"
    "${PROJECT_BINARY_DIR}/../iOSDependencies"
    "${PROJECT_SOURCE_DIR}/../iOSDependencies"
  )
elseif(OGRE_BUILD_PLATFORM_ANDROID)
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${PROJECT_BINARY_DIR}/AndroidDependencies"
    "${PROJECT_SOURCE_DIR}/AndroidDependencies"
    "${PROJECT_BINARY_DIR}/../AndroidDependencies"
    "${PROJECT_SOURCE_DIR}/../AndroidDependencies"
  )
else()
  set(OGRE_DEP_SEARCH_PATH 
    ${OGRE_DEPENDENCIES_DIR}
    ${ENV_OGRE_DEPENDENCIES_DIR}
    "${PROJECT_BINARY_DIR}/Dependencies"
    "${PROJECT_SOURCE_DIR}/Dependencies"
    "${PROJECT_BINARY_DIR}/../Dependencies"
    "${PROJECT_SOURCE_DIR}/../Dependencies"
  )
endif()

message(STATUS "Search path: ${OGRE_DEP_SEARCH_PATH}")
list(GET OGRE_DEP_SEARCH_PATH 0 OGREDEPS_PATH)

if(CMAKE_CROSSCOMPILING)
    set(CMAKE_FIND_ROOT_PATH ${OGREDEPS_PATH} "${CMAKE_FIND_ROOT_PATH}")

    set(CROSS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
    
    if(ANDROID)
        set(CROSS ${CROSS}
            -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
            -DANDROID_ABI=${ANDROID_ABI}
            -DANDROID_NDK=${ANDROID_NDK})
    endif()
    
    if(APPLE_IOS)
        set(CROSS ${CROSS}
            -DIOS_PLATFORM=${IOS_PLATFORM})
    else()
        # this should help discovering zlib, but on ios it breaks it
        set(CROSS ${CROSS}
            -DCMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH})
    endif()
endif()

set(OGREDEPS_SHARED TRUE)
if(OGRE_STATIC OR MSVC)
    # freetype does not like shared build on MSVC and it generally eases distribution there
    set(OGREDEPS_SHARED FALSE)
endif()

set(BUILD_COMMAND_OPTS --target install --config ${CMAKE_BUILD_TYPE})

set(BUILD_COMMAND_COMMON ${CMAKE_COMMAND}
  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  -DCMAKE_INSTALL_PREFIX=${OGREDEPS_PATH}
  -G ${CMAKE_GENERATOR}
  -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM}
  -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
  ${CROSS})

# Set hardcoded path guesses for various platforms
if (UNIX AND NOT EMSCRIPTEN)
  set(OGRE_DEP_SEARCH_PATH ${OGRE_DEP_SEARCH_PATH} /usr/local)
  # Ubuntu 11.10 has an inconvenient path to OpenGL libraries
  set(OGRE_DEP_SEARCH_PATH ${OGRE_DEP_SEARCH_PATH} /usr/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu)
endif ()

# give guesses as hints to the find_package calls
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${OGRE_DEP_SEARCH_PATH})
set(CMAKE_FRAMEWORK_PATH ${CMAKE_FRAMEWORK_PATH} ${OGRE_DEP_SEARCH_PATH})

if(OGRE_BUILD_DEPENDENCIES AND NOT EXISTS ${OGREDEPS_PATH})
    if(MSVC OR EMSCRIPTEN OR MINGW) # other platforms ship zlib
        message(STATUS "Building zlib")
        file(DOWNLOAD 
            http://zlib.net/zlib-1.2.11.tar.gz
            ${PROJECT_BINARY_DIR}/zlib-1.2.11.tar.gz 
            EXPECTED_MD5 1c9f62f0778697a09d36121ead88e08e)
        execute_process(COMMAND ${CMAKE_COMMAND} 
            -E tar xf zlib-1.2.11.tar.gz WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
        execute_process(COMMAND ${BUILD_COMMAND_COMMON}
            -DBUILD_SHARED_LIBS=${OGREDEPS_SHARED}
            ${PROJECT_BINARY_DIR}/zlib-1.2.11
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/zlib-1.2.11)
        execute_process(COMMAND ${CMAKE_COMMAND} 
            --build ${PROJECT_BINARY_DIR}/zlib-1.2.11 ${BUILD_COMMAND_OPTS})
    endif()

    message(STATUS "Building ZZIPlib")
    file(DOWNLOAD
        https://github.com/gdraheim/zziplib/archive/develop.zip
        ${PROJECT_BINARY_DIR}/zziplib-develop.tar.gz)
    execute_process(COMMAND ${CMAKE_COMMAND}
        -E tar xf zziplib-develop.tar.gz WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
    execute_process(COMMAND ${BUILD_COMMAND_COMMON}
        -DZLIB_ROOT=${OGREDEPS_PATH}
        -DZZIPMMAPPED=OFF -DZZIPCOMPAT=OFF -DZZIPLIBTOOL=OFF -DZZIPFSEEKO=OFF -DZZIPWRAP=OFF -DZZIPSDL=OFF -DZZIPBINS=OFF -DZZIPTEST=OFF -DZZIPDOCS=OFF -DBASH=sh
        -DBUILD_STATIC_LIBS=TRUE
        -DBUILD_SHARED_LIBS=${OGREDEPS_SHARED}
        ${PROJECT_BINARY_DIR}/zziplib-develop
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/zziplib-develop)
    execute_process(COMMAND ${CMAKE_COMMAND} 
        --build ${PROJECT_BINARY_DIR}/zziplib-develop ${BUILD_COMMAND_OPTS})

    message(STATUS "Building pugixml")
    file(DOWNLOAD
        https://github.com/zeux/pugixml/releases/download/v1.10/pugixml-1.10.tar.gz
        ${PROJECT_BINARY_DIR}/pugixml-1.10.tar.gz)
    execute_process(COMMAND ${CMAKE_COMMAND}
        -E tar xf pugixml-1.10.tar.gz WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
    execute_process(COMMAND ${BUILD_COMMAND_COMMON}
        -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE # this will be linked into a shared lib
        ${PROJECT_BINARY_DIR}/pugixml-1.10
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/pugixml-1.10)
    execute_process(COMMAND ${CMAKE_COMMAND}
        --build ${PROJECT_BINARY_DIR}/pugixml-1.10 ${BUILD_COMMAND_OPTS})

    find_package(Freetype)
    if (NOT FREETYPE_FOUND)
        message(STATUS "Building freetype")
        file(DOWNLOAD
            https://download.savannah.gnu.org/releases/freetype/freetype-2.9.tar.gz
            ${PROJECT_BINARY_DIR}/freetype-2.9.tar.gz)
        execute_process(COMMAND ${CMAKE_COMMAND}
            -E tar xf freetype-2.9.tar.gz WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
        # patch toolchain for iOS
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/CMake/toolchain/ios.toolchain.xcode.cmake
            freetype-2.9/builds/cmake/iOS.cmake
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
        execute_process(COMMAND ${BUILD_COMMAND_COMMON}
            -DBUILD_SHARED_LIBS=${OGREDEPS_SHARED}
            -DWITH_PNG=OFF
            -DWITH_BZip2=OFF # tries to use it on iOS otherwise
            # workaround for broken iOS toolchain in freetype
            -DPROJECT_SOURCE_DIR=${PROJECT_BINARY_DIR}/freetype-2.9
            ${PROJECT_BINARY_DIR}/freetype-2.9
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/freetype-2.9/objs)
        execute_process(COMMAND ${CMAKE_COMMAND}
            --build ${PROJECT_BINARY_DIR}/freetype-2.9/objs ${BUILD_COMMAND_OPTS})
    endif()

    if(MSVC OR MINGW) # other platforms dont need this
        message(STATUS "Building SDL2")
        file(DOWNLOAD
            https://libsdl.org/release/SDL2-2.0.8.tar.gz
            ${PROJECT_BINARY_DIR}/SDL2-2.0.8.tar.gz)
        execute_process(COMMAND ${CMAKE_COMMAND} 
            -E tar xf SDL2-2.0.8.tar.gz WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
        execute_process(COMMAND ${CMAKE_COMMAND}
            -E make_directory ${PROJECT_BINARY_DIR}/SDL2-build)
        execute_process(COMMAND ${BUILD_COMMAND_COMMON}
            -DSDL_STATIC=FALSE
            ${PROJECT_BINARY_DIR}/SDL2-2.0.8
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/SDL2-build)
        execute_process(COMMAND ${CMAKE_COMMAND}
            --build ${PROJECT_BINARY_DIR}/SDL2-build ${BUILD_COMMAND_OPTS})
    endif()
endif()

#######################################################################
# Core dependencies
#######################################################################

# Find zlib
find_package(ZLIB)
macro_log_feature(ZLIB_FOUND "zlib" "Simple data compression library" "http://www.zlib.net" FALSE "" "")

if (ZLIB_FOUND)
  # Find zziplib
  find_package(ZZip)
  macro_log_feature(ZZip_FOUND "zziplib" "Extract data from zip archives" "http://zziplib.sourceforge.net" FALSE "" "")
endif ()

# Find FreeImage
find_package(FreeImage)
macro_log_feature(FreeImage_FOUND "freeimage" "Support for commonly used graphics image formats" "http://freeimage.sourceforge.net" FALSE "" "")

# Find FreeType
find_package(Freetype)
macro_log_feature(FREETYPE_FOUND "freetype" "Portable font engine" "http://www.freetype.org" FALSE "" "")

# Find X11
if (UNIX AND NOT APPLE AND NOT ANDROID AND NOT EMSCRIPTEN)
  find_package(X11)
  macro_log_feature(X11_FOUND "X11" "X Window system" "http://www.x.org" TRUE "" "")
endif ()


#######################################################################
# RenderSystem dependencies
#######################################################################

# Find OpenGL
if(NOT ANDROID AND NOT EMSCRIPTEN)
  find_package(OpenGL)
  macro_log_feature(OPENGL_FOUND "OpenGL" "Support for the OpenGL and OpenGL 3+ render systems" "http://www.opengl.org/" FALSE "" "")
endif()

# Find OpenGL ES 2.x
find_package(OpenGLES2)
macro_log_feature(OPENGLES2_FOUND "OpenGL ES 2.x" "Support for the OpenGL ES 2.x render system" "http://www.khronos.org/opengles/" FALSE "" "")

# Find DirectX
if(WIN32)
	find_package(DirectX)
	macro_log_feature(DirectX9_FOUND "DirectX9" "Support for the DirectX render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")
	
	find_package(DirectX11)
	macro_log_feature(DirectX11_FOUND "DirectX11" "Support for the DirectX11 render system" "http://msdn.microsoft.com/en-us/directx/" FALSE "" "")

	if(OGRE_CONFIG_ENABLE_QUAD_BUFFER_STEREO)
		# Find DirectX Stereo Driver Libraries
		find_package(NVAPI)
		macro_log_feature(NVAPI_FOUND "NVAPI" "Support NVIDIA stereo with the DirectX render system" "https://developer.nvidia.com/nvapi" FALSE "" "")

		find_package(AMDQBS)
		macro_log_feature(AMDQBS_FOUND "AMDQBS" "Support AMD stereo with the DirectX render system" "http://developer.amd.com/tools-and-sdks/graphics-development/amd-quad-buffer-sdk/" FALSE "" "")
	endif()
endif()

#######################################################################
# Additional features
#######################################################################

# Find Cg
if (NOT (APPLE_IOS OR WINDOWS_STORE OR WINDOWS_PHONE OR ANDROID OR EMSCRIPTEN))
  find_package(Cg)
  macro_log_feature(Cg_FOUND "cg" "C for graphics shader language" "http://developer.nvidia.com/object/cg_toolkit.html" FALSE "" "")
endif ()

# OpenEXR
find_package(OpenEXR)
macro_log_feature(OPENEXR_FOUND "OpenEXR" "Load High dynamic range images" "http://www.openexr.com/" FALSE "" "")

# Python
set(Python_ADDITIONAL_VERSIONS 3.4) # allows using python3 on Ubuntu 14.04
find_package(PythonInterp)
find_package(PythonLibs)
macro_log_feature(PYTHONLIBS_FOUND "Python" "Language bindings to use OGRE from Python" "http://www.python.org/" FALSE "" "")

#######################################################################
# Samples dependencies
#######################################################################

# Find sdl2
if(NOT ANDROID AND NOT EMSCRIPTEN)
  # find script does not work in cross compilation environment
  find_package(SDL2)
  macro_log_feature(SDL2_FOUND "SDL2" "Simple DirectMedia Library needed for input handling in samples" "https://www.libsdl.org/" FALSE "" "")
  if(SDL2_FOUND AND WIN32 AND NOT SDL2_BINARY)
    # fix linking static SDL2 on windows
    set(SDL2_LIBRARY ${SDL2_LIBRARY} winmm.lib imm32.lib version.lib)
  endif()
endif()

#######################################################################
# Tools
#######################################################################

find_package(Doxygen)
macro_log_feature(DOXYGEN_FOUND "Doxygen" "Tool for building API documentation" "http://doxygen.org" FALSE "" "")

# Find Softimage SDK
find_package(Softimage)
macro_log_feature(Softimage_FOUND "Softimage" "Softimage SDK needed for building XSIExporter" FALSE "6.0" "")

#######################################################################
# Tests
#######################################################################

# now see if we have a buildable Dependencies package in
# the source tree. If so, include that, and it will take care of
# setting everything up, including overriding any of the above
# findings.
set(OGREDEPS_RUNTIME_OUTPUT ${OGRE_RUNTIME_OUTPUT})
if (EXISTS "${PROJECT_SOURCE_DIR}/Dependencies/CMakeLists.txt")
  add_subdirectory(Dependencies)
elseif (EXISTS "${PROJECT_SOURCE_DIR}/ogredeps/CMakeLists.txt")
  add_subdirectory(ogredeps)
endif ()

# provide option to install dependencies on Windows
include(InstallDependencies)
