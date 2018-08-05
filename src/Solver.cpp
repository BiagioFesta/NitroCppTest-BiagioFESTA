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
#include "Solver.hpp"
#include <cassert>
#include <queue>
#include <stdexcept>
#include <utility>

namespace nitroCpp {

Solver::Intersection::Intersection(std::vector<int> iIndicesRects, Rect iData)
    : _indicesRects(std::move(iIndicesRects)), _data(std::move(iData)) {}

void Solver::solveProblem(const VectRect& iRects,
                          VectIntersection* oIntersections) const {
  /* Dislaimer: I am going to insert more details in comments because that's an
   * execise for evaluation purpose.
   * For production code it should be better to minimize the verbosity of
   * comments to increase readability.
   */
  using OpenList = std::queue<Intersection>;  // For Breadth-first search
  static constexpr int kWarningInputSize = sizeof(std::size_t) * 8;

  const int kSize = iRects.size();
  const int kSizeMinusOne = kSize - 1;

  oIntersections->clear();
  if (kSize < 0 || kSize >= kWarningInputSize) {
    /* The worst case of the problem happens when ALL input rectangles have all
     * intersections. (E.g. rectangles inside rectangles).
     * In that case the time and space complexity belongs to:
     *     Time: O(2^N)     Space: O(2^N)
     *        where N is the size of input (kSize in the code)
     * In case N >= 64, then the number of states in the worst case is:
     *             2 ^ 64
     * From a memory point of view, that's will saturate the RAM of a desktop
     * computer.
     */
    throw std::runtime_error("Warning! The input size can be too high!");
  }

  /* My solution explores the sub-problem with backtracking algorithm.
   * The implementation is made by means of a Breadth-first search.
   * Important consideration!
   * A DepthFirst Search may be more efficient in term of space complexity,
   * however I've decided to keep a Queue Data structure (instead of a Stack)
   * because the order of the solution is preserved (in accordance with the
   * text-specifications).
   */
  OpenList aOpenList;

  /* Time: O(N^2)
   * Initialize the OpenList structure with all trivial cases.
   */
  for (int i = 0; i < kSizeMinusOne; ++i) {
    for (int j = i + 1; j < kSize; ++j) {
      auto aIntersectionData = Rect::computeIntersection(iRects[i], iRects[j]);
      if (Rect::isValid(aIntersectionData)) {
        aOpenList.emplace(std::vector<int>{i, j}, std::move(aIntersectionData));
      }
    }
  }

  /* That's the core of the algorithm and of the BFS.
   * It computes the solutions of the input problem.
   * However, this algorithm is clever! During the exploration of the
   * state-space, it will completely prune a sub-tree in case it discovers
   * future intersections will be empty. The technic is the base of Branch and
   * Bound algorithms. That possible because the empty set is the null element
   * of intersection operation in the set theory.
   */
  while (!aOpenList.empty()) {
    auto aCurrentNode = std::move(aOpenList.front());
    aOpenList.pop();

    assert(!aCurrentNode._indicesRects.empty());
    const int aLastIndex = aCurrentNode._indicesRects.back();

    for (int i = aLastIndex + 1; i < kSize; ++i) {
      auto aIntersectionData =
          Rect::computeIntersection(aCurrentNode._data, iRects[i]);

      // This check avoid useless exploration, prune of the tree.
      if (Rect::isValid(aIntersectionData)) {
        std::vector<int> aNewState{aCurrentNode._indicesRects};
        aNewState.push_back(i);
        aOpenList.emplace(std::move(aNewState), std::move(aIntersectionData));
      }
    }

    oIntersections->push_back(std::move(aCurrentNode));
  }
}

}  // namespace nitroCpp
