#include "metis_core/data_family.h"

#include "douceurs/render_string.h"

using namespace metis::core;
namespace ds = douceurs::strings;

template<typename style_t>
void metis::core::data_discipline_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         ds::fallback(this->id,                  "[nameless]"),
      "display",    ds::fallback(this->display, this->id,   "[nameless]"),
      "sort",       ds::fallback(this->sort,    this->sort, "[nameless]")
    );
}

template<typename style_t>
void metis::core::data_family_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         ds::fallback(this->id,                  "[nameless]"),
      "display",    ds::fallback(this->display, this->id,   "[nameless]"),
      "sort",       ds::fallback(this->sort,    this->sort, "[nameless]")
    );
}

template<typename style_t>
void metis::core::data_family_relation::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "discipline", ds::fallback(this->discipline,          "[none]")
    );
}

template<typename style_t>
void metis::core::data_subject_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         ds::fallback(this->id,                  "[nameless]"),
      "display",    ds::fallback(this->display, this->id,   "[nameless]"),
      "sort",       ds::fallback(this->sort,    this->sort, "[nameless]")
    );
}

template<typename style_t>
void metis::core::data_subject_relation::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "family",     ds::fallback(this->family,              "[none]")
    );
}