#pragma once

/*
 *  ...
 */

 #include <span>
 #include <string_view>
 #include <sstream>

 #include "data_constants.h"
 #include "data_types.h"

namespace metis::core {

    struct data_query_payload {
        std::string_view   question, answer;

        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_query_sort {
        using element = std::string_view;

        std::span<element> sort_elements;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };
    
    struct data_query_batch {
        bool               is_active : 1;
        bool               is_potato : 1;
        timepoint_t        query_last_tp;
        float              batch_base;
        float              batch_penalty_slow, batch_penalty_fast;
        float              batch_rng;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_query_meta {
        using element = std::string_view;

        std::span<element> flags;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_query_relation {
        std::string_view   subject;
        std::string_view   group;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_query_stats {
        timepoint_t        query_add_time;
        std::uint32_t      count_query_all, count_query_mistake;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

}
