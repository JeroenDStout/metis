#include "metis_core/proc_set.h"

#include "metis_py/metis_family_view.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

namespace metis_query_view_detail {

    auto& names(metis::py::discipline_view &view) {
        return view.owner->buffers.canonical.discipline_names[view.idx];
    }
    
    auto& names(metis::py::discipline_view const &view) {
        return view.owner->buffers.canonical.discipline_names[view.idx];
    }

    auto& names(metis::py::family_view &view) {
        return view.owner->buffers.canonical.family_names[view.idx];
    }
    
    auto& names(metis::py::family_view const &view) {
        return view.owner->buffers.canonical.family_names[view.idx];
    }

    auto& relation(metis::py::family_view &view) {
        return view.owner->buffers.canonical.family_relations[view.idx];
    }
    
    auto& relation(metis::py::family_view const &view) {
        return view.owner->buffers.canonical.family_relations[view.idx];
    }

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

void nb_metis_discipline_view(nanobind::module_ &m)
{
    namespace d = metis_query_view_detail;

    using view   = metis::py::discipline_view;
    using string = std::string;
    
    nb::class_<view>(m, "discipline_view")
      .def_prop_rw("id",
        [](view const &view)            { return d::names(view).id;                            },
        [](view &view, string const &v) { d::names(view).id        = d::alloc_string(view, v); }
      )
      .def_prop_rw("display_name",
        [](const view &view)            { return d::names(view).display;                       },
        [](view &view, string const &v) { d::names(view).display   = d::alloc_string(view, v); }
      )
      .def_prop_rw("sort_name",
        [](const view &view)            { return d::names(view).sort;                          },
        [](view &view, string const &v) { d::names(view).sort      = d::alloc_string(view, v); }
      )
    ;
}

void nb_metis_family_view(nanobind::module_ &m)
{
    namespace d = metis_query_view_detail;

    using view   = metis::py::family_view;
    using string = std::string;
    
    nb::class_<view>(m, "family_view")
      .def_prop_rw("id",    
        [](view const &view)            { return d::names(view).id;                               },
        [](view &view, string const &v) { d::names(view).id            = d::alloc_string(view, v); }
      )
      .def_prop_rw("display_name",
        [](const view &view)            { return d::names(view).display;                           },
        [](view &view, string const &v) { d::names(view).display       = d::alloc_string(view, v); }
      )
      .def_prop_rw("sort_name",
        [](const view &view)            { return d::names(view).sort;                              },
        [](view &view, string const &v) { d::names(view).sort          = d::alloc_string(view, v); }
      )
      .def_prop_rw("discipline",
        [](const view &view)            { return d::relation(view).discipline;                     },
        [](view &view, string const &v) { d::relation(view).discipline = d::alloc_string(view, v); }
      )
    ;
}

void nb_metis_subject_view(nanobind::module_ &m)
{
    namespace d = metis_query_view_detail;

    using view   = metis::py::subject_view;
    using string = std::string;
    
    nb::class_<view>(m, "subject_view")
      .def_prop_rw("id",
        [](view const &view)            { return d::names(view).id;                                },
        [](view &view, string const &v) { d::names(view).id            = d::alloc_string(view, v); }
      )                                                                                            
      .def_prop_rw("display_name",                                                                 
        [](const view &view)            { return d::names(view).display;                           },
        [](view &view, string const &v) { d::names(view).display       = d::alloc_string(view, v); }
      )
      .def_prop_rw("sort_name",
        [](const view &view)            { return d::names(view).sort;                              },
        [](view &view, string const &v) { d::names(view).sort          = d::alloc_string(view, v); }
      )
      .def_prop_rw("family",
        [](const view &view)            { return d::relation(view).family;                         },
        [](view &view, string const &v) { d::relation(view).family     = d::alloc_string(view, v); }
      )
    ;
}
