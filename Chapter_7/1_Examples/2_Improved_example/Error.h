#pragma once

#include <stdexcept>
#include <string>

/*
 * Throws std::runtime_error with specified message.
 */
void inline error(const std::string& message) {
  throw std::runtime_error(message);
  exit(1);
}