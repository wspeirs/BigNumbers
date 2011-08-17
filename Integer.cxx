/*
 * This file is part of BigNumbers.
 *
 * BigNumbers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BigNumbers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BigNumbers.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Integer.h"

bool Integer::operator==(ulong rhs) const
{
    if(blocks.size() != 1 || blocks[0] != rhs)
        return false;
    else
        return true;
}

Integer Integer::add(const Integer &a, const Integer &b)
{
    Integer r;
    ulong carry = 0;
    size_t min_blocks = min(a.blocks.size(), b.blocks.size());
    size_t i;

    for(i=0; i < min_blocks; ++i)
    {
        r.blocks.push_back(a.blocks[i] + b.blocks[i] + carry);
        carry = (r.blocks[i] < b.blocks[i] ? 1 : 0);
    }

    block_const_it it;

    if(a.blocks.size() > b.blocks.size())
    {
        it = a.blocks.begin() + i;
        min_blocks = a.blocks.size();
    }

    else if(a.blocks.size() < b.blocks.size())
    {
        it = b.blocks.begin() + i;
        min_blocks = b.blocks.size();
    }

    for( ; i < min_blocks; ++i)
    {
        r.blocks.push_back(*(it++) + carry);
        carry = (r.blocks[i] == 0 ? 1 : 0);
    }

    if(carry != 0)
        r.blocks.push_back(carry);

    return r;
}

Integer Integer::operator+(const Integer &b)
{
    if(*this == 0)
        return b;
    if(b == 0)
        return *this;

    // same sign
    if(sign == b.sign)
    {
        Integer r = add(*this, b);
        r.sign = b.sign;
        return r;
    }

    // this is negative
/*
   if(sign == -1)
    {
        sign = 1;
        Integer r = sub(b, *this);
        sign = -1;
        return r;
    }

    // b is negative
    if(b.sign == -1)
    {
        b.sign = 1;
        Integer r = sub(*this, b);
        b.sign = -1;
        return r;
    }
*/
}
