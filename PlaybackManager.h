#ifndef PLAYBACKMANAGER_H
#define PLAYBACKMANAGER_H

#include <queue>       // For the std::queue
#include <vector>      // For shuffling
#include <string>
#include <algorithm>   // For std::shuffle
#include <random>      // For the shuffle engine
#include <chrono>      // For seeding the shuffle engine

#include "Playlist.h"      
#include "MusicLibrary.h"  

class PlaybackManager {
private:
    std::queue<Song> playbackQueue; 

public:
    PlaybackManager() {} 

    // --- Member 3's Core Functions ---
    void loadQueue(Playlist& playlist);
    void shufflePlay(Playlist& playlist);

    // --- MODIFIED FUNCTION ---
    // "Plays" and removes the next song, returning it
    Song playNextInQueue();
    
    // --- NEW FUNCTION ---
    // Adds a song back to the front of the queue (for "play previous")
    void addSongToFrontOfQueue(const Song& song);
};

#endif //PLAYBACKMANAGER_H