message("--- debugTarget ---")

#
# First we define 3 sets of properties for targets, sources and directories
# 
# then we define the function debugTarget
# 

set(_target_properties
ALIASED_TARGET
BINARY_DIR
BUILD_RPATH
BUNDLE_EXTENSION
BUNDLE
C_EXTENSIONS
C_STANDARD
C_STANDARD_REQUIRED
COMPATIBLE_INTERFACE_BOOL
COMPATIBLE_INTERFACE_NUMBER_MAX
COMPATIBLE_INTERFACE_NUMBER_MIN
COMPATIBLE_INTERFACE_STRING
COMPILE_DEFINITIONS
COMPILE_DEFINITIONS_RELEASE
COMPILE_DEFINITIONS_DEBUG
COMPILE_FEATURES
COMPILE_FLAGS
COMPILE_OPTIONS
COMPILE_PDB_NAME
CXX_EXTENSIONS
CXX_STANDARD
CXX_STANDARD_REQUIRED
DEBUG_POSTFIX
DEFINE_SYMBOL
DEPLOYMENT_REMOTE_DIRECTORY
EchoString
ENABLE_EXPORTS
EXCLUDE_FROM_ALL
EXCLUDE_FROM_DEFAULT_BUILD
EXPORT_NAME
FOLDER
FRAMEWORK
FRAMEWORK_VERSION
GENERATOR_FILE_NAME
IMPORTED
INCLUDE_DIRECTORIES
INSTALL_NAME_DIR
INSTALL_RPATH
INSTALL_RPATH_USE_LINK_PATH
INTERFACE_AUTOUIC_OPTIONS
INTERFACE_COMPILE_DEFINITIONS
INTERFACE_COMPILE_FEATURES
INTERFACE_COMPILE_OPTIONS
INTERFACE_INCLUDE_DIRECTORIES
INTERFACE_LINK_LIBRARIES
INTERFACE_POSITION_INDEPENDENT_CODE
INTERFACE_SOURCES
INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
INTERPROCEDURAL_OPTIMIZATION
LABELS
LIBRARY_OUTPUT_DIRECTORY
LIBRARY_OUTPUT_NAME
LINK_DEPENDS_NO_SHARED
LINK_DEPENDS
LINKER_LANGUAGE
LINK_FLAGS
LINK_INTERFACE_LIBRARIES
LINK_INTERFACE_MULTIPLICITY
LINK_LIBRARIES
LINK_SEARCH_END_STATIC
LINK_SEARCH_START_STATIC
LINK_WHAT_YOU_USE
MANUALLY_ADDED_DEPENDENCIES
NAME
NO_SONAME
NO_SYSTEM_FROM_IMPORTED
OUTPUT_NAME
POSITION_INDEPENDENT_CODE
PREFIX
PRIVATE_HEADER
PROJECT_LABEL
PUBLIC_HEADER
RESOURCE
RULE_LAUNCH_COMPILE
RULE_LAUNCH_CUSTOM
RULE_LAUNCH_LINK
RUNTIME_OUTPUT_DIRECTORY
RUNTIME_OUTPUT_NAME
SKIP_BUILD_RPATH
SOURCE_DIR
SOURCES
SOVERSION
STATIC_LIBRARY_FLAGS
SUFFIX
TYPE
VERSION
VISIBILITY_INLINES_HIDDEN
WIN32_EXECUTABLE
)

set(_source_properties
ABSTRACT
AUTOUIC_OPTIONS
AUTORCC_OPTIONS
COMPILE_DEFINITIONS
COMPILE_DEFINITIONS_RELEASE
COMPILE_DEFINITIONS_DEBUG
COMPILE_FLAGS
EXTERNAL_OBJECT
Fortran_FORMAT
GENERATED
HEADER_FILE_ONLY
KEEP_EXTENSION
LABELS
LANGUAGE
LOCATION
MACOSX_PACKAGE_LOCATION
OBJECT_DEPENDS
OBJECT_OUTPUTS
SKIP_AUTOGEN
SKIP_AUTOMOC
SKIP_AUTORCC
SKIP_AUTOUIC
SYMBOLIC
VS_COPY_TO_OUT_DIR
VS_DEPLOYMENT_CONTENT
VS_DEPLOYMENT_LOCATION
VS_INCLUDE_IN_VSIX
VS_RESOURCE_GENERATOR
VS_SHADER_ENTRYPOINT
VS_SHADER_FLAGS
VS_SHADER_MODEL
VS_SHADER_TYPE
VS_TOOL_OVERRIDE
VS_XAML_TYPE
WRAP_EXCLUDE
XCODE_EXPLICIT_FILE_TYPE
XCODE_FILE_ATTRIBUTES
XCODE_LAST_KNOWN_FILE_TYPE
)

set(_dir_properties
ADDITIONAL_MAKE_CLEAN_FILES
BINARY_DIR
BUILDSYSTEM_TARGETS
CACHE_VARIABLES
CLEAN_NO_CUSTOM
CMAKE_CONFIGURE_DEPENDS
COMPILE_DEFINITIONS
COMPILE_OPTIONS
DEFINITIONS
EXCLUDE_FROM_ALL
IMPLICIT_DEPENDS_INCLUDE_TRANSFORM
INCLUDE_DIRECTORIES
INCLUDE_REGULAR_EXPRESSION
INTERPROCEDURAL_OPTIMIZATION_<CONFIG>
INTERPROCEDURAL_OPTIMIZATION
LINK_DIRECTORIES
LISTFILE_STACK
MACROS
PARENT_DIRECTORY
RULE_LAUNCH_COMPILE
RULE_LAUNCH_CUSTOM
RULE_LAUNCH_LINK
SOURCE_DIR
SUBDIRECTORIES
TEST_INCLUDE_FILE
VARIABLES
)

function(debugTarget _target)
  # a hello
  message("debugging ${_target}")
  # inspecting target
  foreach(_prop ${_target_properties})
    get_property(_val TARGET ${_target} PROPERTY ${_prop})
    if(_val)
      message("${_prop}@${_target} = ${_val}")
    endif()
  endforeach()
  # inspecting sources
  get_property(_sources TARGET ${_target} PROPERTY SOURCES)
  foreach(_source ${_sources})
    foreach(_prop ${_source_properties})
       get_property(_val SOURCE ${_source} PROPERTY ${_prop})
      if(_val)
        message("${_prop}@${_target}/${_source} = ${_val}")
      endif()
    endforeach()
  endforeach()
  # inspecting directories
  message("debugging directory ${CMAKE_CURRENT_SOURCE_DIR}")
  foreach(_prop @{_dir_properties})
    get_directory_property(_val ${_prop})
    if(_val)
          message("${_prop}@dir(${CMAKE_CURRENT_SOURCE_DIR}) = ${_val}")
    endif()
  endforeach()  
endfunction()

