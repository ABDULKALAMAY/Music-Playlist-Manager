#include "HistoryManager.h"
#include <iostream>

HistoryManager::HistoryManager() {
    // Constructor is empty, stack is already initialized
}

/**
 * Pushes a song onto the top of the history stack
 * @param song The song to add to the history
 */
void HistoryManager::pushSong(const Song& song) {
    historyStack.push(song);
    std::cout << "Added to history: " << song.title << std::endl;
}

/**
 * Pops a song from the history (for "play previous")
 * @return The last song played, or a "null" song if history is empty
 */
Song HistoryManager::popSong() {
    if (historyStack.empty()) {
        std::cout << "No songs in history." << std::endl;
        // Return a "null" song object
        return Song("Nothing", "Playing"); 
    }

    // Get the top song
    Song prevSong = historyStack.top();
    // Remove it from the stack
    historyStack.pop();
    
    return prevSong;
}

/**
 * Checks if the history is empty
 */
bool HistoryManager::isEmpty() {
    return historyStack.empty();
}

/**
 * Displays all songs in the history (newest to oldest)
 * This is non-destructive.
 */
void HistoryManager::displayHistory() {
    if (historyStack.empty()) {
        std::cout << "\n--- Play History ---" << std::endl;
        std::cout << "  History is empty." << std::endl;
        std::cout << "----------------------" << std::endl;
        return;
    }

    // To display a stack, we must pop it to a temporary stack
    std::stack<Song> tempStack;
    
    std::cout << "\n--- Play History (Newest to Oldest) ---" << std::endl;

    // Pop from original, print, and push to temp
    while (!historyStack.empty()) {
        Song s = historyStack.top();
        historyStack.pop();
        std::cout << "  " << s.title << " - " << s.artist << std::endl;
        tempStack.push(s);
    }
    std::cout << "-----------------------------------------" << std::endl;

    // Now, restore the original stack
    while (!tempStack.empty()) {
        historyStack.push(tempStack.top());
        tempStack.pop();
    }
}