#pragma once

/*
 *  ...
 */

 #include <memory_resource>
 #include <unordered_map>

 #include "data_queries.h"
 #include "data_family.h"

namespace tinyxml2 {
  class XMLDocument;
}

namespace metis::core {

    struct data_set_buffers {
        template<typename T>
        using array_t         = std::vector<T>;
        template<typename T>
        using smap_t          = std::unordered_map<std::string_view, T>;

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
            array_t<data_query_sort>         query_sort;
            array_t<data_query_relation>     query_relations;

            bool                             flag_maps_dirty;
        } canonical;
    };

    struct data_set {
        using raw_allocator_t = std::unique_ptr<std::pmr::monotonic_buffer_resource>;

        data_set_buffers buffers;
        
        raw_allocator_t raw_allocator;
        std::unique_ptr<tinyxml2::XMLDocument> loaded_xml;

        data_set();
        data_set(data_set&&) = delete;
        ~data_set();
    };

}
