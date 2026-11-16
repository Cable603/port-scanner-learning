#pragma once

// Move-only owner for one POSIX socket descriptor. Lifetime and close behavior
// are implemented in socket_handle.cpp so OS calls stay out of this header.
namespace port_scanner {

class SocketHandle {
public:
    // Empty state owns no descriptor. A valid descriptor is adopted, not copied.
    SocketHandle() noexcept = default;
    explicit SocketHandle(int native_handle) noexcept
        : descriptor_(native_handle) {}

    // Destruction closes an owned descriptor; cleanup must never throw.
    ~SocketHandle();

    // A descriptor has exactly one owner, so copying is prohibited.
    SocketHandle(const SocketHandle&) = delete;
    SocketHandle& operator=(const SocketHandle&) = delete;

    // Moving transfers ownership and leaves the source empty.
    SocketHandle(SocketHandle&& other) noexcept;
    SocketHandle& operator=(SocketHandle&& other) noexcept;

    // These are intentionally tiny header definitions: they only inspect state.
    [[nodiscard]] bool valid() const noexcept {
        return descriptor_ >= 0;
    }

    // Borrowed descriptor for a system call; callers must not close it directly.
    [[nodiscard]] int native_handle() const noexcept {
        return descriptor_;
    }

    // Relinquish ownership without closing; the caller becomes responsible.
    [[nodiscard]] int release() noexcept;

    // Close the current descriptor, then adopt the supplied descriptor.
    // Passing -1 leaves this object empty. Implemented out of line for POSIX close.
    void reset(int replacement = -1) noexcept;

private:
    int descriptor_{-1};
};

} // namespace port_scanner