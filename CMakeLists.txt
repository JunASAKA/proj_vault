CMAKE_MINIMUM_REQUIRED(VERSION 3.24) #cmake最低版本
PROJECT("vault") #Project name
SET(CMAKE_CXX_STANDARD 23)
include_directories(src/include)
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
SET(CMAKE_CXX_FLAGS "-ljsoncpp -lsqlite3 -O2")#编译选项，非紧急情况不要动。
IF(WIN32)
    SET(CMAKE_CXX_FLAGS "-lcurldll")
    SET(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
ELSEIF(APPLE)
    SET(CMAKE_CXX_FLAGS "-lcurl")
ELSEIF(UNIX)
    SET(CMAKE_CXX_FLAGS "-lcurl")
ENDIF()
SET(SRC_LISTS ${DIR_SRCS})#将源文件整理进一个变量，方便管理。文件之间用半角分号分割。
ADD_EXECUTABLE(vault ${SRC_LISTS})#同上。
IF(WIN32)
    TARGET_LINK_LIBRARIES(vault jsoncpp curldll)
ELSEIF(APPLE)
    TARGET_LINK_LIBRARIES(vault jsoncpp curl)
ELSEIF(UNIX)
    TARGET_LINK_LIBRARIES(vault jsoncpp curl sqlite3)
ENDIF()
