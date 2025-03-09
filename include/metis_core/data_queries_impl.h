#include "metis_core/data_queries.h"

#include "douceurs/render_string.h"

template<typename style_t>
void metis::core::data_query_payload::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "question", ds::fallback(this->question, "[none]"),
      "answer",   ds::fallback(this->answer,   "[none]")
    );
}

template<typename style_t>
void metis::core::data_query_relation::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "subject",  ds::fallback(this->subject,  "[none]"),
      "group",    ds::fallback(this->group,    "[none]")
    );
}