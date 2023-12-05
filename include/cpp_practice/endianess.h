#include <bit>

namespace cpp_practice::endianess {

///\brief endianess - byte ordering
enum class endianess { little_endian, big_endian, mixed_endian };

///\brief return \b true if the system is little endian
constexpr bool is_little_endian() {
  return std::endian::native == std::endian::little;
}

///\brief return \b true if the system is big endian
constexpr bool is_big_endian() {
  return std::endian::native == std::endian::big;
}

///\brief return \b true if the system is mixed endian
///\note only the PDP-11 architecture is mixed endian to the best of my
/// knowledge
constexpr bool is_mixed_endian() {
  return !is_little_endian() && !is_big_endian();
}

///\brief return the endianess of the system
constexpr endianess get_endianess() {
  if constexpr (is_little_endian()) {
    return endianess::little_endian;
  }

  if constexpr (is_big_endian()) {
    return endianess::big_endian;
  }

  if constexpr (is_mixed_endian()) {
    return endianess::mixed_endian;
  }

  // Note that it must be one of the options, so this is unreachable.
  // If for some reason all are false, then we get a compiler error.
}

}  // namespace cpp_practice::endianess