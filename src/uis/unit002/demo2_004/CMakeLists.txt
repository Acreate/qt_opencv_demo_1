message("============ ${CURRENT_FOLDER}")
string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
message("name =" ${CURRENT_FOLDER})
project(
  ${CURRENT_FOLDER}
  VERSION 0.1
  LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(OpenCV_DIR "C:/libs/opencv/build/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 当前目录下也有代码
file(  GLOB  SRC_LIST
  "*.cpp"
  "*.c"
  "*.hpp"
  "*.h"
  "*.ui")
include_directories(../libs/converQimageOrCvMat)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  # qt_add_executable( ${PROJECT_NAME} MANUAL_FINALIZATION ${SRC_LIST} )
  add_executable(${PROJECT_NAME} ${SRC_LIST})
else()
  if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
  else()
    add_executable(${PROJECT_NAME} ${SRC_LIST})
  endif()
endif()

target_link_libraries(
	  ${PROJECT_NAME}
  PRIVATE 
	Qt${QT_VERSION_MAJOR}::Core 
	Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets 
	${OpenCV_LIBS}
	converQimageOrCvMat)
# 设置包内容
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE NOT)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(${PROJECT_NAME})
endif()

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:opencv_world>
          "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

if(APPLE)
  set(executable_path "$<TARGET_FILE_NAME:${PROJECT_NAME}>.app")
else()
  set(executable_path
      "${EXECUTABLE_OUTPUT_PATH}/$<TARGET_FILE_NAME:${PROJECT_NAME}>")
endif()

set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${PROJECT_NAME}.cmake")
file(
  GENERATE
  OUTPUT ${deploy_script}
  CONTENT
    "
message(\"=================\")
message(\"============	> 执行 : ${executable_path}\")
message(\"=================\")
include(\"${QT_DEPLOY_SUPPORT}\")

message(\"=================\")
message(\"============	> 消息 ${EXECUTABLE_OUTPUT_PATH}\")
message(\"============	> 消息 ${QT_DEPLOY_SUPPORT}\")
message(\"=================\")

qt_deploy_runtime_dependencies(
    EXECUTABLE \"${executable_path}\"
	BIN_DIR ${EXECUTABLE_OUTPUT_PATH}
	LIB_DIR bin
	PLUGINS_DIR bin
)
")
install(SCRIPT ${deploy_script})
