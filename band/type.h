#pragma once

#include <type_traits>

namespace band {

template <typename Interface, typename Class>
using Implements = std::enable_if_t<std::is_convertible<Class*, Interface*>::value>;

}  // namespace band
