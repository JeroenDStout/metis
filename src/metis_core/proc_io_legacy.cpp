#include "metis_core/proc_io_legacy.h"

#include "metis_core/view_family.h"
#include "metis_core/view_queries.h"
#include "metis_core/proc_set.h"
#include "metis_core/inc_tinyxml.h"

#include "douceurs/def_value.h"
#include "douceurs/ref_value.h"
#include "douceurs/slurp.h"
#include "douceurs/template_buffer_alloc.h"
#include "douceurs/render_string.h"
#include "douceurs/string_view_manip.h"
#include "douceurs/string_conv.h"
#include "douceurs/string_conv_chrono.h"

#include <array>
#include <chrono>
#include <iostream>

using namespace metis::core;

void proc_io_legacy::load_from_path(metis::core::data_set &out_set, load_stats *out_stats, std::string_view path) const
{
    namespace d  = douceurs;
    namespace ds = douceurs::strings;
    
    if (verbose_logging)
      std::cout << "proc_io_legacy::load_from_path from " << path << " started" << std::endl;

    // Time helpers
    auto get_time_now   = [] {
      return std::chrono::high_resolution_clock::now();
    };
    auto duration_in_ms = [](auto t1, auto t2) {
      return std::uint32_t(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
    };

    // Function constants
    metis::core::proc_set proc_set{ .verbose_logging = false };
    bool const write_stats = out_stats != nullptr;
    bool const gen_stats   = write_stats || verbose_logging;
    std::string const path_str(path);
    std::string buffer;
    
    auto t_start = d::value::con_invoke(gen_stats, get_time_now);

    // -- Slurp file
    
    auto slurp_ret = d::io::slurp(d::value::keep(d::memory::buf_std(buffer)), std::string(path));
    if (d::io::is_failure(slurp_ret)) {
        std::cout << "Could not load " << path;
        return;
    }
    
    auto t_slurp_done = d::value::con_invoke(gen_stats, get_time_now);
    if (gen_stats) {
        auto ms = duration_in_ms(t_start, t_slurp_done);
        if (verbose_logging) std::cout << "Finished reading in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->read_time_ms = ms;
    }

    // -- Parse as XML
    
    auto& document = *(out_set.loaded_xml = std::make_unique<tinyxml2::XMLDocument>());
    bool success = (tinyxml2::XML_SUCCESS == document.Parse(buffer.data(), buffer.size()));
    if (!success) {
        std::cout << "Could not parse " << path;
        return;
    }
    
    auto t_parse_done = d::value::con_invoke(gen_stats, get_time_now);
    if (gen_stats) {
        auto ms = duration_in_ms(t_slurp_done, t_parse_done);
        if (verbose_logging) std::cout << "Finished parsing xml in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->parse_time_ms = ms;
    }

    // -- Interpret
    
    {
        auto find_child = [](auto const *elem, char const *name) -> tinyxml2::XMLNode const * {
            for (auto *entry = elem->FirstChild(); entry; entry = entry->NextSibling()) {
                if (0 == strcmp(entry->Value(), name))
                  return entry;
            }
            return nullptr;
        };
        auto con_str_alloc = [&](char const* name, std::string_view fallback) {
            if (name != nullptr)
              return proc_set.alloc(out_set, name);
            return fallback;
        };

        auto *xml_root        = document.RootElement();
        auto *xml_set         = find_child(xml_root, "set");
        auto *xml_omegagroups = find_child(xml_set, "omegaGroups");
        auto *xml_megagroups  = find_child(xml_set, "megaGroups");
        auto *xml_groups      = find_child(xml_set, "groups");
        auto *xml_terms       = find_child(xml_set, "terms");
        
        // Omegagroups -> Disciplines
        for (auto* xml_group = xml_omegagroups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");
            
            auto name =  d::strings::fallback(c_name, "[nameless]");
            
            view_discipline view{ out_set, proc_set.add_discipline(out_set) };
            view.names().id      = name;
            view.names().display = d::strings::fallback(c_display_name, name);
            view.names().sort    = d::strings::fallback(c_sort_name,    name);
        }

        // Megagroups -> Families
        for (auto* xml_group = xml_megagroups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");
            char const* c_omega_group  = xml_group->ToElement()->Attribute("omegaGroup");
            
            auto name =  d::strings::fallback(c_name, "[nameless]");

            view_family view{ out_set, proc_set.add_family(out_set) };
            view.names().id             = name;
            view.names().display        = d::strings::fallback(c_display_name, name);
            view.names().sort           = d::strings::fallback(c_sort_name,    name);
            view.relations().discipline = d::strings::fallback(c_omega_group,  "[no_discipline]");
        }

        // Groups -> Subjects
        for (auto* xml_group = xml_groups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");
            char const* c_mega_group   = xml_group->ToElement()->Attribute("megaGroup");

            auto name =  d::strings::fallback(c_name, "[nameless]");
            
            view_subject view{ out_set, proc_set.add_subject(out_set) };
            view.names().id         = name;
            view.names().display    = d::strings::fallback(c_display_name, name);;
            view.names().sort       = d::strings::fallback(c_sort_name,    name);
            view.relations().family = d::strings::fallback(c_mega_group, "[no_family]");
        }

        // Terms -> Queries
        for (auto *xml_term = xml_terms->FirstChild(); xml_term; xml_term = xml_term->NextSibling()) {
            auto *base = find_child(xml_term, "base")->ToElement();

            char const* c_group     = base->Attribute("g");
            char const* c_question  = base->Attribute("q");
            char const* c_answer    = base->Attribute("a");
            char const* c_subgroup  = base->Attribute("sg");
            char const* c_subsort   = base->Attribute("ss");
            char const* c_sensitive = base->Attribute("sensitive");
            
            view_query view{ out_set, proc_set.add_query(out_set) };
            view.payload().question = d::strings::fallback(c_question);
            view.payload().answer   = d::strings::fallback(c_answer);
            view.relation().subject = d::strings::fallback(c_group);
            view.relation().group   = d::strings::fallback(c_subgroup);

            if (c_subsort != nullptr) {
                std::array<std::string_view, 1> span = { std::string_view{c_subsort} };
                view.sort().sort_elements = proc_set.alloc(out_set, span);
            }
            if (c_sensitive != nullptr) {
                std::array<std::string_view, 1> span = { std::string_view{"sensitive"} };
                view.meta().tags          = proc_set.alloc(out_set, span);
            }

            auto *stat = find_child(xml_term, "stat")->ToElement();
            
            char const* c_potato              = stat->Attribute("potato");
            char const* c_query_last_asked    = stat->Attribute("dateLastQuery");
            char const* c_query_add_time      = stat->Attribute("dateAdded");
            char const* c_query_count_all     = stat->Attribute("queryCount");
            char const* c_query_count_mistake = stat->Attribute("mistakeCount");
            char const* c_batch_base          = stat->Attribute("batch");
            char const* c_batch_penalty       = stat->Attribute("batchPenalty");
            char const* c_batch_penalty_heavy = stat->Attribute("batchPenaltyHeavy");
            char const* c_batch_rng           = stat->Attribute("rng");
            
            view.batch().is_active            = true;
            view.batch().is_potato            = ds::convert_to<std::uint32_t>(ds::fallback(c_potato),              (std::uint32_t)0) != 0;
            view.batch().query_last_tp        = ds::to_chrono<timepoint_d_t>(ds::fallback(c_query_last_asked), "%F %T", {});
            view.batch().timeout              = 0;
            view.batch().batch_base           = ds::convert_to<float>(ds::fallback(c_batch_base),                  0.f);
            view.batch().batch_penalty_slow   = ds::convert_to<float>(ds::fallback(c_batch_penalty),               0.f);
            view.batch().batch_penalty_fast   = ds::convert_to<float>(ds::fallback(c_batch_penalty_heavy),         0.f);
            view.batch().batch_rng            = ds::convert_to<float>(ds::fallback(c_batch_rng),                   0.f);

            view.stats().query_add_time       = ds::to_chrono<timepoint_d_t>(ds::fallback(c_query_add_time), "%F %T", {});
            view.stats().count_query_all      = ds::convert_to<std::uint32_t>(ds::fallback(c_query_count_all),     (std::uint32_t)0);
            view.stats().count_query_mistake  = ds::convert_to<std::uint32_t>(ds::fallback(c_query_count_mistake), (std::uint32_t)0);
        }
    }

    auto t_interpret_done = d::value::con_invoke(gen_stats, get_time_now);
    if (gen_stats) {
        auto ms = duration_in_ms(t_parse_done, t_interpret_done);
        if (verbose_logging) std::cout << "Finished interpreting xml in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->interpret_time_ms = ms;
    }

    // -- Finish up

    if (gen_stats) {
        auto ms = duration_in_ms(t_start, t_interpret_done);
        if (verbose_logging) std::cout << "Finished loading in " << ms << "ms" << std::endl;
        if (write_stats)     out_stats->total_time_ms = ms;
    }
    
    if (verbose_logging)
      std::cout << "proc_io_legacy::load_from_path " << path << " completed" << std::endl;
}