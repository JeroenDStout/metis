#include <iostream>

#include "metis_core/proc_io_legacy.h"

#include "metis_py/inc_nanobind.h"
#include "metis_py/inc_nanobind_stl.h"
namespace nb = nanobind;

void nb_metis_io(nb::module_ &m)
{
    namespace mc = metis::core;

    using load_stats = mc::proc_io_legacy::load_stats;
    nb::class_<load_stats>(m, "load_stats")
      .def_rw("read_time",     &load_stats::read_time_ms)
      .def_rw("total_time_ms", &load_stats::total_time_ms)
    ;

    m.def("load_legacy", [](std::string path) {
        mc::proc_io_legacy proc;
        mc::proc_io_legacy::load_stats stats;
        proc.load_from_path(&stats, path);
        return std::make_tuple(int(0), stats);
      }
    );
}