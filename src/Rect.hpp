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
#ifndef NITRO_CPP__RECT__HPP
#define NITRO_CPP__RECT__HPP

namespace nitroCpp {

/*! \brief Simple POD which represent an rectangle in the specified space.
 *  \author Biagio Festa
 */
struct Rect {
  int _x;
  int _y;
  int _w;
  int _h;

  //! \brief Default constructor
  Rect() = default;

  //! \brief Construct all internal data.
  Rect(const int x, const int y, const int w, const int h);

  /*! \brief It computes the intersection of two rectangles.
   *  \note In case the two inputs do not intersect, the output will be a not
   *  valid rect.
   *  \see isValid
   */
  static Rect computeIntersection(const Rect& iRectA,
                                  const Rect& iRectB) noexcept;

  /*! \brief Check is a rectangle is well-defined.
   *  I.e., the dimensions must be positive.
   */
  static bool isValid(const Rect& iRect) noexcept;
};

}  // namespace nitroCpp

#endif  // NITRO_CPP__RECT__HPP
