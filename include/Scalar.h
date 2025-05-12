#pragma once

#include "UnaryOperation.h"


// Represents the identity operation
// Returns the same set that it gets as input
// Used as the leaf in every operation tree
class Scalar : public UnaryOperation
{
public:
    Scalar(int scalar);// to check if scalar < MAX_SCAL_SIZE
    T compute(const std::vector<T>& input) const override;
    void print(std::ostream& ostr, bool first_print = false) const override;

private:
    int m_scalar;
};
