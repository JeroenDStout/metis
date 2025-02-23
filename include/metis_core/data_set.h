#pragma once

/*
 *  ...
 */

 #include <memory_resource>

 #include "data_queries.h"

namespace metis::core {

    struct data_set_buffers {
        using raw_allocator_t = std::unique_ptr<std::pmr::monotonic_buffer_resource>;

        raw_allocator_t                 raw_allocator;
        std::vector<data_query_payload> query_payloads;
    };

    struct data_set {
        data_set_buffers buffers;
    };

}
