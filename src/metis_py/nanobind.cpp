#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"

void nb_repo_version(nanobind::module_&);

NB_MODULE(metis_py, m)
{
    nb_repo_version(m);
}
