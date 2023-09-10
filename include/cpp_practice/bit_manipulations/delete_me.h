#include <bitset>
#include <iostream>
#include <vector>

class BitSlidingWindow {
 private:
  const std::vector<uint8_t>& data;
  int current_byte = 0;
  int current_bit = 0;
  int window_size;

 public:
  BitSlidingWindow(const std::vector<uint8_t>& data_in, int window_size_in)
      : data(data_in), window_size(window_size_in) {}

  // Returns true if there's more data to be processed
  bool has_more() const {
    return (current_byte * 8 + current_bit + window_size) <= (data.size() * 8);
  }

  // Slide the window to the next position and get the data in that window as an
  // integer
  uint32_t next_window() {
    uint32_t result = 0;
    int bits_processed = 0;

    while (bits_processed < window_size) {
      if (current_byte >= data.size()) break;

      // Number of bits left in the current byte
      int bits_left = 8 - current_bit;
      // Number of bits needed from the current byte
      int bits_needed = std::min(window_size - bits_processed, bits_left);

      // Extract bits from the current byte
      uint32_t byte_part =
          (data[current_byte] >> (8 - current_bit - bits_needed)) &
          ((1 << bits_needed) - 1);
      result |= (byte_part << (window_size - bits_processed - bits_needed));

      bits_processed += bits_needed;
      current_bit += bits_needed;

      // Move to the next byte if necessary
      if (current_bit >= 8) {
        current_bit = 0;
        current_byte++;
      }
    }
    return result;
  }
};

int main() {
  std::vector<uint8_t> data = {0b10101010, 0b11001100, 0b11110000};
  BitSlidingWindow window(data, 5);  // 5-bit sliding window

  while (window.has_more()) {
    uint32_t value = window.next_window();
    std::bitset<5> bits(value);
    std::cout << bits << std::endl;
  }

  return 0;
}
