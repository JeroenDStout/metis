#include "metis_core/proc_io_legacy.h"

#include <chrono>
#include <iostream>

#include "douceurs/def_value.h"
#include "douceurs/ref_value.h"
#include "douceurs/slurp.h"
#include "douceurs/template_buffer_alloc.h"
#include "douceurs/render_string.h"

#include "metis_core/proc_set.h"
#include "metis_core/inc_tinyxml.h"

using namespace metis::core;

void proc_io_legacy::load_from_path(metis::core::data_set &out_set, load_stats *out_stats, std::string_view path) const
{
    namespace d = douceurs;
    
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
    
    tinyxml2::XMLDocument document;
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
        auto *xml_groups      = find_child(xml_set, "groups");
        auto *xml_megagroups  = find_child(xml_set, "megaGroups");
        auto *xml_omegagroups = find_child(xml_set, "omegaGroups");
        
        // Omegagroups -> Disciplines
        for (auto* xml_group = xml_omegagroups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");

            auto name      = con_str_alloc(c_name,         "[nameless]");
            auto display   = con_str_alloc(c_display_name, name);
            auto sort      = con_str_alloc(c_sort_name,    name);

            auto idx = proc_set.add_discipline(out_set);
            out_set.buffers.canonical.discipline_names[idx].id         = name;
            out_set.buffers.canonical.discipline_names[idx].display    = display;
            out_set.buffers.canonical.discipline_names[idx].sort       = sort;
        }

        // Megagroups -> Families
        for (auto* xml_group = xml_megagroups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");
            char const* c_omega_group  = xml_group->ToElement()->Attribute("omegaGroup");
            
            auto name       = con_str_alloc(c_name,         "[nameless]");
            auto display    = con_str_alloc(c_display_name, name);
            auto sort       = con_str_alloc(c_sort_name,    name);
            auto discipline = con_str_alloc(c_omega_group,  "[parentless]");

            auto idx = proc_set.add_family(out_set);
            out_set.buffers.canonical.family_names[idx].id             = name;
            out_set.buffers.canonical.family_names[idx].display        = display;
            out_set.buffers.canonical.family_names[idx].sort           = sort;
            out_set.buffers.canonical.family_relations[idx].discipline = discipline;
        }

        // Groups -> Subjects
        for (auto* xml_group = xml_groups->FirstChild(); xml_group; xml_group = xml_group->NextSibling()) {
            char const* c_name         = xml_group->ToElement()->Attribute("name");
            char const* c_display_name = xml_group->ToElement()->Attribute("displayName");
            char const* c_sort_name    = xml_group->ToElement()->Attribute("sortName");
            char const* c_mega_group   = xml_group->ToElement()->Attribute("megaGroup");
            
            auto name       = con_str_alloc(c_name,         "[nameless]");
            auto display    = con_str_alloc(c_display_name, name);
            auto sort       = con_str_alloc(c_sort_name,    name);
            auto family     = con_str_alloc(c_mega_group,  "[parentless]");

            auto idx = proc_set.add_subject(out_set);
            out_set.buffers.canonical.subject_names[idx].id            = name;
            out_set.buffers.canonical.subject_names[idx].display       = display;
            out_set.buffers.canonical.subject_names[idx].sort          = sort;
            out_set.buffers.canonical.subject_relations[idx].family    = family;
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