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
#include <Rect.hpp>
#include "Utility.hpp"

namespace nitroCpp {
namespace unittest {

TEST(RectTest, ComputeIntersectionOk) {
  static constexpr int kSizeRect = 10;
  static constexpr int kInterectionArea = 1;
  static_assert(kSizeRect, "Dimension must to be positive");
  static_assert(kInterectionArea < kSizeRect, "Not feasible test");

  const Rect aRectA{0, 0, kSizeRect, kSizeRect};
  const Rect aRectB{kSizeRect - kInterectionArea,
                    kSizeRect - kInterectionArea,
                    kSizeRect,
                    kSizeRect};

  const Rect aIntersectionAB = Rect::computeIntersection(aRectA, aRectB);
  ASSERT_TRUE(Rect::isValid(aIntersectionAB));
  ASSERT_EQ(aIntersectionAB._x, kSizeRect - kInterectionArea);
  ASSERT_EQ(aIntersectionAB._y, kSizeRect - kInterectionArea);
  ASSERT_EQ(aIntersectionAB._w, kInterectionArea);
  ASSERT_EQ(aIntersectionAB._h, kInterectionArea);
}

TEST(RectTest, ComputeIntersectionVoid) {
  static constexpr int kSizeRect = 10;
  static_assert(kSizeRect, "Dimension must to be positive");

  const Rect aRectA{0, 0, kSizeRect, kSizeRect};
  const Rect aRectB{kSizeRect, kSizeRect, kSizeRect, kSizeRect};

  const Rect aIntersectionAB = Rect::computeIntersection(aRectA, aRectB);
  ASSERT_FALSE(Rect::isValid(aIntersectionAB));
}

TEST(RectTest, Commutativity) {
  static constexpr int kSizeRect = 10;
  static constexpr int kInterectionArea = 1;
  static_assert(kSizeRect, "Dimension must to be positive");
  static_assert(kInterectionArea < kSizeRect, "Not feasible test");

  const Rect aRectA{0, 0, kSizeRect, kSizeRect};
  const Rect aRectB{kSizeRect - kInterectionArea,
                    kSizeRect - kInterectionArea,
                    kSizeRect,
                    kSizeRect};

  const Rect aIntersectionAB = Rect::computeIntersection(aRectA, aRectB);
  const Rect aIntersectionBA = Rect::computeIntersection(aRectB, aRectA);

  ASSERT_TRUE(areSame(aIntersectionAB, aIntersectionAB));
}

}  // namespace unittest
}  // namespace nitroCpp
