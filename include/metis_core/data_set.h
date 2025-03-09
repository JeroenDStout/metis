#pragma once

/*
 *  ...
 */

 #include <memory_resource>
 #include <unordered_map>

 #include "data_queries.h"
 #include "data_family.h"

namespace metis::core {

    struct data_set_buffers {
        using raw_allocator_t = std::unique_ptr<std::pmr::monotonic_buffer_resource>;

        template<typename T>
        using array_t         = std::vector<T>;
        template<typename T>
        using smap_t           = std::unordered_map<std::string_view, T>;

        raw_allocator_t raw_allocator;

        struct canonical_t {            
            array_t<data_discipline_names>   discipline_names;
            smap_t<discipline_idx_t>         discipline_id_to_idx;
                                             
            array_t<data_family_names>       family_names;
            array_t<data_family_relation>    family_relations;
            smap_t<family_idx_t>             family_id_to_idx;
                                             
            array_t<data_subject_names>      subject_names;
            array_t<data_subject_relation>   subject_relations;
            smap_t<subject_idx_t>            subject_id_to_idx;

            array_t<data_query_payload>      query_payloads;
            array_t<data_query_relation>     query_relations;

            bool                             flag_maps_dirty;
        } canonical;

        data_set_buffers()
        : raw_allocator(std::make_unique<raw_allocator_t::element_type>())
        { ; }
    };

    struct data_set {
        data_set_buffers buffers;
    };

}
