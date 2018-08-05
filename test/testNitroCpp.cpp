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
#include <NitroCpp.hpp>
#include <string>

namespace nitroCpp {
namespace unittest {

class NitroCppTest : public NitroCpp {
 public:
  using NitroCpp::parseCommandLine;
  using NitroCpp::parseJsonFromBuffer;
  using NitroCpp::readFile;
  using NitroCpp::validateJsonDocument;
};

TEST(NitroCppTest, ParseCommandLineNoInput) {
  static constexpr int kArgC = 1;
  static constexpr const char* kArgV[] = {"TheProgramm"};

  NitroCppTest::CommandLineOptions aOutputOptions;
  ASSERT_FALSE(NitroCppTest::parseCommandLine(kArgC, kArgV, &aOutputOptions));
}

TEST(NitroCppTest, ParseCommandOk) {
  static constexpr int kArgC = 2;
  static constexpr const char* kFileName = "FileName.json";
  static constexpr const char* kArgV[] = {"TheProgramm", kFileName};

  NitroCppTest::CommandLineOptions aOutputOptions;
  ASSERT_TRUE(NitroCppTest::parseCommandLine(kArgC, kArgV, &aOutputOptions));
  ASSERT_STREQ(aOutputOptions._inputFilename.c_str(), kFileName);
}

TEST(NitroCppTest, ReadFileFailure) {
  static const std::string kFileName = "???ThisFileDoesNotExist???";

  ASSERT_THROW(NitroCppTest::readFile(kFileName), std::runtime_error);
}

TEST(NitroCppTest, ParseAndValidateJsonOk) {
  static constexpr const char* kValidJson =
      R"%%%(
{
  "rects" : [
    {"x" : 100, "y" : 100, "w" : 250, "h" : 80},
    {"x" : 120, "y" : 200, "w" : 250, "h" : 150},
    {"x" : 140, "y" : 160, "w" : 250, "h" : 100},
    {"x" : 160, "y" : 140, "w" : 350, "h" : 190}
  ]
}
)%%%";

  const auto aJsonDocument = NitroCppTest::parseJsonFromBuffer(kValidJson);
  ASSERT_FALSE(aJsonDocument.IsNull());
  ASSERT_TRUE(NitroCppTest::validateJsonDocument(aJsonDocument));
}

TEST(NitroCppTest, ParseJsonNotValid) {
  static constexpr const char* kNotValidJson =
      R"%%%(
{
  ThisIsNotValidJson
}
)%%%";

  const auto aJsonDocument = NitroCppTest::parseJsonFromBuffer(kNotValidJson);
  ASSERT_TRUE(aJsonDocument.IsNull());
}

TEST(NitroCppTest, ParseJsonFromBufferEmpty) {
  static constexpr const char* kEmptyJson = "";

  const auto aJsonDocument = NitroCppTest::parseJsonFromBuffer(kEmptyJson);
  ASSERT_TRUE(aJsonDocument.IsNull());
}

TEST(NitroCppTest, InputMissingInformation) {
  static constexpr const char* kValidJsonMissingInfo =
      R"%%%(
{
  "problem" : "is valid but does not contain rects"
}
)%%%";

  const auto aJsonDocument = NitroCppTest::parseJsonFromBuffer(kValidJsonMissingInfo);
  ASSERT_FALSE(aJsonDocument.IsNull());
  ASSERT_FALSE(NitroCppTest::validateJsonDocument(aJsonDocument));
}

}  // namespace unittest
}  // namespace nitroCpp
