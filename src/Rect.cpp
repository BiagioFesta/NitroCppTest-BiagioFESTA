/*
  Copyright (C) 2018  Biagio Festa
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Rect.hpp"
#include <algorithm>

namespace nitroCpp {

Rect::Rect(const int x, const int y, const int w, const int h)
    : _x(x), _y(y), _w(w), _h(h) {}

Rect Rect::computeIntersection(const Rect& iRectA,
                               const Rect& iRectB) noexcept {
  Rect aIntersection;
  aIntersection._x = std::max(iRectA._x, iRectB._x);
  aIntersection._y = std::max(iRectA._y, iRectB._y);
  aIntersection._w =
      std::min(iRectA._x + iRectA._w, iRectB._x + iRectB._w) - aIntersection._x;
  aIntersection._h =
      std::min(iRectA._y + iRectA._h, iRectB._y + iRectB._h) - aIntersection._y;
  return aIntersection;
}

bool Rect::isValid(const Rect& iRect) noexcept {
  return iRect._w > 0 && iRect._h > 0;
}

}  // namespace nitroCpp
