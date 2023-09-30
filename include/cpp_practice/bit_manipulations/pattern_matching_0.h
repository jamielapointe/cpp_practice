/*
Write a function to find a 32-bit pattern in a uint8_t array. The pattern does
not have to be byte aligned.

Example 1:
uint32_t pattern = 0x00654321
uint8_t array[] = { 0xFF, 0xFF, 0x00, 0x65, 0x43, 0x21, 0xFF};
return: 16

Example 2:
uint32_t pattern = 0x00654321
uint8_t array[] = {0xFF, 0xFE, 0x00, 0xCA, 0x86, 0x43, 0xFF}
return 15
*/

/*
Binary Representations of Examples:
Pattern: 0000 0000 0110 0101 0100 0011 0010 0001

Example 1:
[1111 1111, 1111 1111, 0000 0000, 0110 0101, 0100 0011, 0010 0001, 1111 1111]
                       ^                                        ^

Example 2:
[1111 1111, 1111 1110, 0000 0000, 1100 1010, 1000 0110, 0100 0011, 1111 1111]
                    ^                                          ^
*/

#include <array>
#include <cstdint>

namespace cpp_practice::bit_manipulations::pattern_matching_0 {

///\brief Use a bit sliding window to find a pattern in an array of bytes
///\note window is allowed to cross byte boundaries
///\tparam array_length
template <uint32_t array_length>
class BitSlidingWindow {
 public:
  ///\brief Construct a new Bit Sliding Window object
  ///
  ///\param array - the data to search
  explicit BitSlidingWindow(std::array<uint8_t, array_length> array)
      : array_(array) {}

  ///\brief Determine if there is any more data to process
  ///
  ///\return true if there is more data to proccess
  ///\return false there is no more data to process
  bool has_more() const {
    return (current_bit_position() + kWindowSizeBits) <=
           (kArraySizeBytes * kBitsPerByte);
  }

  ///\brief get the current head bit position
  ///
  ///\return int the current head bit position
  int current_bit_position() const {
    return current_byte_ * kBitsPerByte + current_bit_in_byte_;
  }

  ///\brief slide the window down the array by 1 bit
  void slide_window() {
    ++current_bit_in_byte_;
    if (current_bit_in_byte_ >= kBitsPerByte) {
      current_bit_in_byte_ = 0;
      ++current_byte_;
    }
  }

  ///\brief slide the window down the array by 1 bit and return the data in the
  /// window
  ///
  ///\return uint32_t the data in the window
  uint32_t get_current_window() const {
    int current_byte = current_byte_;
    int current_bit_in_byte = current_bit_in_byte_;
    uint32_t result = 0;
    int bits_processed = 0;

    while (bits_processed < kWindowSizeBits) {
      if (current_byte >= kArraySizeBytes) break;

      // Number of bits left in the current byte
      int bits_left = kBitsPerByte - current_bit_in_byte;
      // Number of bits needed from the current byte
      int bits_needed = std::min(kWindowSizeBits - bits_processed, bits_left);

      // Extract bits from the current byte
      uint32_t byte_part =
          get_byte_part(bits_needed, current_byte, current_bit_in_byte);

      // Add the extracted bits to the result
      result |=
          (byte_part << get_result_r_shift_value(bits_processed, bits_needed));

      bits_processed += bits_needed;
      current_bit_in_byte += bits_needed;

      // Move to the next byte if necessary
      if (current_bit_in_byte >= kBitsPerByte) {
        current_bit_in_byte = 0;
        ++current_byte;
      }
    }

    return result;
  }

 private:
  std::array<uint8_t, array_length> array_;
  int current_bit_in_byte_ = 0;
  int current_byte_ = 0;

  static constexpr int kBitsPerByte = 8;
  static constexpr int kWindowSizeBits = 32;
  static constexpr int kArraySizeBytes = static_cast<int>(array_length);

  static int get_result_r_shift_value(int bits_processed, int bits_needed) {
    return (kWindowSizeBits - bits_processed - bits_needed);
  }

  static int get_byte_r_shift_value(int bits_needed, int current_bit_in_byte) {
    return (kBitsPerByte - current_bit_in_byte - bits_needed);
  }

  static uint32_t get_byte_mask(int bits_needed) {
    return ((static_cast<uint32_t>(1) << static_cast<uint32_t>(bits_needed)) -
            static_cast<uint32_t>(1));
  }

  uint32_t get_byte_part(int bits_needed, int current_byte,
                         int current_bit_in_byte) const {
    return (static_cast<uint32_t>(
                array_.at(static_cast<std::size_t>(current_byte))) >>
            static_cast<uint32_t>(
                get_byte_r_shift_value(bits_needed, current_bit_in_byte))) &
           get_byte_mask(bits_needed);
  }
};

///\brief Find a pattern in an array of bytes
/// The pattern can be anywhere in the contiguous bits of the array, even
/// crossing byte boundaries
///\tparam array_length
///\param pattern - the pattern to search for
///\param array - the array to search
///\return int - the bit position of the pattern, or -1 if the pattern was not
template <uint32_t array_length>
int find_pattern(uint32_t pattern,
                 std::array<uint8_t, array_length> const& array) {
  BitSlidingWindow<array_length> window(array);
  while (window.has_more()) {
    uint32_t value = window.get_current_window();
    if (value == pattern) {
      return window.current_bit_position();
    }
    window.slide_window();
  }

  return -1;  // could not find the pattern
}

}  // namespace cpp_practice::bit_manipulations::pattern_matching_0
