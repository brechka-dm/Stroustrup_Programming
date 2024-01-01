#pragma once

#include <stdexcept>
#include <string>

void inline error(const std::string& message) {
  throw std::runtime_error(message);
  exit(1);
}