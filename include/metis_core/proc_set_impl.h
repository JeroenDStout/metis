#include "metis_core/data_set.h"
#include "metis_core/data_family_impl.h"
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
void metis::core::proc_set_dbg_string<style_t>::debug_string_discipline(std::stringstream &ss, view_discipline const &view) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&view](auto &ss) { view.names().debug_string<style_t>(ss); },
      "meta",           [&view](auto &ss) { view.meta().debug_string<style_t>(ss);  }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_family(std::stringstream &ss, view_family const &view) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&view](auto &ss) { view.names().debug_string<style_t>(ss);     },
      "meta",           [&view](auto &ss) { view.meta().debug_string<style_t>(ss);      },
      "relations",      [&view](auto &ss) { view.relations().debug_string<style_t>(ss); }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_subject(std::stringstream &ss, view_subject const &view) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "names",          [&view](auto &ss) { view.names().debug_string<style_t>(ss);     },
      "meta",           [&view](auto &ss) { view.meta().debug_string<style_t>(ss);      },
      "relations",      [&view](auto &ss) { view.relations().debug_string<style_t>(ss); }
    );
}

template<typename style_t>
void metis::core::proc_set_dbg_string<style_t>::debug_string_query(std::stringstream &ss, view_query const &view) const
{
    douceurs::strings::render_dbg_vars<style_t>(ss,
      "payload",        [&view](auto &ss) { view.payload().debug_string<style_t>(ss);  },
      "meta",           [&view](auto &ss) { view.meta().debug_string<style_t>(ss);     },
      "sort",           [&view](auto &ss) { view.sort().debug_string<style_t>(ss);     },
      "relations",      [&view](auto &ss) { view.relation().debug_string<style_t>(ss); },
      "batch",          [&view](auto &ss) { view.batch().debug_string<style_t>(ss);    },
      "stats",          [&view](auto &ss) { view.stats().debug_string<style_t>(ss);    },
      "meta",           [&view](auto &ss) { view.meta().debug_string<style_t>(ss);     }
    );
}
