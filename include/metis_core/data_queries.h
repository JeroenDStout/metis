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
        float              base;
        float              penalty_slow, penalty_fast;
        float              rng;
        
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
        std::uint32_t      count_query, count_mistake;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

}
