#pragma once

#include "metis_core/data_queries.h"
#include "metis_core/data_set.h"

namespace metis::core {

    struct view_query {
        data_set &  owner;
        query_idx_t idx;

        auto & payload()              { return owner.buffers.canonical.query_payloads[idx];  }
        auto const & payload() const  { return owner.buffers.canonical.query_payloads[idx];  }
        auto & sort()                 { return owner.buffers.canonical.query_sort[idx];      }
        auto const & sort() const     { return owner.buffers.canonical.query_sort[idx];      }
        auto & relation()             { return owner.buffers.canonical.query_relations[idx]; }
        auto const & relation() const { return owner.buffers.canonical.query_relations[idx]; }
        auto & batch()                { return owner.buffers.canonical.query_batch[idx];     }
        auto const & batch() const    { return owner.buffers.canonical.query_batch[idx];     }
        auto & meta()                 { return owner.buffers.canonical.query_meta[idx];      }
        auto const & meta() const     { return owner.buffers.canonical.query_meta[idx];      }
        auto & stats()                { return owner.buffers.canonical.query_stats[idx];     }
        auto const & stats() const    { return owner.buffers.canonical.query_stats[idx];     }

        view_query(data_set& owner_, query_idx_t idx_)
        : owner(owner_), idx(idx_) { ; }
        view_query(view_query&&) = delete;
    };

}