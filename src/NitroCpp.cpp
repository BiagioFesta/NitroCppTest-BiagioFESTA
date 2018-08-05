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
#include "NitroCpp.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Rect.hpp"

namespace {

constexpr const char* kRectsFieldStr = "rects";
constexpr const char* kXFieldStr = "x";
constexpr const char* kYFieldStr = "y";
constexpr const char* kWFieldStr = "w";
constexpr const char* kHFieldStr = "h";

void printRectData(const nitroCpp::Rect& iRect, std::ostream* oStream) {
  *oStream << '(' << iRect._x << ',' << iRect._y << "), w=" << iRect._w
           << ", h=" << iRect._h << '.';
}

void printInputRects(const nitroCpp::NitroCpp::VectRect& iInputVectors,
                     std::ostream* oStream) {
  const int kSize = iInputVectors.size();

  *oStream << "Input:\n";
  for (int i = 0; i < kSize; ++i) {
    *oStream << "      " << i + 1 << ": Rectangle at ";
    ::printRectData(iInputVectors[i], oStream);
    *oStream << '\n';
  }
  *oStream << '\n';
}

void printOutputIntersections(
    const nitroCpp::NitroCpp::VectInterection& iOuputIntersections,
    std::ostream* oStream) {
  *oStream << "Intersections\n";
  for (const auto& aIntersection : iOuputIntersections) {
    *oStream << "      Between rectangle ";

    const int kSize = aIntersection._indicesRects.size();
    for (int i = 0; i < kSize; ++i) {
      if (i != 0) {
        *oStream << (i == kSize - 1 ? " and " : ", ");
      }
      *oStream << aIntersection._indicesRects[i] + 1;
    }
    *oStream << " at ";
    ::printRectData(aIntersection._data, oStream);
    *oStream << '\n';
  }
}

}  // namespace

namespace nitroCpp {

int NitroCpp::run(int argc, const char* const argv[]) noexcept {
  try {
    CommandLineOptions aCommandLineOptions;
    if (parseCommandLine(argc, argv, &aCommandLineOptions) == false) {
      std::cerr << "Usage\n"
                << "  " << argv[0] << " FILENAME\n";
      return -1;
    }

    const auto aFileContent = readFile(aCommandLineOptions._inputFilename);
    const auto aJsonDocument = parseJsonFromBuffer(aFileContent.c_str());
    const auto aRects = parseRectsFromDocument(aJsonDocument);
    ::printInputRects(aRects, &std::cout);

    Solver::VectIntersection aIntersections;

    Solver aSolver;
    aSolver.solveProblem(aRects, &aIntersections);
    ::printOutputIntersections(aIntersections, &std::cout);
  } catch (const std::exception& aError) {
    std::cerr << aError.what() << '\n';
    return -1;
  }
  return 0;
}

bool NitroCpp::parseCommandLine(int argc,
                                const char* const argv[],
                                CommandLineOptions* oCommandLineOptions) {
  if (argc < 2) return false;

  oCommandLineOptions->_inputFilename = argv[1];
  return true;
}

std::string NitroCpp::readFile(const std::string& iFilename) {
  std::ifstream aInputFile;
  aInputFile.open(iFilename);

  if (aInputFile.fail()) {
    throw std::runtime_error("Cannot open the input file");
  }

  std::string aFileContent;

  // Reserve memory at once, avoid successive reallocation
  aInputFile.seekg(0, std::ios::end);
  aFileContent.reserve(aInputFile.tellg());
  aInputFile.seekg(0, std::ios::beg);

  aFileContent.assign(std::istreambuf_iterator<char>(aInputFile),
                      std::istreambuf_iterator<char>());

  return aFileContent;
}

NitroCpp::JsonDocument NitroCpp::parseJsonFromBuffer(const char* iBuffer) {
  JsonDocument aJsonDocument;
  aJsonDocument.Parse(iBuffer);
  return aJsonDocument;
}

bool NitroCpp::validateJsonDocument(const JsonDocument& iJsonDocument) {
  if (iJsonDocument.IsNull() || !iJsonDocument.HasMember(kRectsFieldStr)) {
    return false;
  }

  const auto& aRects = iJsonDocument[kRectsFieldStr];
  if (!aRects.IsArray()) {
    return false;
  }

  return std::all_of(aRects.Begin(), aRects.End(), [](const auto& iRect) {
    return iRect.IsObject() && iRect.HasMember(kXFieldStr) &&
           iRect.HasMember(kYFieldStr) && iRect.HasMember(kWFieldStr) &&
           iRect.HasMember(kHFieldStr);
  });
}

NitroCpp::VectRect NitroCpp::parseRectsFromDocument(
    const JsonDocument& iJsonDocument) {
  const auto& aRects = iJsonDocument[kRectsFieldStr];

  VectRect aVectRect;

  // TODO(biagio): this transform all rect input (not 10 max).
  // The specifications say "may", I would like to try to process all
  std::transform(aRects.Begin(),
                 aRects.End(),
                 std::back_inserter(aVectRect),
                 [](const auto& iJsonRect) {
                   using nitroCpp::Rect;

                   return Rect(iJsonRect[kXFieldStr].GetInt(),
                               iJsonRect[kYFieldStr].GetInt(),
                               iJsonRect[kWFieldStr].GetInt(),
                               iJsonRect[kHFieldStr].GetInt());
                 });
  return aVectRect;
}

}  // namespace nitroCpp
