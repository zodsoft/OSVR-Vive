/** @file
    @brief Header

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_ChaperoneData_h_GUID_983CDBF6_6DCF_44AC_E261_19EF8436EA23
#define INCLUDED_ChaperoneData_h_GUID_983CDBF6_6DCF_44AC_E261_19EF8436EA23

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <memory>
#include <string>
#include <cstdint>
#include <array>

namespace osvr {
namespace vive {
    /// Data on the known tracking universes, chaperone bounds, play spaces,
    /// etc. loaded from the chaperone_info file.
    class ChaperoneData {
      public:
        struct UniverseData {
            std::array<double, 3> translation;
            double yaw;
        };

        explicit ChaperoneData(std::string const &steamConfigDir);
        ~ChaperoneData();

        bool valid() const;
        explicit operator bool() const { return valid(); }

        /// Not all messages are fatal - so this can be true without valid being
        /// false.
        bool hasMessages() const { return !err_.empty(); }

        /// If the object isn't valid, or if we hit some snags that weren't
        /// fatal, you'll have a message or a few sitting in here.
        std::string const &getMessage() const { return err_; }

        /// Do we have data for this universe ID?
        /// Note that 0 is a dummy/always invalid universe.
        bool knowUniverseId(std::uint64_t universe) const;

        UniverseData getDataForUniverse(std::uint64_t universe) const;

        /// Get the number of known and handled universes;
        std::size_t getNumberOfKnownUniverses() const;

      private:
        void errorOut_(std::string const& message);
        void warn_(std::string const& message);
        struct Impl;
        std::unique_ptr<Impl> impl_;
        const std::string configDir_;
        std::string err_;
    };

} // namespace vive
} // namespace osvr

#endif // INCLUDED_ChaperoneData_h_GUID_983CDBF6_6DCF_44AC_E261_19EF8436EA23
