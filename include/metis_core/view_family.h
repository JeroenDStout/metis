#pragma once

#include "metis_core/data_queries.h"

#include "metis_core/data_set.h"


namespace metis::core {

    struct view_discipline {
        data_set &       owner;
        discipline_idx_t idx;

        auto &       names()       { return owner.buffers.canonical.discipline_names[idx]; }
        auto const & names() const { return owner.buffers.canonical.discipline_names[idx]; }
        auto &       meta()        { return owner.buffers.canonical.discipline_meta[idx];  }
        auto const & meta() const  { return owner.buffers.canonical.discipline_meta[idx];  }

        view_discipline(data_set& owner_, discipline_idx_t idx_)
        : owner(owner_), idx(idx_) { ; }
        view_discipline(view_discipline&&) = delete;
    };

    struct view_family {
        data_set &       owner;
        family_idx_t     idx;

        auto &       names()           { return owner.buffers.canonical.family_names[idx];     }
        auto const & names() const     { return owner.buffers.canonical.family_names[idx];     }
        auto &       meta()            { return owner.buffers.canonical.family_meta[idx];      }
        auto const & meta() const      { return owner.buffers.canonical.family_meta[idx];      }
        auto &       relations()       { return owner.buffers.canonical.family_relations[idx]; }
        auto const & relations() const { return owner.buffers.canonical.family_relations[idx]; }

        view_family(data_set& owner_, family_idx_t idx_)
        : owner(owner_), idx(idx_) { ; }
        view_family(view_family&&) = delete;
    };

    struct view_subject {
        data_set &       owner;
        subject_idx_t    idx;

        auto & names()                 { return owner.buffers.canonical.subject_names[idx];     }
        auto const & names() const     { return owner.buffers.canonical.subject_names[idx];     }
        auto & meta()                  { return owner.buffers.canonical.subject_meta[idx];      }
        auto const & meta() const      { return owner.buffers.canonical.subject_meta[idx];      }
        auto & relations()             { return owner.buffers.canonical.subject_relations[idx]; }
        auto const & relations() const { return owner.buffers.canonical.subject_relations[idx]; }

        view_subject(data_set& owner_, family_idx_t idx_)
        : owner(owner_), idx(idx_) { ; }
        view_subject(view_subject&&) = delete;
    };

}