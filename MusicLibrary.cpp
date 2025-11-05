#include "MusicLibrary.h"

// ===============================================
// TASK 1: ADD A SONG 
// ( ... no changes here ... )
// ===============================================

// Public function
void MusicLibrary::addSong(Song song) {
    root = addSongRecursive(root, song);
    std::cout << "Added to library: " << song.title << std::endl;
}

// Private helper function
BSTNode* MusicLibrary::addSongRecursive(BSTNode* node, Song song) {
    // Base Case: Found an empty spot
    if (node == nullptr) {
        return new BSTNode(song);
    }

    // Recursive Step: Go left or right
    if (song.title < node->song.title) {
        node->left = addSongRecursive(node->left, song);
    } else if (song.title > node->song.title) {
        node->right = addSongRecursive(node->right, song);
    } else {
        std::cout << "Song title '" << song.title << "' already in library." << std::endl;
    }
    return node;
}

// ===============================================
// TASK 2: SEARCH FOR A SONG 
// ( ... no changes to searchByTitle or searchRecursive ... )
// ===============================================

// Public function
void MusicLibrary::searchByTitle(std::string title) {
    BSTNode* result = searchRecursive(root, title);
    if (result != nullptr) {
        std::cout << "\n--- Song Found ---" << std::endl;
        std::cout << "Title: " << result->song.title << std::endl;
        std::cout << "Artist: " << result->song.artist << std::endl;
        std::cout << "--------------------" << std::endl;
    } else {
        std::cout << "\nSong '" << title << "' not found in library." << std::endl;
    }
}

// Private helper function
BSTNode* MusicLibrary::searchRecursive(BSTNode* node, std::string title) {
    // Base Case 1: Node is empty (song not found)
    if (node == nullptr) {
        return nullptr;
    }

    // Base Case 2: We found the song!
    if (node->song.title == title) {
        return node;
    }

    // Recursive Step: Search left or right
    if (title < node->song.title) {
        return searchRecursive(node->left, title); // Search left subtree
    } else {
        return searchRecursive(node->right, title); // Search right subtree
    }
}

// ===============================================
// TASK 3: DISPLAY ALL SONGS
// ( ... no changes here ... )
// ===============================================

// Public function
void MusicLibrary::displayAllSongs() {
    std::cout << "\n--- Full Music Library (A-Z) ---" << std::endl;
    printInOrder(root);
    std::cout << "------------------------------------" << std::endl;
}

// Private helper function (In-Order Traversal)
void MusicLibrary::printInOrder(BSTNode* node) {
    if (node != nullptr) {
        printInOrder(node->left); // 1. Go all the way left
        std::cout << "  " << node->song.title << " - " << node->song.artist << std::endl;
        printInOrder(node->right); // 3. Go right
    }
}

// ===============================================
// --- NEW FUNCTION IMPLEMENTATION ---
// ===============================================

/**
 * Finds a song by title and returns a pointer to it.
 * @return Pointer to the Song, or nullptr if not found.
 */
Song* MusicLibrary::findSong(std::string title) {
    BSTNode* node = searchRecursive(root, title);
    if (node != nullptr) {
        // Return a pointer to the song inside the node
        return &(node->song);
    }
    return nullptr;
}