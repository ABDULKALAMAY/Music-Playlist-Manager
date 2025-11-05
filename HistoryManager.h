#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <stack>
#include "MusicLibrary.h" // For the Song struct

class HistoryManager {
private:
    // We use the standard template library (STL) stack
    std::stack<Song> historyStack;

public:
    HistoryManager(); // Constructor

    // Pushes a song onto the top of the history stack
    void pushSong(const Song& song);

    // Pops a song from the history and returns it
    // Used for the "play previous" button
    Song popSong();

    // Displays all songs in the history from newest to oldest
    void displayHistory();

    // Checks if the history is empty
    bool isEmpty();
};

#endif //HISTORYMANAGER_H