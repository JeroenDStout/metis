init_directory(metis_core)

# Define the metis_core project
init_project(metis_core "metis")

# Sources
setup_project_source(metis_core "core"
  src:
    metis.cpp
)
setup_project_source(metis_core "core/const"
  include:
    data_types.h
    data_constants.h
)
setup_project_source(metis_core "core/data"
  include:
    data_queries.h
    data_queries_impl.h
    data_set.h
    data_family.h
    data_family_impl.h
)
#setup_project_source(metis_core "core/policy"
#)
setup_project_source(metis_core "core/proc"
  src:
    proc_set.cpp
  include:
    proc_set.h
    proc_set_impl.h
)

setup_project_source(metis_core "assets"
  src:
    assets.cpp
  include:
    assets.h
)

# Target
configure_project_static_lib(metis_core)
configure_cxx_target(metis_core)
configure_target_outputs(metis_core)
configure_publish_exec(metis_core)
configure_project_douceurs(metis_core)
#configure_asset_folder(metis_core metis_core_assets ...)
    
add_dependencies(metis_core repo_version)
