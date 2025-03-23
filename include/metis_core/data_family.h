#pragma once

/*
 *  ...
 */

 #include <string_view>
 #include <sstream>

 #include "data_constants.h"
 #include "data_types.h"

namespace metis::core {

    // Discipline

    struct data_discipline_names {
        std::string_view   id, display, sort;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_discipline_meta {
        using element = std::string_view;

        std::span<element> tags;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    // Family

    struct data_family_names {
        std::string_view   id, display, sort;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_family_relation {
        std::string_view   discipline;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_family_meta {
        using element = std::string_view;

        std::span<element> tags;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };


    // Subject

    struct data_subject_names {
        std::string_view   id, display, sort;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_subject_relation {
        std::string_view   family;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

    struct data_subject_meta {
        using element = std::string_view;

        std::span<element> tags;
        
        template<typename style_t>
        void debug_string(std::stringstream&) const;
    };

}
