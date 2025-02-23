#pragma once

/*
 *  ...
 */

 #include <span>
 #include <string_view>

 #include "data_constants.h"
 #include "data_types.h"

namespace metis::core {

    struct data_query_payload {
        std::string_view   question, answer;
    };

    struct data_query_sort {
        using element = std::string_view;

        std::span<element> sort_elements;
    };
    
    struct data_query_batch {
        float              base;
        float              penalty, penalty_heavy;
        float              rng;
    };

    struct data_query_stats {
        std::uint32_t      count_query, count_mistake;
    };

    struct data_query_meta {
        using element = std::string_view;

        std::span<element> flags;
    };

}
