#include <iostream>
#include "MusicLibrary.h" // Your code is in here!

int main() {
    // 1. Create your music library
    MusicLibrary myLibrary;

    // 2. Add songs (your addSong function)
    myLibrary.addSong(Song("Yesterday", "The Beatles"));
    myLibrary.addSong(Song("Bohemian Rhapsody", "Queen"));
    myLibrary.addSong(Song("Stairway to Heaven", "Led Zeppelin"));
    myLibrary.addSong(Song("Africa", "Toto"));

    // 3. Display all songs (proves your BST is sorting them)
    // Output should be alphabetical:
    // Africa
    // Bohemian Rhapsody
    // Stairway to Heaven
    // Yesterday
    myLibrary.displayAllSongs();

    // 4. Search for a song that exists
    myLibrary.searchByTitle("Bohemian Rhapsody");

    // 5. Search for a song that does NOT exist
    myLibrary.searchByTitle("Wonderwall");

    return 0;
}