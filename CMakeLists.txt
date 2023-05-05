cmake_minimum_required(VERSION 3.10.2)
project(maket_bot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

# DB lib
find_package(SqliteOrm REQUIRED)


set(DB_SOURCES  db/model/user.h
                db/model/mock.cpp
                db/model/mock.h
                db/DBHandler.cpp
                db/DBHandler.h
                db/model/entity.h
                db/model/Room.h
                db/model/DataObject.h
                db/model/Wall.h
                db/model/Material.h)

add_library(db_handler ${DB_SOURCES})
target_link_libraries(db_handler PRIVATE sqlite_orm::sqlite_orm)


#IMAGE BUILDER

find_package( OpenCV REQUIRED )
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package (SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

set(IB_SOURCES ImageBuilder/src/ImageBuilder.cpp
        ImageBuilder/src/ImageBuilder.h ImageBuilder/src/ConfigParser.cpp ImageBuilder/src/ConfigParser.h ImageBuilder/src/Finishing.h ImageBuilder/src/Config.cpp ImageBuilder/src/Config.h)
set(SFML_LIBRARIES -lsfml-graphics -lsfml-window -lsfml-system)

add_library(ImageBuilder ${IB_SOURCES})
# ${OpenCV_LIBS}                                     ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
target_link_libraries(ImageBuilder  ${OpenCV_LIBS}
                                    nlohmann_json::nlohmann_json)

add_executable(test_IB ImageBuilder/main.cpp)
target_link_libraries(test_IB ImageBuilder)
#-------------------------

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(maket_bot main.cpp   src/UserState.cpp
                                    src/UserState.h
                                    src/Dispatcher.cpp
                                    src/Dispatcher.h)

target_link_libraries(maket_bot db_handler
                                /usr/local/lib/libTgBot.a
                                ${CMAKE_THREAD_LIBS_INIT}
                                ${OPENSSL_LIBRARIES}
                                ${Boost_LIBRARIES}
                                ${CURL_LIBRARIES})