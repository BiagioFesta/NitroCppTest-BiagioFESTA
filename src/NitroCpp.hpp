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
#ifndef NITRO_CPP__NITRO_CPP__HPP
#define NITRO_CPP__NITRO_CPP__HPP
#include <rapidjson/document.h>
#include <ostream>
#include <string>
#include "Solver.hpp"

namespace nitroCpp {

/*! \brief Entry Point of the application.
 *  This class represent the high level logic of the application.
 *  \author Biagio Festa
 */
class NitroCpp {
 public:
  using JsonDocument = rapidjson::Document;
  using VectRect = Solver::VectRect;
  using VectInterection = Solver::VectIntersection;

  struct CommandLineOptions {
    std::string _inputFilename;
  };

  /*! \brief Launch the application. It's the entry point.
   *  \param [in] argc    The size of array of argv.
   *  \param [in] argv    The command line tokens.
   *  \return 0 if the application ends with success, -1 otherwise.
   */
  int run(int argc, const char* const argv[]) noexcept;

 protected:
  //! \brief Parses the command line.
  static bool parseCommandLine(int argc,
                               const char* const argv[],
                               CommandLineOptions* oCommandLineOptions);

  //! \brief Reads the a file from the filesystem.
  static std::string readFile(const std::string& iFilename);

  /*! \brief Parse a Json content.
   *  \return a JsonDocument.
   *  In case of error the JsonDocument IsNull() == true.
   */
  static JsonDocument parseJsonFromBuffer(const char* iBuffer);

  /*! \brief It validate the content of the JsonDocument.
   *  In particual, it will ensure that the content of the json contains all
   * information needed for the problem.
   */
  static bool validateJsonDocument(const JsonDocument& iJsonDocument);

  /* \brief It will create the data-objects starting from the input json.
   * \note Preeconditions: The jsonDocument must be valid.
   * \see validateJsonDocument
   */
  static VectRect parseRectsFromDocument(const JsonDocument& iJsonDocument);
};

}  // namespace nitroCpp

#endif  // NITRO_CPP__NITRO_CPP__HPP
