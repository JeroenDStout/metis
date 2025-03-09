#include "metis_core/proc_set.h"

#include "metis_py/metis_family_view.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_query_view_detail {

    auto& names(metis::py::subject_view &view) {
        return view.owner->buffers.canonical.subject_names[view.idx];
    }
    
    auto& names(metis::py::subject_view const &view) {
        return view.owner->buffers.canonical.subject_names[view.idx];
    }

    auto& relation(metis::py::subject_view &view) {
        return view.owner->buffers.canonical.subject_relations[view.idx];
    }
    
    auto& relation(metis::py::subject_view const &view) {
        return view.owner->buffers.canonical.subject_relations[view.idx];
    }

    template<typename view_t>
    auto alloc_string(view_t &view, std::string_view const &string) {
        metis::core::proc_set proc;
        return proc.alloc(*view.owner, string);
    }

}

void nb_metis_subject_view(nanobind::module_ &m)
{
    namespace d = metis_query_view_detail;

    using view   = metis::py::subject_view;
    using string = std::string;

    nb::class_<view>(m, "subject_view")
      .def_prop_rw("id",
        [](view const &view)            { return d::names(view).id;                            },
        [](view &view, string const &v) { d::names(view).id = d::alloc_string(view, v);        }
      )
      .def_prop_rw("display_name",
        [](const view &view)            { return d::names(view).display;                       },
        [](view &view, string const &v) { d::names(view).display   = d::alloc_string(view, v); }
      )
    ;
}
