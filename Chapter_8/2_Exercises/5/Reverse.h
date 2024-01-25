#pragma once

#include <vector>

/*
 * Creates a new vector with a changed order of elements. The
 * original vector is not changed.
 */
std::vector<int> reverse_immut(const std::vector<int>& vector);

/*
 * Changes the order of elements in the passed vector.
 */
void reverse_mut(std::vector<int>& vector);