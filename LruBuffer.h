#pragma once
#include <unordered_map>
#include <set>
#include <utility>
#include <stdexcept>

template<typename K, typename V>
class LruBuffer {
private:
    size_t maxSize = 1;
    size_t Tm = 0;
    std::unordered_map<K, V> Data;
    std::unordered_map<K, size_t> LastUse;
    std::set<std::pair<size_t, K>> Queue;

public:
    LruBuffer() = delete;
    explicit LruBuffer(size_t max_size) : maxSize(max_size) {
        if(max_size == 0) {
            throw std::runtime_error("must be positive");
        }
    }

    void erase(const K& key) {
        if (!Data.count(key)) {
            throw std::runtime_error("fail erase");
        }
        Queue.erase({LastUse[key], key});
        LastUse.erase(key);
        Data.erase(key);
    }

    void set(auto&& key, auto&& val) {
        if (Data.count(key)) {
            erase(key);
        }
        if (Data.size() == maxSize) {
            auto [_, kk] = *Queue.begin();
            erase(kk);
        }
        Data[key] = std::forward<V>(val);
        LastUse[key] = Tm++;
        Queue.emplace({LastUse[key],  std::forward<K>(key)}); //в с++ 17 порядок вычисления слева на право
    }

    V get(auto&& key) {
        if (!Data.count(key)) {
            throw std::runtime_error("bad key");
        }

        Queue.erase({LastUse[key], key});
        LastUse[key] = Tm++;
        auto& value = Data[key]; 
        Queue.emplace({LastUse[key], std::forward<K>(key)});

        return value;
    }

    bool check(const K& key) {
        return Data.count(key);
    }
};
