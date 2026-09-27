// ⭐⭐ Exercise 02: LoggingDecorator
// interface DataStore { virtual std::string get(const std::string& key) = 0;
//                       virtual void put(const std::string& key, const std::string& value) = 0; }
// 1. MemoryStore: a std::map-based implementation.
// 2. LoggingStore: a DECORATOR. It implements DataStore, WRAPS another DataStore&, logs each call,
//    then forwards to the wrapped store.
// 3. CachingStore: another decorator that counts how many get() calls reached the wrapped store
//    (cache values it has already fetched).
// 4. Stack them: CachingStore -> LoggingStore -> MemoryStore, and show which calls reach the bottom.
#include <iostream>
#include <map>
#include <string>

int main()
{
    // TODO
}
