#include "metis_core/proc_set_impl.h"
#include "metis_core/data_queries_impl.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_query_view_detail {

    auto alloc_string(metis::core::view_query &view, std::string_view const &string) {
        metis::core::proc_set proc;
        return proc.alloc(view.owner, string);
    }

}

#define FILL_PROP_STR(str_name, prop_group, prop_id) \
  str_name, \
  [](view const &view)            { return view.prop_group().prop_id;                            }, \
  [](view &view, string const &v) { view.prop_group().prop_id        = d::alloc_string(view, v); }

void nb_metis_query_view(nanobind::module_ &m)
{
    namespace mc = metis::core;
    namespace d  = metis_query_view_detail;

    using view   = metis::core::view_query;
    using string = std::string;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;

    nb::class_<view>(m, "query_view")
      .def("get_dbg_string",
        [](const view& view) { proc_set_dbg_string p; std::stringstream ss; p.debug_string_query(ss, view); return ss.str(); }
      )
      .def_prop_rw(FILL_PROP_STR("question", payload, question))
      .def_prop_rw(FILL_PROP_STR("answer",   payload, answer  ))
    ;
}
