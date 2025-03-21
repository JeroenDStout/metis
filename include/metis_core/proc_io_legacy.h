#pragma once

/*
 *  ...
 */
 
 #include <sstream>
 #include <string_view>
 #include "metis_core/data_types.h"

namespace metis::core {

    struct proc_io_legacy {
        bool verbose_logging = true;

        struct load_stats {
            std::uint32_t read_time_ms;
            std::uint32_t parse_time_ms;
            std::uint32_t total_time_ms;

            template<typename style_t>
            void debug_string(std::stringstream&) const;
        };

        void load_from_path(load_stats *out_stats, std::string_view path) const;
    };

}
