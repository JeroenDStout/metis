init_directory(metis_py)

# Define the metis_py project
init_project(metis_py "metis")

# Sources
setup_project_source(metis_py "nanobind"
  src:
    nanobind.cpp
    nanobind_meta.cpp
)
setup_project_source(metis_py "module"
  src:
    metis_module.cpp
)
setup_project_source(metis_py "bindings"
  src:
    metis_io.cpp
    metis_set.cpp
    metis_query_view.cpp
    metis_family_view.cpp
  include:
    metis_query_view.h
    metis_family_view.h
)
setup_project_source(metis_py "third_party"
  include:
    inc_nanobind.h
    inc_nanobind_stl.h
)

# Target
configure_project_nanobind(metis_py)
configure_cxx_target(metis_py)
configure_target_outputs(metis_py)
configure_project_eigen(metis_py)
configure_project_douceurs(metis_py)
	
add_dependencies(metis_py metis_core repo_version)
target_link_libraries(metis_py PRIVATE metis_core)
