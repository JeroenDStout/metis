#include "metis_core/data_family.h"

#include "douceurs/render_string.h"

using namespace metis::core;
namespace ds = douceurs::strings;

template<typename style_t>
void metis::core::data_discipline_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         this->id,
      "display",    this->display,
      "sort",       this->sort
    );
}

template<typename style_t>
void metis::core::data_family_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         this->id,
      "display",    this->display,
      "sort",       this->sort
    );
}

template<typename style_t>
void metis::core::data_family_relation::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "discipline", this->discipline
    );
}

template<typename style_t>
void metis::core::data_subject_names::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "id",         this->id,
      "display",    this->display,
      "sort",       this->sort
    );
}

template<typename style_t>
void metis::core::data_subject_relation::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "family",     this->family
    );
}
