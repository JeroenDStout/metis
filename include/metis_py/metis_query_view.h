#pragma once

/*
 *  ...
 */

#include "metis_core/data_set.h"
#include "metis_core/data_types.h"

namespace metis::py {

    struct query_view {
        
        metis::core::data_set    *owner;
        metis::core::query_idx_t idx;

    };

}