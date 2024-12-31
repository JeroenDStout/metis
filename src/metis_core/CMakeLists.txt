init_directory(metis_core)

# Define the metis_core project
init_project(metis_core "metis")

# Sources
setup_project_source(metis_core "core"
  src:
    metis.cpp
)
setup_project_source(metis_core "core/data"
  include:
    data_questions.h
)
#setup_project_source(metis_core "core/policy"
#)
#setup_project_source(metis_core "core/proc"
#)

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
#configure_asset_folder(metis_core metis_core_assets ...)
    
add_dependencies(metis_core repo_version)
