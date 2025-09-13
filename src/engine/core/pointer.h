#pragma once

#include <functional>
#include <map>
#include <memory>
#include <unordered_map>

/*
Borrowed some templates utilities since I thought this looked nice:
https://github.com/Jernesstar/VolcanicEngine/blob/979bc23cd4a61a4c5ab553b62d6869adf23e0cb6/VolcaniCore/src/VolcaniCore/Core/Defines.h#L39
*/

template <typename T>
using Ptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Ptr<T> CreatePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename TKey, typename TValue>
using Map = std::unordered_map<TKey, TValue>;

template <typename TKey, typename TValue>
using OMap = std::map<TKey, TValue>;

template <typename TValue1, typename TValue2>
using Pair = std::pair<TValue1, TValue2>;

template <typename TReturn, typename... Args>
using Func = std::function<TReturn(Args...)>;