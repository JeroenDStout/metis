#include "metis_core/proc_io_legacy.h"

#include "douceurs/render_string.h"

using namespace metis::core;
namespace ds = douceurs::strings;

template<typename style_t>
void metis::core::proc_io_legacy::load_stats::debug_string(std::stringstream& ss) const
{
    ds::render_dbg_vars<style_t>(ss,
      "read",  this->read_time_ms,
      "parse", this->parse_time_ms,
      "total", this->total_time_ms
    );
}