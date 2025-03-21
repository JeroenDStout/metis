#include <iostream>

#include "metis_core/proc_io_legacy_impl.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

#include "douceurs/render_string.h"

void nb_metis_io(nb::module_ &m)
{
    namespace mc = metis::core;
    using dbg_style = douceurs::strings::render_dbg_vars_style_json;

    using load_stats = mc::proc_io_legacy::load_stats;
    nb::class_<load_stats>(m, "load_stats")
      .def("get_dbg_string",
        [](const load_stats& stats) { std::stringstream ss; stats.debug_string<dbg_style>(ss); return ss.str(); }
      )
      .def_rw("read_time",  &load_stats::read_time_ms)
      .def_rw("parse_time", &load_stats::parse_time_ms)
      .def_rw("total_time", &load_stats::total_time_ms)
    ;

    m.def("load_legacy", [](std::string path) {
        mc::proc_io_legacy proc;
        mc::proc_io_legacy::load_stats stats;
        proc.load_from_path(&stats, path);
        return std::make_tuple(int(0), stats);
      }
    );
}