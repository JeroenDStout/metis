#pragma once

/*
 *  ...
 */
 
 #include <span>
 #include <string_view>
 #include <sstream>
 #include "metis_core/data_types.h"

namespace metis::core {

    struct data_set;

    struct proc_set {
        
        bool verbose_logging = true;

        using string_view      = std::string_view;
        using string_view_span = std::span<std::string_view>;
        
        string_view      alloc(data_set&, string_view const&)      const;
        string_view_span alloc(data_set&, string_view_span const&) const;

        discipline_idx_t add_discipline(data_set&) const;
        family_idx_t     add_family(data_set&) const;
        subject_idx_t    add_subject(data_set&) const;
        query_idx_t      add_query(data_set&) const;
    };

    template<typename style_t>
    struct proc_set_dbg_string {
        void debug_string_stats(     std::stringstream&, data_set const&) const;
        void debug_string_discipline(std::stringstream&, data_set const&, discipline_idx_t) const;
        void debug_string_family(    std::stringstream&, data_set const&, family_idx_t) const;
        void debug_string_subject(   std::stringstream&, data_set const&, subject_idx_t) const;
        void debug_string_query(     std::stringstream&, data_set const&, query_idx_t) const;
    };

}
