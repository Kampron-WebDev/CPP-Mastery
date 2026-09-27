#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Song {
    std::string title;
    explicit Song(std::string t) : title{std::move(t)} {}
    ~Song() { std::cout << "Song " << title << " freed\n"; }
};

class Playlist {
public:
    explicit Playlist(std::string name) : name{std::move(name)} {}
    void add(std::shared_ptr<Song> song) { songs.push_back(std::move(song)); }
    void print() const
    {
        std::cout << name << ": ";
        for (const auto& s : songs) std::cout << s->title << ' ';
        std::cout << '\n';
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Song>> songs;
};

int main()
{
    Playlist favourites{"Favourites"};
    {
        auto a = std::make_shared<Song>("A");
        auto b = std::make_shared<Song>("B");
        auto c = std::make_shared<Song>("C");
        {
            Playlist party{"Party"};
            party.add(a);
            party.add(c);
            favourites.add(a);
            favourites.add(b);
            party.print();
            favourites.print();
            std::cout << "counts: A=" << a.use_count() << " B=" << b.use_count() << " C=" << c.use_count() << '\n';
        }   // Party destroyed: its shared_ptrs let go
        std::cout << "after Party: A=" << a.use_count() << " C=" << c.use_count() << '\n';
        std::cout << "leaving block (local a, b, c released)\n";
    }   // C is freed here (nobody else holds it). A and B live on in Favourites.
    std::cout << "end of main\n";
}   // Favourites destroyed: A and B freed
