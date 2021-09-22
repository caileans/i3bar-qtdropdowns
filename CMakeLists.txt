
cmake_minimum_required(VERSION 3.5)

project(i3_QDropDown VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)


set(DROPDOWNTEMP
    lib/QDropDown.cpp
    lib/QDropDown.h
)

include_directories(lib/)

add_executable(PowerDropDown PowerDropDown.cpp ${DROPDOWNTEMP})
target_link_libraries(PowerDropDown PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)
set_target_properties(PowerDropDown PROPERTIES AUTOMOC TRUE)

add_executable(CalendarDropDown CalendarDropDown.cpp ${DROPDOWNTEMP})
target_link_libraries(CalendarDropDown PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)
set_target_properties(CalendarDropDown PROPERTIES AUTOMOC TRUE)


