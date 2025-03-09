#include <iostream>

#include "metis_core/data_set.h"
#include "metis_core/proc_set.h"

#include "metis_py/metis_query_view.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_set_detail {

    auto get_query_view(metis::core::data_set &ref, metis::core::query_idx_t idx) {
        auto view = std::make_unique<metis::py::query_view>();
        view->owner     = &ref;
        view->query_idx = idx;
        return view;
    }

}

void nb_metis_sets(nanobind::module_ &m)
{
    namespace d  = metis_set_detail;
    namespace mc = metis::core;

    nb::class_<mc::data_set>(m, "set")
      .def(nb::init<>())
      .def_prop_ro("query_count",
        [](const mc::data_set& ref) { return ref.buffers.canonical.query_payloads.size(); }
      )
      .def("get_query_view", /* TODO: Boundary check? */
        [](mc::data_set &ref, mc::query_idx_t idx) { return d::get_query_view(ref, idx); }
      )
      .def("add_query",
        [](mc::data_set &ref) { mc::proc_set p; return d::get_query_view(ref, p.add_query(ref)); }
      )
    ;
}
