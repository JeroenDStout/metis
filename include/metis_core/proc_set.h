#pragma once

/*
 *  ...
 */

 #include <string_view>
 #include "metis_core/data_types.h"

namespace metis::core {

    struct data_set;

    struct proc_set {
        
        bool verbose_logging = true;
        
        std::string_view alloc(data_set&, std::string_view const&) const;

        query_idx_t add_query(data_set&) const;
    };

}
