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

template<typename style_t>
void metis::core::data_query_batch::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "query_last_tp",      this->query_last_tp,
      "batch_base",         this->batch_base,
      "batch_penalty_slow", this->batch_penalty_slow,
      "batch_penalty_fast", this->batch_penalty_fast,
      "batch_rng",          this->batch_rng
    );
}

template<typename style_t>
void metis::core::data_query_meta::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "flags",        this->flags
    );
}

template<typename style_t>
void metis::core::data_query_stats::debug_string(std::stringstream &ss) const
{
    namespace ds = douceurs::strings;

    ds::render_dbg_vars<style_t>(ss,
      "query_add_time",      this->query_add_time,
      "count_query_all",     this->count_query_all,
      "count_query_mistake", this->count_query_mistake
    );
}
