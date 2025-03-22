#include "metis_core/data_set.h"
#include "metis_core/inc_tinyxml.h"

using namespace metis::core;

data_set::data_set()
: raw_allocator(std::make_unique<raw_allocator_t::element_type>())
{ ; }

data_set::~data_set() { ; }