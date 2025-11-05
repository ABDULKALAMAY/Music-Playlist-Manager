#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
// We MUST include your MusicLibrary.h to get the definition of the 'Song' struct
#include "MusicLibrary.h" 

// --- Step 1: Define the Node for the Playlist ---
// This is a DOUBLY linked list node
struct PlaylistNode {
    Song song;           // The song data
    PlaylistNode* next;  // Pointer to the next song
    PlaylistNode* prev;  // Pointer to the previous song

    // Constructor to easily create a new node
    PlaylistNode(Song s) : song(s), next(nullptr), prev(nullptr) {}
};

// --- Step 2: Define the Playlist class ---
class Playlist {
private:
    PlaylistNode* head;         // Points to the "first" song in the playlist
    PlaylistNode* currentSong;  // Points to the song currently playing

public:
    // Constructor
    Playlist() : head(nullptr), currentSong(nullptr) {}

    // --- Member 1's Core Functions ---

    // Adds a song to the end of the circular list
    void addSong(Song song);

    // Removes a song by its title
    void removeSong(std::string title);

    // Moves currentSong to the next track
    void nextSong();

    // Moves currentSong to the previous track
    void prevSong();

    // Prints the song currently playing
    void playCurrent();

    // Displays all songs in the playlist from the beginning
    void displayPlaylist();
    
    PlaylistNode* getHead() { return head; }
};

#endif //PLAYLIST_H
