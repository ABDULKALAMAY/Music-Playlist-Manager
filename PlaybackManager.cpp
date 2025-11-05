#include "PlaybackManager.h"
#include "Playlist.h" // We need the full definition of Playlist to iterate
#include <iostream> // Added for std::cout

// --- Loads the playlist (in order) into the queue ---
void PlaybackManager::loadQueue(Playlist& playlist) {
    // 1. Clear any old songs from the queue
    std::queue<Song> emptyQueue;
    std::swap(playbackQueue, emptyQueue);

    // 2. Get the head of the playlist
    PlaylistNode* current = playlist.getHead();
    
    if (current == nullptr) {
        std::cout << "Playlist is empty. Nothing to load." << std::endl;
        return;
    }

    // 3. Loop through the circular list and add each song to the queue
    std::cout << "Loading queue in order..." << std::endl;
    do {
        playbackQueue.push(current->song);
        current = current->next;
    } while (current != playlist.getHead());
    
    std::cout << "Queue loaded." << std::endl;
}

// --- Creates a shuffled queue from the playlist ---
void PlaybackManager::shufflePlay(Playlist& playlist) {
    // 1. Clear any old songs from the queue
    std::queue<Song> emptyQueue;
    std::swap(playbackQueue, emptyQueue);

    PlaylistNode* current = playlist.getHead();

    if (current == nullptr) {
        std::cout << "Playlist is empty. Nothing to shuffle." << std::endl;
        return;
    }

    // 3. Copy all songs from the circular list into a temporary vector
    std::vector<Song> tempVector;
    do {
        tempVector.push_back(current->song);
        current = current->next;
    } while (current != playlist.getHead());

    // 4. Shuffle the vector
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tempVector.begin(), tempVector.end(), std::default_random_engine(seed));

    // 5. Load the shuffled vector into the playback queue
    std::cout << "Shuffling playlist and loading queue..." << std::endl;
    for (const Song& song : tempVector) {
        playbackQueue.push(song);
    }
    std::cout << "Queue shuffled and loaded." << std::endl;
}


// --- "Plays" (removes) the next song from the queue and returns it ---
Song PlaybackManager::playNextInQueue() {
    if (playbackQueue.empty()) {
        std::cout << "Playback queue is empty. Load or shuffle a playlist first." << std::endl;
        return Song("Nothing", "Playing"); // Return "null" song
    }

    // 1. Get the song at the front of the queue
    Song nextSong = playbackQueue.front();

    // 2. "Play" it (print it)
    std::cout << "Playing from queue: " << nextSong.title << " - " << nextSong.artist << std::endl;

    // 3. Remove it from the queue
    playbackQueue.pop();
    
    // 4. Return it
    return nextSong;
}

// --- NEW FUNCTION ---
// Adds a song back to the front of the queue
void PlaybackManager::addSongToFrontOfQueue(const Song& song) {
    // 1. Create a new temporary queue
    std::queue<Song> newQueue;
    
    // 2. Push the new song first
    newQueue.push(song);
    
    // 3. Push all the old songs
    while (!playbackQueue.empty()) {
        newQueue.push(playbackQueue.front());
        playbackQueue.pop();
    }
    
    // 4. Replace the old queue with the new one
    playbackQueue = newQueue;
    
    std::cout << "Added " << song.title << " back to the front of the queue." << std::endl;
}