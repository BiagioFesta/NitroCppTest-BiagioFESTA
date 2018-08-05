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
#ifndef NITRO_CPP__SOLVER__HPP
#define NITRO_CPP__SOLVER__HPP
#include <vector>
#include "Rect.hpp"

namespace nitroCpp {

/*! \brief This class is the solver of the problem.
 *  \see solveProblem
 *  \author Biagio Festa
 */
class Solver {
 public:
  struct Intersection {
    std::vector<int> _indicesRects;  // The indices (0-based) of rect involved
    Rect _data;                      // The result of the intersection

    //! \brief Default Constructor
    Intersection(std::vector<int> iIndicesRects, Rect iData);
  };

  using VectIntersection = std::vector<Intersection>;
  using VectRect = std::vector<Rect>;

  /*! \brief It solves the problem of the test.
   *  It compute all possible intersections among two or more rectangles in
   *  input.
   *  \param [in]  iRect            The input rectangles.
   *  \param [out] oIntersections   All possible intersections.
   *  \note Complexity:
   *       Time: O(2^N)         Space: O(2^N)
   *  \throw In case the input size is too big.
   */
  void solveProblem(const VectRect& iRects,
                    VectIntersection* oIntersections) const;
};

}  // namespace nitroCpp

#endif  // NITRO_CPP__SOLVER__HPP
