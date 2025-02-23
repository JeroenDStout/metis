#include <iostream>

#include "metis_core/proc_set.h"

#include "metis_core/data_set.h"

using namespace metis::core;

std::string_view proc_set::alloc(data_set &set, std::string_view const &str) const
{
    void *raw_data = set.buffers.raw_allocator->allocate(str.length());
    std::memcpy(raw_data, str.data(), str.length());

    if (verbose_logging)
        std::cout << "Allocating string '" << str << "'" << std::endl;

    return std::string_view((const char*)raw_data, str.length());
}

query_idx_t proc_set::add_query(data_set &set) const
{
    set.buffers.query_payloads.push_back({});
    auto ret = query_idx_t(set.buffers.query_payloads.size() - 1);

    if (verbose_logging)
        std::cout << "Added query at idx " << std::to_string(ret) << std::endl;

    return ret;
}