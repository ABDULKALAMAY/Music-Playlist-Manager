#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <string>
#include <iostream>

// --- Defines what a Song is ---
struct Song {
    std::string title;
    std::string artist;
    
    Song(std::string t, std::string a) : title(t), artist(a) {}
};

// --- Defines the Node for your Binary Search Tree ---
struct BSTNode {
    Song song;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Song s) : song(s), left(nullptr), right(nullptr) {}
};

// --- Defines your Music Library class ---
class MusicLibrary {
private:
    BSTNode* root; // The starting point of your BST

    // --- Private Helper Functions ---
    BSTNode* addSongRecursive(BSTNode* node, Song song);
    BSTNode* searchRecursive(BSTNode* node, std::string title);
    void printInOrder(BSTNode* node); // For displaying all songs

public:
    MusicLibrary() : root(nullptr) {} // Constructor

    // --- Public Functions (Your Tasks) ---
    void addSong(Song song);                // 
    void searchByTitle(std::string title);  // 
    void displayAllSongs();                 // For testing 
};

#endif //MUSICLIBRARY_H