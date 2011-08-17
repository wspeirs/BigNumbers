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

#ifndef INTEGER_H
#define INTEGER_H

#include <vector>
#include <algorithm>

#include <sys/types.h>

using std::vector;
using std::min;
using std::max;

typedef vector<ulong> block_t;
typedef block_t::const_iterator block_const_it;
typedef block_t::iterator block_it;

class Integer {
    vector<ulong> blocks;
    char sign; ///< The sign of the integer: 1 = positive, -1 = negative

    public: Integer() : blocks(), sign(0) { }

    // Comparision functions
//    public: bool operator==(const Integer &rhs) const;
    public: bool operator==(ulong rhs) const;

    // Addition functions
    private: Integer add(const Integer &a, const Integer &b);
    public: Integer operator+(const Integer &b);

//    Integer operator+(const uint a, const Integer &b);
//    Integer operator+(const Integer &a, const uint b);
};

#endif
