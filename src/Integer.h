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
#include <string>

#include <sys/types.h>

using std::vector;
using std::string;
using std::min;
using std::max;

typedef vector<ulong> block_t;
typedef block_t::const_iterator block_const_it;
typedef block_t::iterator block_it;

class Integer {
private:
    vector<ulong> blocks;
    mutable char sign; ///< The sign of the integer: 1 = positive, -1 = negative

    //
    // Internal functions
    //
    Integer add(const Integer &a, const Integer &b);
    Integer sub(const Integer &a, const Integer &b);
    
public:
    Integer() : blocks(), sign(0) { }
    Integer(const ulong arg) : blocks(), sign(1)
    { blocks.push_back(arg); }
    Integer(const string &hex);



    // Comparision functions
    bool operator==(const Integer &b) const
    { return this->cmp(b) == 0; }

    bool operator<(const Integer &b) const
    { return this->cmp(b) < 0; }

    bool operator>(const Integer &b) const
    { return this->cmp(b) > 0; }

    bool operator<=(const Integer &b) const
    { return this->cmp(b) <= 0; }
    
    bool operator>=(const Integer &b) const
    { return this->cmp(b) >= 0; }
    
    int cmp(const Integer &b) const;
    int cmp_abs(const Integer &b) const;


    // Arithmetic functions
    Integer operator+(const Integer &b);
    Integer operator-(const Integer &b);

};

#endif
