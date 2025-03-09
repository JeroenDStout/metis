#include "metis_core/proc_set_impl.h"
#include "metis_core/data_queries_impl.h"

#include "metis_py/metis_query_view.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_query_view_detail {

    auto& payload(metis::py::query_view &view) {
        return view.owner->buffers.canonical.query_payloads[view.idx];
    }
    
    auto& payload(metis::py::query_view const &view) {
        return view.owner->buffers.canonical.query_payloads[view.idx];
    }

    auto alloc_string(metis::py::query_view &view, std::string_view const &string) {
        metis::core::proc_set proc;
        return proc.alloc(*view.owner, string);
    }

}

void nb_metis_query_view(nanobind::module_ &m)
{
    namespace mc = metis::core;
    namespace d  = metis_query_view_detail;

    using qv     = metis::py::query_view;
    using string = std::string;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;

    nb::class_<qv>(m, "query_view")
      .def("get_dbg_string",
        [](const qv& view)            { proc_set_dbg_string p; std::stringstream ss; p.debug_string_query(ss, *view.owner, view.idx); return ss.str(); }
      )
      .def_prop_rw("question",
        [](qv const &view)            { return d::payload(view).question;                     },
        [](qv &view, string const &v) { d::payload(view).question = d::alloc_string(view, v); }
      )
      .def_prop_rw("answer",
        [](const qv &view)            { return d::payload(view).answer;                       },
        [](qv &view, string const &v) { d::payload(view).answer   = d::alloc_string(view, v); }
      )
    ;
}
