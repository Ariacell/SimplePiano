#include <fmt/core.h>

#include <glm/glm.hpp>

template <>
struct fmt::formatter<glm::vec2> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const glm::vec2& v, fmt::format_context& ctx) const {
        return fmt::format_to(ctx.out(), "vec2({}, {})", v.x, v.y);
    }
};

template <>
struct fmt::formatter<glm::vec3> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const glm::vec3& v, fmt::format_context& ctx) const {
        return fmt::format_to(ctx.out(), "vec3({}, {}, {})", v.x, v.y, v.z);
    }
};

template <>
struct fmt::formatter<glm::vec4> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const glm::vec4& v, fmt::format_context& ctx) const {
        return fmt::format_to(ctx.out(), "vec4({}, {}, {}, {})", v.x, v.y, v.z,
                              v.w);
    }
};
