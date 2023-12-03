#include <bit>

namespace cpp_practice::endianess {

///\brief endianess - byte ordering
enum class endianess { little_endian, big_endian, unknown };

///\brief return \b true if the system is little endian
constexpr bool is_little_endian() {
  return std::endian::native == std::endian::little;
}

///\brief return \b true if the system is big endian
constexpr bool is_big_endian() {
  return std::endian::native == std::endian::big;
}

///\brief return the endianess of the system
constexpr endianess get_endianess() {
  if (is_little_endian()) {
    return endianess::little_endian;
  } else if (is_big_endian()) {
    return endianess::big_endian;
  } else {
    return endianess::unknown;
  }
}

}  // namespace cpp_practice::endianess