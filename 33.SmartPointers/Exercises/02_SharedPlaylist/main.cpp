// ⭐⭐ Exercise 02: SharedPlaylist
// One Song object can be in several playlists at once, so ownership is SHARED.
//   struct Song { std::string title; ~Song() prints "Song <title> freed" };
//   class Playlist { std::string name; std::vector<std::shared_ptr<Song>> songs; add(), print() }
// 1. Create 3 songs with make_shared. Add song A to two playlists.
// 2. Print use_count() of each song.
// 3. Destroy one playlist (put it in a block). Print use_count again.
// 4. Show exactly WHEN each song is freed.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    // TODO
}
