#include <iostream>

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

void nb_metis_sets(nanobind::module_ &m);
void nb_metis_query_view(nanobind::module_ &m);

void nb_metis_module(nanobind::module_ &m)
{
    nb_metis_sets(m);
    nb_metis_query_view(m);
}
