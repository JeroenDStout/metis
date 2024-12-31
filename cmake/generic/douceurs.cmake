message(STATUS "Setup douceurs")

include(FetchContent)

# Obtain SDL3
FetchContent_Declare(
  douceurs
  GIT_REPOSITORY https://github.com/JeroenDStout/douceurs.git
  GIT_TAG        6c5abc110be1dd1992e55b0557265c25d9da4906
  GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(douceurs)
    
# Config
function(configure_project_douceurs project_ref)
  message(STATUS "Configure douceurs ${project_ref}")
  
  include_directories(${douceurs_SOURCE_DIR}/include)
  
  set_target_properties(douceurs_repo_version PROPERTIES FOLDER "dependencies/douceurs")
endfunction()
