cmake_minimum_required(VERSION 3.2)

project(bulkmt VERSION 0.0.1)

configure_file(version.h.in version.h)

add_executable(bulkmt main.cpp
	CoutObserver.cpp
	LogObserver.cpp
	CommandBlock.cpp
	TimedBlock.cpp
	LineProcessor.cpp
	Metrics.cpp
	MetricsCollection.cpp
)

set_target_properties(bulkmt PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
	COMPILE_OPTION -Wpedantic -Wall -Wextra
)

target_link_libraries(bulkmt -pthread)

install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT erkinvs@gmail.com)

include(CPack)