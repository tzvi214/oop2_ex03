#include "Scalar.h"

#include <iostream>
#include "FileException.h"

Scalar::Scalar(int scalar)
 : m_scalar(scalar)
{ }


Operation::T Scalar::compute(const std::vector<T>& input) const
{
    return input.front() * m_scalar;
}


void Scalar::print(std::ostream& ostr, bool first_print) const
{
    (void)first_print; // Cast to void to avoid unused parameter warning
    ostr << "scal " << m_scalar;
}
