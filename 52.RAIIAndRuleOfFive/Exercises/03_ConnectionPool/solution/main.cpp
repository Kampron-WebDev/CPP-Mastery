#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

class Pool;

class Lease {
public:
    Lease(Pool* pool, int id) : pool{pool}, connectionId{id} {}
    ~Lease();
    Lease(const Lease&) = delete;
    Lease& operator=(const Lease&) = delete;
    Lease(Lease&& o) noexcept : pool{std::exchange(o.pool, nullptr)}, connectionId{o.connectionId} {}
    Lease& operator=(Lease&& o) noexcept;
    int id() const { return connectionId; }

private:
    Pool* pool;   // nullptr = moved-from: owns nothing
    int connectionId;
};

class Pool {
public:
    explicit Pool(int size)
    {
        for (int i = size; i >= 1; --i) freeIds.push_back(i);
    }
    Lease acquire()
    {
        if (freeIds.empty()) throw std::runtime_error{"no free connections"};
        const int id = freeIds.back();
        freeIds.pop_back();
        std::cout << "  acquired #" << id << '\n';
        return Lease{this, id};
    }
    int available() const { return static_cast<int>(freeIds.size()); }

private:
    friend class Lease;
    void giveBack(int id)
    {
        freeIds.push_back(id);
        std::cout << "  returned #" << id << '\n';
    }
    std::vector<int> freeIds;
};

Lease::~Lease()
{
    if (pool) pool->giveBack(connectionId);
}

Lease& Lease::operator=(Lease&& o) noexcept
{
    if (this != &o) {
        if (pool) pool->giveBack(connectionId);   // release what we held
        pool = std::exchange(o.pool, nullptr);
        connectionId = o.connectionId;
    }
    return *this;
}

void runQuery(Lease lease) { std::cout << "  query on connection #" << lease.id() << '\n'; }   // returned at the end

int main()
{
    Pool pool{3};
    Lease a = pool.acquire();
    {
        Lease b = pool.acquire();
        std::cout << "available: " << pool.available() << '\n';   // 1
    }
    std::cout << "after block: " << pool.available() << '\n';     // 2

    runQuery(std::move(a));
    std::cout << "after runQuery: " << pool.available() << '\n';  // 3

    try {
        std::vector<Lease> many;
        for (int i = 0; i < 4; ++i) many.push_back(pool.acquire());
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << '\n';
    }
    std::cout << "after exception: " << pool.available() << '\n';  // 3: nothing leaked
}
