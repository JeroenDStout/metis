init_directory(metis_qt)

# Define the Timetron project
init_project(metis_qt "metis")

# Sources
setup_project_source(metis_qt "core"
  src:
    main.cpp
    window.cpp
  include:
    window.h
)
setup_project_source_qt_ui(metis_qt "ui"
  window.ui
  version.ui
)
setup_project_source(metis_qt "assets"
  src:
    ${rel_can_assets}/app_resource/resource.rc
)

# Target
configure_project_executable(metis_qt)
configure_project_console(metis_qt)
configure_cxx_target(metis_qt)
configure_qt_target(metis_qt)
configure_publish_exec(metis_qt)
	
add_dependencies(metis_qt repo_version douceurs_repo_version metis_core)
target_link_libraries(metis_qt PRIVATE metis_core)
