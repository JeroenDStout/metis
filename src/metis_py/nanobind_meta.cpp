#include "metis_py/inc_nanobind.h"
#include "repo_version/git_version.h"
#include "douceurs_repo_version/git_version.h"

void nb_repo_version(nanobind::module_ &m)
{
    m.def("get_version", [](){
      nanobind::dict dict;
      dict["metis"]    = gaos::version::get_git_essential_version();
      dict["douceurs"] = douceurs::version::get_git_essential_version();
      return dict;
    });
}