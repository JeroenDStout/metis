#include <iostream>

#include "metis_core/data_questions.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

void nb_metis_module(nanobind::module_ &m)
{
    m;
}