#include "metis_core/data_queries.h"

#include "douceurs/render_string.h"

template<typename style_t>
void metis::core::data_query_payload::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "question", this->question,
      "answer",   this->answer
    );
}

template<typename style_t>
void metis::core::data_query_sort::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "sort",    this->sort_elements
    );
}

template<typename style_t>
void metis::core::data_query_relation::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "subject", this->subject,
      "group",   this->group
    );
}
