#include "metis_core/proc_set_impl.h"

#include "metis_core/data_family_impl.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

#include "douceurs/render_string.h"

namespace metis_query_view_detail {

    template<typename view_t>
    auto alloc_string(view_t &view, std::string_view const &string) {
        metis::core::proc_set proc;
        return proc.alloc(view.owner, string);
    }

}

#define FILL_PROP_STR(str_name, prop_group, prop_id) \
  str_name, \
  [](view const &view)            { return view.prop_group().prop_id;                            }, \
  [](view &view, string const &v) { view.prop_group().prop_id        = d::alloc_string(view, v); }

void nb_metis_discipline_view(nanobind::module_ &m)
{
    namespace mc = metis::core;
    namespace d  = metis_query_view_detail;

    using view   = metis::core::view_discipline;
    using string = std::string;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;
    
    nb::class_<view>(m, "discipline_view")
      .def("get_dbg_string",
        [](view const& view) { proc_set_dbg_string p; std::stringstream ss; p.debug_string_discipline(ss, view); return ss.str(); }
      )
      .def_prop_rw(FILL_PROP_STR("id",           names, id      ))
      .def_prop_rw(FILL_PROP_STR("display_name", names, display ))
      .def_prop_rw(FILL_PROP_STR("sort_name",    names, sort    ))
    ;
}

void nb_metis_family_view(nanobind::module_ &m)
{
    namespace mc = metis::core;
    namespace d  = metis_query_view_detail;
    
    using view   = metis::core::view_family;
    using string = std::string;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;
    
    nb::class_<view>(m, "family_view")
      .def("get_dbg_string",
        [](view const& view) { proc_set_dbg_string p; std::stringstream ss; p.debug_string_family(ss, view); return ss.str(); }
      )
      .def_prop_rw(FILL_PROP_STR("id",           names,     id         ))
      .def_prop_rw(FILL_PROP_STR("display_name", names,     display    ))
      .def_prop_rw(FILL_PROP_STR("sort_name",    names,     sort       ))
      .def_prop_rw(FILL_PROP_STR("discipline",   relations, discipline ))
    ;
}

void nb_metis_subject_view(nanobind::module_ &m)
{
    namespace mc = metis::core;
    namespace d  = metis_query_view_detail;

    using view   = metis::core::view_subject;
    using string = std::string;
    using proc_set_dbg_string = mc::proc_set_dbg_string<douceurs::strings::render_dbg_vars_style_json>;
    
    nb::class_<view>(m, "subject_view")
      .def("get_dbg_string",
        [](view const& view)            { proc_set_dbg_string p; std::stringstream ss; p.debug_string_subject(ss, view); return ss.str(); }
      )
      .def_prop_rw(FILL_PROP_STR("id",           names,     id      ))
      .def_prop_rw(FILL_PROP_STR("display_name", names,     display ))
      .def_prop_rw(FILL_PROP_STR("sort_name",    names,     sort    ))
      .def_prop_rw(FILL_PROP_STR("family",       relations, family  ))
    ;
}
