#pragma once

// A small expected-value-style type used by operations that can either return
// data or a structured Error. Template definitions live here because callers
// instantiate Result<T> in multiple translation units.
#include "port_scanner/error.hpp"

#include <utility>
#include <variant>

namespace port_scanner {

// Holds either a successful value of T or an Error. Callers should check
// has_value() before requesting value() or error(); the wrong accessor follows
// std::variant behavior and throws std::bad_variant_access.
template <typename T>
class Result {
public:
    // Construct a successful result by moving the provided value into storage.
    [[nodiscard]] static Result success(T value) {
        return Result(std::move(value));
    }

    // Construct a failed result with a descriptive, categorized error.
    [[nodiscard]] static Result failure(Error error) {
        return Result(std::move(error));
    }

    // True when this result contains T. This inspection has no side effects.
    [[nodiscard]] bool has_value() const noexcept {
        return std::holds_alternative<T>(data_);
    }

    // Convenient explicit condition for branching on success.
    [[nodiscard]] explicit operator bool() const noexcept {
        return has_value();
    }

    // Access a successful value while preserving the caller's value category.
    // Precondition: has_value() is true.
    [[nodiscard]] T& value() & {
        return std::get<T>(data_);
    }

    [[nodiscard]] const T& value() const& {
        return std::get<T>(data_);
    }

    [[nodiscard]] T&& value() && {
        return std::get<T>(std::move(data_));
    }

    // Access the stored failure description.
    // Precondition: has_value() is false.
    [[nodiscard]] Error& error() & {
        return std::get<Error>(data_);
    }

    [[nodiscard]] const Error& error() const& {
        return std::get<Error>(data_);
    }

private:
    // Private constructors require callers to say success or failure explicitly.
    explicit Result(T value) : data_(std::move(value)) {}
    explicit Result(Error error) : data_(std::move(error)) {}

    std::variant<T, Error> data_;
};

// Void specialization represents successful completion without a value.
template <>
class Result<void> {
public:
    [[nodiscard]] static Result success() {
        return Result(std::monostate{});
    }

    [[nodiscard]] static Result failure(Error error) {
        return Result(std::move(error));
    }

    [[nodiscard]] bool has_value() const noexcept {
        return std::holds_alternative<std::monostate>(data_);
    }

    [[nodiscard]] explicit operator bool() const noexcept {
        return has_value();
    }

    // Precondition: has_value() is false.
    [[nodiscard]] Error& error() & {
        return std::get<Error>(data_);
    }

    [[nodiscard]] const Error& error() const& {
        return std::get<Error>(data_);
    }

private:
    explicit Result(std::monostate success) : data_(success) {}
    explicit Result(Error error) : data_(std::move(error)) {}

    std::variant<std::monostate, Error> data_;
};

} // namespace port_scanner