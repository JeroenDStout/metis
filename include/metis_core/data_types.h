#pragma once

/*
 *  ...
 */

#include <chrono>

namespace metis::core {

    using query_idx_t      = std::uint32_t;
    using subject_idx_t    = std::uint32_t;
    using family_idx_t     = std::uint32_t;
    using discipline_idx_t = std::uint32_t;

    using timepoint_d_t    = std::chrono::seconds;
    using timepoint_t      = std::chrono::sys_time<timepoint_d_t>;

}
