#include <iostream>
#include <string>
#include <limits> // For clearing cin buffer

// Include all our project headers
#include "MusicLibrary.h"    // Member 2
#include "Playlist.h"        // Member 1
#include "PlaybackManager.h" // Member 3
#include "HistoryManager.h"  // Member 4

// --- Create global instances of our managers ---
MusicLibrary myLibrary;
Playlist myPlaylist;
PlaybackManager myPlaybackManager;
HistoryManager myHistoryManager;

// --- Global state for the player ---
Song currentSong("Nothing", "Playing");
bool isPlaying = false;


/**
 * Helper function to add initial songs to the library
 */
void seedLibrary() {
    std::cout << "Seeding music library..." << std::endl;
    myLibrary.addSong(Song("Bohemian Rhapsody", "Queen"));
    myLibrary.addSong(Song("Stairway to Heaven", "Led Zeppelin"));
    myLibrary.addSong(Song("Hotel California", "Eagles"));
    myLibrary.addSong(Song("Shape of You", "Ed Sheeran"));
    myLibrary.addSong(Song("Blinding Lights", "The Weeknd"));
    myLibrary.addSong(Song("Yesterday", "The Beatles"));
    myLibrary.addSong(Song("Africa", "Toto"));
    std::cout << "Library seeded." << std::endl;
}

/**
 * Helper function to display the main menu
 */
void displayMenu() {
    std::cout << "\n=============================================" << std::endl;
    std::cout << "           🎶 MUSIC PLAYER 🎶" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << " Now Playing: " << currentSong.title << " - " << currentSong.artist 
              << (isPlaying ? " (Playing)" : " (Paused)") << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "  LIBRARY (MEMBER 2)" << std::endl;
    std::cout << "    1. Display Full Music Library (A-Z)" << std::endl;
    std::cout << "    2. Search Library for a Song" << std::endl;
    std::cout << "\n  PLAYLIST (MEMBER 1)" << std::endl;
    std::cout << "    3. Add Song to Playlist (from Library)" << std::endl;
    std::cout << "    4. Display Current Playlist" << std::endl;
    std::cout << "    5. Remove Song from Playlist" << std::endl;
    std::cout << "\n  PLAYBACK (MEMBER 3 & 4)" << std::endl;
    std::cout << "    6. Load Playlist into Queue (Ordered)" << std::endl;
    std::cout << "    7. Load Playlist into Queue (SHUFFLE)" << std::endl;
    std::cout << "    8. ► Play Next Song (from Queue)" << std::endl;
    std::cout << "    9. ◄ Play Previous Song (from History)" << std::endl;
    std::cout << "   10. █ Show Play History" << std::endl;
    std::cout << "\n  SYSTEM" << std::endl;
    std::cout << "   11. Exit" << std::endl;
    std::cout << "=============================================" << std::endl;
}

/**
 * Helper to get a line of text from the user
 */
std::string getStringInput(std::string prompt) {
    std::string input;
    std::cout << prompt;
    // Clear the input buffer from previous 'cin >>'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, input);
    return input;
}

/**
 * Helper to get an integer choice
 */
int getChoice() {
    int choice;
    std::cout << "\nEnter your choice (1-11): ";
    while (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

/**
 * Logic for Case 3: Add Song to Playlist
 */
void handleAddToPlaylist() {
    std::string title = getStringInput("Enter title of song to add from library: ");
    Song* songToAdd = myLibrary.findSong(title); // Use new function
    
    if (songToAdd != nullptr) {
        // We found it! Add a *copy* to the playlist
        myPlaylist.addSong(*songToAdd);
    } else {
        std::cout << "Song '" << title << "' not found in library." << std::endl;
    }
}

/**
 * Logic for Case 5: Remove Song from Playlist
 */
void handleRemoveFromPlaylist() {
    myPlaylist.displayPlaylist();
    std::string title = getStringInput("\nEnter title of song to remove: ");
    myPlaylist.removeSong(title);
}

/**
 * Logic for Case 8: Play Next
 */
void handlePlayNext() {
    // 1. If a song is currently playing, add it to history
    if (isPlaying || currentSong.title != "Nothing") {
        myHistoryManager.pushSong(currentSong);
    }
    
    // 2. Get the next song from the queue
    Song nextSong = myPlaybackManager.playNextInQueue();
    
    // 3. Update the global state
    currentSong = nextSong;
    if (currentSong.title == "Nothing") {
        isPlaying = false;
    } else {
        isPlaying = true;
    }
}

/**
 * Logic for Case 9: Play Previous
 */
void handlePlayPrevious() {
    if (myHistoryManager.isEmpty()) {
        std::cout << "Play history is empty. Cannot go back." << std::endl;
        return;
    }
    
    // 1. If a song is playing, add it back to the *front* of the queue
    if (isPlaying || currentSong.title != "Nothing") {
        myPlaybackManager.addSongToFrontOfQueue(currentSong);
    }
    
    // 2. Pop the previous song from history
    Song prevSong = myHistoryManager.popSong();
    
    // 3. Update global state
    currentSong = prevSong;
    isPlaying = true;
    std::cout << "Now Playing (from history): " << currentSong.title << " - " << currentSong.artist << std::endl;
}


int main() {
    // Add some initial songs to the library
    seedLibrary();

    bool running = true;
    while (running) {
        displayMenu();
        int choice = getChoice();

        switch (choice) {
            case 1: // Display Library
                myLibrary.displayAllSongs();
                break;
            case 2: // Search Library
                myLibrary.searchByTitle(getStringInput("Enter song title to search: "));
                break;
            case 3: // Add to Playlist
                handleAddToPlaylist();
                break;
            case 4: // Display Playlist
                myPlaylist.displayPlaylist();
                break;
            case 5: // Remove from Playlist
                handleRemoveFromPlaylist();
                break;
            case 6: // Load Queue (Ordered)
                myPlaybackManager.loadQueue(myPlaylist);
                break;
            case 7: // Load Queue (Shuffle)
                myPlaybackManager.shufflePlay(myPlaylist);
                break;
            case 8: // Play Next
                handlePlayNext();
                break;
            case 9: // Play Previous
                handlePlayPrevious();
                break;
            case 10: // Show History
                myHistoryManager.displayHistory();
                break;
            case 11: // Exit
                running = false;
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        
        if (running) {
            std::cout << "\n(Press Enter to continue...)";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

    return 0;
}