#include <iostream>

#include "metis_core/data_set.h"
#include "metis_core/proc_set_impl.h"

#include "metis_py/metis_query_view.h"
#include "metis_py/metis_family_view.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_set_detail {

    template<typename view_t, typename idx_t>
    auto get_view(metis::core::data_set &ref, idx_t idx) {
        auto view = std::make_unique<view_t>();
        view->owner = &ref;
        view->idx   = idx;
        return view;
    }

}

void nb_metis_sets(nanobind::module_ &m)
{
    namespace d  = metis_set_detail;
    namespace mc = metis::core;
    namespace mp = metis::py;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;

    // TODO: Boundary checks?

    nb::class_<mc::data_set>(m, "set")
      .def(nb::init<>())
      .def("get_stats_string",
        [](const mc::data_set& ref) { proc_set_dbg_string p; std::stringstream ss; p.debug_string_stats(ss, ref); return ss.str(); }
      )
      .def_prop_ro("discipline_count",
        [](const mc::data_set& ref) { return ref.buffers.canonical.discipline_names.size(); }
      )
      .def("get_discipline_view",
        [](mc::data_set &ref, mc::discipline_idx_t idx) { return d::get_view<mp::discipline_view>(ref, idx); }
      )
      .def("add_discipline",
        [](mc::data_set &ref) { mc::proc_set p; return d::get_view<mp::discipline_view>(ref, p.add_discipline(ref)); }
      )
      .def("get_family_view",
        [](mc::data_set &ref, mc::query_idx_t idx) { return d::get_view<mp::family_view>(ref, idx); }
      )
      .def("add_family",
        [](mc::data_set &ref) { mc::proc_set p; return d::get_view<mp::family_view>(ref, p.add_family(ref)); }
      )
      .def_prop_ro("subject_count",
        [](const mc::data_set& ref) { return ref.buffers.canonical.subject_names.size(); }
      )
      .def("get_subject_view",
        [](mc::data_set &ref, mc::query_idx_t idx) { return d::get_view<mp::subject_view>(ref, idx); }
      )
      .def("add_subject",
        [](mc::data_set &ref) { mc::proc_set p; return d::get_view<mp::subject_view>(ref, p.add_subject(ref)); }
      )
      .def_prop_ro("query_count",
        [](const mc::data_set& ref) { return ref.buffers.canonical.query_payloads.size(); }
      )
      .def("get_query_view",
        [](mc::data_set &ref, mc::query_idx_t idx) { return d::get_view<mp::query_view>(ref, idx); }
      )
      .def("add_query",
        [](mc::data_set &ref) { mc::proc_set p; return d::get_view<mp::query_view>(ref, p.add_query(ref)); }
      )
    ;
}
