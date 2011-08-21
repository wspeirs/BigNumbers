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

int main()
{
    Integer a(1);
    Integer b(2);
    Integer c(3);

    c = a + b;
    c = a + 2;

    c = a - b;
    c = a - 2;

    return 0;
}
