#include <string_view>
#include <string>
#include <cstddef>
#include <utility>
#include <functional>
#include <unordered_map>
#include <memory>

struct StringHash
{
    using is_transparent = void;

    [[nodiscard]] auto operator()(const char* text) const -> std::size_t { return std::hash<std::string_view>{}(text); }
    [[nodiscard]] auto operator()(std::string_view text) const -> std::size_t { return std::hash<std::string_view>{}(text); }
    [[nodiscard]] auto operator()(const std::string& text) const -> std::size_t { return std::hash<std::string>{}(text); }
};

// Use std::hash by default.
template<typename T> struct Hash : std::hash<T> {};

// String specialization to enable transparent lookup in unordered containers.
template<> struct Hash<std::string> : StringHash {};

template<typename Key, typename T, typename Hasher = Hash<Key>, typename KeyEqual = std::equal_to<>, typename Allocator = std::allocator<std::pair<const Key, T>>>
using UnorderedMap = std::unordered_map<Key, T, Hasher, KeyEqual, Allocator>;