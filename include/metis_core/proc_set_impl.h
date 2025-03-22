#include "metis_core/data_set.h"
#include "metis_core/proc_set.h"

#include "douceurs/render_string.h"

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_stats(std::stringstream &ss, data_set const &set) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "disciplines", set.buffers.canonical.discipline_names.size(),
      "families",    set.buffers.canonical.family_names.size(),
      "subjects",    set.buffers.canonical.subject_names.size(),
      "queries",     set.buffers.canonical.query_payloads.size()
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_discipline(std::stringstream &ss, data_set const &set, discipline_idx_t idx) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&set, idx](auto &ss) { set.buffers.canonical.discipline_names[idx].debug_string<style_t>(ss); }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_family(std::stringstream &ss, data_set const &set, family_idx_t idx) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&set, idx](auto &ss) { set.buffers.canonical.family_names[idx].debug_string<style_t>(ss); },
      "relations",      [&set, idx](auto &ss) { set.buffers.canonical.family_relations[idx].debug_string<style_t>(ss); }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_subject(std::stringstream &ss, data_set const &set, subject_idx_t idx) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&set, idx](auto &ss) { set.buffers.canonical.subject_names[idx].debug_string<style_t>(ss); },
      "relations",      [&set, idx](auto &ss) { set.buffers.canonical.subject_relations[idx].debug_string<style_t>(ss); }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_query(std::stringstream &ss, data_set const &set, query_idx_t idx) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "payload",        [&set, idx](auto &ss) { set.buffers.canonical.query_payloads[idx].debug_string<style_t>(ss); },
      "sort",           [&set, idx](auto &ss) { set.buffers.canonical.query_sort[idx].debug_string<style_t>(ss); },
      "relations",      [&set, idx](auto &ss) { set.buffers.canonical.query_relations[idx].debug_string<style_t>(ss); }
    );
}
