#pragma once

// Abstract data type for collected probe outcomes. Callers use these operations
// rather than depending on the collection representation.
#include "port_scanner/types.hpp"

#include <cstddef>
#include <vector>

namespace port_scanner {

class ScanResults {
public:
    // Append one completed attempt. Ownership of the value moves into the ADT.
    void add(ProbeResult result);

    // Number of stored attempts; valid for the lifetime of this collection.
    [[nodiscard]] std::size_t size() const noexcept;

    // Whether any probe outcomes have been stored.
    [[nodiscard]] bool empty() const noexcept;

    // Read one result by stable insertion index. Throws std::out_of_range when
    // index is not less than size(); this does not expose or mutate storage.
    [[nodiscard]] const ProbeResult& at(std::size_t index) const;

    // Count connected outcomes for a summary. The implementation is a traversal.
    [[nodiscard]] std::size_t open_count() const noexcept;

private:
    // Vector is the initial representation because scans are bounded and reports
    // traverse results in order. It remains private so the ADT can evolve.
    std::vector<ProbeResult> results_;
};

} // namespace port_scanner