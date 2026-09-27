#include <iostream>
#include <map>
#include <string>

class DataStore {
public:
    virtual ~DataStore() = default;
    virtual std::string get(const std::string& key) = 0;
    virtual void put(const std::string& key, const std::string& value) = 0;
};

class MemoryStore : public DataStore {
public:
    std::string get(const std::string& key) override
    {
        const auto it = data.find(key);
        return it == data.end() ? "" : it->second;
    }
    void put(const std::string& key, const std::string& value) override { data[key] = value; }
private:
    std::map<std::string, std::string> data;
};

// Decorator: same interface, wraps another store, adds behaviour, forwards the call.
class LoggingStore : public DataStore {
public:
    explicit LoggingStore(DataStore& inner) : inner{inner} {}
    std::string get(const std::string& key) override
    {
        std::cout << "  [log] get(" << key << ")\n";
        return inner.get(key);
    }
    void put(const std::string& key, const std::string& value) override
    {
        std::cout << "  [log] put(" << key << ", " << value << ")\n";
        inner.put(key, value);
    }
private:
    DataStore& inner;
};

class CachingStore : public DataStore {
public:
    explicit CachingStore(DataStore& inner) : inner{inner} {}
    std::string get(const std::string& key) override
    {
        if (const auto it = cache.find(key); it != cache.end()) return it->second;   // served from cache
        return cache[key] = inner.get(key);
    }
    void put(const std::string& key, const std::string& value) override
    {
        cache[key] = value;   // write-through: keep cache and store consistent
        inner.put(key, value);
    }
private:
    DataStore& inner;
    std::map<std::string, std::string> cache;
};

int main()
{
    MemoryStore memory;
    LoggingStore logged{memory};
    CachingStore store{logged};   // CachingStore -> LoggingStore -> MemoryStore

    store.put("name", "Ama");
    // Call get() BEFORE printing, so the [log] lines don't land in the middle of our output.
    std::cout << "1st get(city):\n";
    const auto first = store.get("city");     // reaches the bottom: logged
    std::cout << "  -> '" << first << "'\n2nd get(city):\n";
    const auto second = store.get("city");    // served from the cache: no log line
    std::cout << "  -> '" << second << "' (cached)\nget(name):\n";
    const auto name = store.get("name");      // cached by put(): no log line
    std::cout << "  -> '" << name << "' (cached by put)\n";
}
