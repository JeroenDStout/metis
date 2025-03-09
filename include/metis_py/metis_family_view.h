#pragma once

/*
 *  ...
 */

#include "metis_core/data_set.h"
#include "metis_core/data_types.h"

namespace metis::py {

    struct subject_view {
        metis::core::data_set         *owner;
        metis::core::subject_idx_t    idx;
    };

    struct family_view {
        metis::core::data_set         *owner;
        metis::core::family_idx_t     idx;
    };

    struct discipline_view {
        metis::core::data_set         *owner;
        metis::core::discipline_idx_t idx;
    };

}