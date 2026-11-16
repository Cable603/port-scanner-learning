#pragma once

// Bounded, thread-safe queue ADT for scan jobs. Synchronization and blocking
// behavior are implemented in work_queue.cpp rather than exposed as inline code.
#include "port_scanner/resolver.hpp"
#include "port_scanner/types.hpp"

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <optional>
#include <queue>

namespace port_scanner {

struct ScanJob {
    ResolvedEndpoint endpoint;
    Port port{};
};

// Multiple producers and workers may use this queue concurrently. push waits
// for capacity or closure; pop waits for work or closure. After close(), queued
// jobs may still be drained, then pop returns no value. Capacity must be > 0.
class WorkQueue {
public:
    explicit WorkQueue(std::size_t capacity);

    WorkQueue(const WorkQueue&) = delete;
    WorkQueue& operator=(const WorkQueue&) = delete;

    // Returns false only when the queue is closed before this job is accepted.
    [[nodiscard]] bool push(ScanJob job);

    // Waits for a job. Returns empty only after closure and all jobs are drained.
    [[nodiscard]] std::optional<ScanJob> pop();

    // Stop accepting new jobs and wake blocked producers and consumers.
    void close();

    // Snapshot of queued jobs, not including work already held by a worker.
    [[nodiscard]] std::size_t size() const;

private:
    const std::size_t capacity_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::queue<ScanJob> jobs_;
    bool closed_{false};
};

} // namespace port_scanner