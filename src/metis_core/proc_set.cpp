#include <iostream>

#include "douceurs/render_string.h"

#include "metis_core/proc_set.h"
#include "metis_core/data_set.h"

using namespace metis::core;

std::string_view proc_set::alloc(data_set &set, std::string_view const &str) const
{
    void *raw_data = set.raw_allocator->allocate(str.length());
    std::memcpy(raw_data, str.data(), str.length());

    if (verbose_logging)
        std::cout << "Allocating string '" << str << "'" << std::endl;

    return std::string_view((const char*)raw_data, str.length());
}

auto proc_set::alloc(data_set &set, string_view_span const &view_span) const -> string_view_span
{
    void *raw_data = set.raw_allocator->allocate(view_span.size_bytes());
    string_view_span span{ (std::string_view*)raw_data, view_span.size() };

    for (auto dst = span.begin(), src = view_span.begin(); dst != span.end(); ++dst, ++src)
        *dst = alloc(set, *src);

    if (verbose_logging)
        std::cout << "Allocated string span with " << span.size() << " elements" << std::endl;

    return span;
}

auto proc_set::add_discipline(data_set &set) const -> discipline_idx_t
{
    set.buffers.meta.flag_maps_dirty = true;

    set.buffers.canonical.discipline_names.push_back({});
    set.buffers.canonical.discipline_meta.push_back({});
    auto ret = query_idx_t(set.buffers.canonical.discipline_names.size() - 1);

    if (verbose_logging)
        std::cout << "Added discipline at idx " << std::to_string(ret) << std::endl;

    return ret;
}

auto proc_set::add_family(data_set &set) const -> family_idx_t
{
    set.buffers.meta.flag_maps_dirty = true;

    set.buffers.canonical.family_names.push_back({});
    set.buffers.canonical.family_relations.push_back({});
    set.buffers.canonical.family_meta.push_back({});
    auto ret = query_idx_t(set.buffers.canonical.family_names.size() - 1);

    if (verbose_logging)
        std::cout << "Added family at idx " << std::to_string(ret) << std::endl;

    return ret;
}

auto proc_set::add_subject(data_set &set) const -> subject_idx_t
{
    set.buffers.meta.flag_maps_dirty = true;

    set.buffers.canonical.subject_names.push_back({});
    set.buffers.canonical.subject_relations.push_back({});
    set.buffers.canonical.subject_meta.push_back({});
    auto ret = query_idx_t(set.buffers.canonical.subject_names.size() - 1);

    if (verbose_logging)
        std::cout << "Added subject at idx " << std::to_string(ret) << std::endl;

    return ret;
}

auto proc_set::add_query(data_set &set) const -> query_idx_t
{
    set.buffers.canonical.query_payloads.push_back({});
    set.buffers.canonical.query_relations.push_back({});
    set.buffers.canonical.query_sort.push_back({});
    set.buffers.canonical.query_batch.push_back({});
    set.buffers.canonical.query_stats.push_back({});
    set.buffers.canonical.query_meta.push_back({});

    auto ret = query_idx_t(set.buffers.canonical.query_payloads.size() - 1);

    if (verbose_logging)
        std::cout << "Added query at idx " << std::to_string(ret) << std::endl;

    return ret;
}
