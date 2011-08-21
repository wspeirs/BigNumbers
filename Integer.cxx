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

#include <stdio.h>

Integer::Integer(const string &hex) : blocks(), sign(0)
{
    string::const_iterator it = hex.begin();

    if(*it == '-')
    {
        sign = -1;
        ++it;
    }

    else
        sign = 1;

    if(*it == '0' && *(it+1) == 'x')
        it += 2;

    size_t len = hex.end() - it;
    size_t size = len/8 + (len%8 == 0 ? 0 : 1);
    int i = size - 1;

    blocks.resize(size);

    if(len%8 != 0)
    {
        char format[5];

        sprintf(format, "%%0%dX", len%8);
        sscanf(hex.substr(it-hex.begin()).c_str(), format, &(blocks[size-1]));

        it += len%8;
        --i;
    }


    for( ; i >= 0; --i)
    {
        sscanf(hex.substr(it-hex.begin()).c_str(), "%08X", &(blocks[i]));

        it += 8;
    }

    // might need a resize here
}

int Integer::cmp(const Integer &b) const
{
    if(sign == b.sign)
        return sign == 1 ? cmp_abs(b) : -1 * cmp_abs(b);

    return sign;
}

int Integer::cmp_abs(const Integer &b) const
{
    if(blocks.size() > b.blocks.size())
        return 1;

    else if(blocks.size() < b.blocks.size())
        return -1;

    else
    {
        for(int i=blocks.size()-1; i >= 0; --i)
        {
            if(blocks[i] != b.blocks[i])
                return blocks[i] > b.blocks[i] ? 1 : -1;
        }
    }

    return 0;
}

Integer Integer::add(const Integer &a, const Integer &b)
{
    Integer r;
    ulong carry = 0;
    size_t min_blocks = min(a.blocks.size(), b.blocks.size());
    size_t i;

    r.blocks.reserve(max(a.blocks.size(), b.blocks.size()) + 1);

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
    else if(sign == -1)
    {
        sign = 1;
        Integer r = sub(b, *this);
        sign = -1;
        return r;
    }

    // b is negative
    else
    {
        b.sign = 1;
        Integer r = sub(*this, b);
        b.sign = -1;
        return r;
    }
}

Integer Integer::sub(const Integer &a, const Integer &b)
{
    Integer r;
    ulong barrow = 0, nextBarrow = 0;
    size_t min_blocks = min(a.blocks.size(), b.blocks.size());
    size_t i;

    r.blocks.reserve(max(a.blocks.size(), b.blocks.size()) + 1);

    for(i=0; i < min_blocks; ++i)
    {
        nextBarrow = ( a.blocks[i] < (b.blocks[i] + barrow) ? 1 : 0 );

        r.blocks.push_back(a.blocks[i] - b.blocks[i] - barrow);

        barrow = nextBarrow;
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
        r.blocks.push_back(*(it++) - barrow);
        barrow = (r.blocks[i] == 0xFFFFFFFF ? 1 : 0);
    }

    return r;
}

Integer Integer::operator-(const Integer &b)
{
    if(*this == 0)
    {
        Integer r = b;
        r.sign = -1 * b.sign;
        return r;
    }

    if(b == 0)
    {
        return *this;
    }

    if(this->sign != b.sign)
    {
        return *this + b;
    }

    else
    {
        int cmp = this->cmp(b);

        if(cmp == 0)
            return Integer(0);
        else if(cmp > 0)
            return sub(*this, b);
        else
            return add(b, *this);
    }
}

