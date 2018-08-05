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
#include <gtest/gtest.h>
#include <Solver.hpp>
#include "Utility.hpp"

namespace nitroCpp {
namespace unittest {

TEST(SolverTest, solveProblemOneInput) {
  const Solver::VectRect aInput = {{0, 0, 1, 1}};

  Solver::VectIntersection aOutput;
  Solver().solveProblem(aInput, &aOutput);

  ASSERT_TRUE(aOutput.empty());
}

TEST(SolverTest, solveProblemTwoInputs) {
  const Solver::VectRect kIntersectRect = {{0, 0, 10, 10}, {5, 5, 10, 10}};
  const Solver::VectRect kNoIntersectRect = {{0, 0, 5, 5}, {5, 5, 10, 10}};

  Solver::VectIntersection aOutput;
  Solver().solveProblem(kIntersectRect, &aOutput);
  ASSERT_EQ(aOutput.size(), 1);

  ASSERT_TRUE(
      areSame(aOutput[0]._data,
              Rect::computeIntersection(kIntersectRect[0], kIntersectRect[1])));

  Solver().solveProblem(kNoIntersectRect, &aOutput);
  ASSERT_EQ(aOutput.size(), 0);
}

TEST(SolverTest, solveProblemNested) {
  static constexpr int kNestedLevels = 10;
  static constexpr int kExpectedNumIntersections =
      (1 << kNestedLevels) - (kNestedLevels + 1);

  Solver::VectRect aNestedRects;
  for (int i = 0; i < kNestedLevels; ++i) {
    const int kDim = kNestedLevels - i;
    aNestedRects.emplace_back(i, i, kDim, kDim);
  }

  Solver::VectIntersection aOutput;
  Solver().solveProblem(aNestedRects, &aOutput);
  ASSERT_EQ(aOutput.size(), kExpectedNumIntersections);
}

}  // namespace unittest
}  // namespace nitroCpp
