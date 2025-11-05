#include "Playlist.h"

// --- Adds a song to the end of the playlist ---
void Playlist::addSong(Song song) {
    PlaylistNode* newNode = new PlaylistNode(song);

    // Case 1: The list is empty
    if (head == nullptr) {
        head = newNode;
        head->next = head; // Point to itself to make it circular
        head->prev = head; // Point to itself to make it circular
        currentSong = head;
    }
    // Case 2: The list is NOT empty
    else {
        PlaylistNode* tail = head->prev; // Get the last node

        // Link the new node
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    std::cout << "Added to playlist: " << song.title << std::endl;
}

// --- Removes a song from the playlist by its title ---
void Playlist::removeSong(std::string title) {
    if (head == nullptr) {
        std::cout << "Playlist is empty." << std::endl;
        return;
    }

    PlaylistNode* temp = head;
    bool found = false;

    // We must loop through the circular list
    do {
        if (temp->song.title == title) {
            found = true;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (found) {
        // --- Logic to remove the node 'temp' ---

        // Case 1: It's the only node in the list
        if (temp->next == temp) {
            head = nullptr;
            currentSong = nullptr;
        }
        // Case 2: It's not the only node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            // If we are deleting the 'head' node, move 'head' forward
            if (temp == head) {
                head = temp->next;
            }
            // If we are deleting the 'currentSong', move 'currentSong' forward
            if (temp == currentSong) {
                currentSong = temp->next;
            }
        }

        delete temp; // Free the memory
        std::cout << "Removed from playlist: " << title << std::endl;
    } else {
        std::cout << "Song '" << title << "' not found in playlist." << std::endl;
    }
}

// --- Prints the currently selected song ---
void Playlist::playCurrent() {
    if (currentSong == nullptr) {
        std::cout << "Playlist is empty. Nothing to play." << std::endl;
    } else {
        std::cout << "Now Playing: " << currentSong->song.title << " - " << currentSong->song.artist << std::endl;
    }
}

// --- Moves to the next song ---
void Playlist::nextSong() {
    if (currentSong == nullptr) {
        std::cout << "Playlist is empty." << std::endl;
    } else {
        currentSong = currentSong->next; // Just move the pointer
        playCurrent();
    }
}

// --- Moves to the previous song ---
void Playlist::prevSong() {
    if (currentSong == nullptr) {
        std::cout << "Playlist is empty." << std::endl;
    } else {
        currentSong = currentSong->prev; // Just move the pointer
        playCurrent();
    }
}

// --- Displays all songs in order ---
void Playlist::displayPlaylist() {
    if (head == nullptr) {
        std::cout << "Playlist is empty." << std::endl;
        return;
    }

    std::cout << "\n--- Current Playlist ---" << std::endl;
    PlaylistNode* temp = head;
    do {
        std::cout << "  " << temp->song.title << " - " << temp->song.artist;
        if (temp == currentSong) {
            std::cout << "  <-- (Now Playing)";
        }
        std::cout << std::endl;
        temp = temp->next;
    } while (temp != head);
    std::cout << "--------------------------" << std::endl;
}

