#pragma once

/*
 * Auxiliary functions that used in several modules. 
 */
namespace Utils {  
// Increases current_year by 1, bypassing the value 0.
constexpr int inc_year(int current_year) {
  return current_year == -1 ? 1 : ++current_year;
}

// Decreases current_year by 1, bypassing the value 0.
constexpr int dec_year(int current_year) {
  return current_year == 1 ? -1 : --current_year;
}
}  // namespace Utils