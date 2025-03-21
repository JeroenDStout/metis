#include "metis_core/proc_io_legacy.h"

#include <chrono>
#include <iostream>

#include "douceurs/def_value.h"
#include "douceurs/ref_value.h"
#include "douceurs/slurp.h"
#include "douceurs/template_buffer_alloc.h"

#include "metis_core/inc_tinyxml.h"

using namespace metis::core;

void proc_io_legacy::load_from_path(load_stats *out_stats, std::string_view path) const
{
    namespace d = douceurs;
    
    if (verbose_logging)
      std::cout << "proc_io_legacy::load_from_path from " << path << " started" << std::endl;

    // Time helpers
    auto get_time_now   = [] {
      return std::chrono::high_resolution_clock::now();
    };
    auto duration_in_ms = [](auto t1, auto t2) {
      return std::uint32_t(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
    };

    // Function constants
    bool const write_stats = out_stats != nullptr;
    bool const gen_stats   = write_stats || verbose_logging;
    std::string const path_str(path);
    std::string buffer;
    
    auto t_start = d::value::con_invoke(gen_stats, get_time_now);

    // -- Slurp file
    
    auto slurp_ret = d::io::slurp(d::value::keep(d::memory::buf_std(buffer)), std::string(path));
    if (d::io::is_failure(slurp_ret)) {
        std::cout << "Could not load " << path;
        return;
    }
    
    auto t_slurp_done = d::value::con_invoke(gen_stats, get_time_now);
    if (gen_stats) {
        auto ms = duration_in_ms(t_start, t_slurp_done);
        if (verbose_logging) std::cout << "Finished reading in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->read_time_ms = ms;
    }

    // -- Parse as XML
    
    tinyxml2::XMLDocument document;
    bool success = (tinyxml2::XML_SUCCESS == document.Parse(buffer.data(), buffer.size()));
    if (!success) {
        std::cout << "Could not parse " << path;
        return;
    }
    
    auto t_parse_done = d::value::con_invoke(gen_stats, get_time_now);
    if (gen_stats) {
        auto ms = duration_in_ms(t_slurp_done, t_parse_done);
        if (verbose_logging) std::cout << "Finished parsing xml in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->parse_time_ms = ms;
    }

    // -- Finish up

    if (gen_stats) {
        auto ms = duration_in_ms(t_start, t_parse_done);
        if (verbose_logging) std::cout << "Finished loading in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->total_time_ms = ms;
    }
    
    if (verbose_logging)
      std::cout << "proc_io_legacy::load_from_path " << path << " completed" << std::endl;
}