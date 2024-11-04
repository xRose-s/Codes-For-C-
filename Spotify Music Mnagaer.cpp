#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SongNode {
public:
    string title;
    SongNode* next;

    SongNode(const string& songTitle) : title(songTitle), next(nullptr) {}
};

class MusicPlayer {
private:
    SongNode* head;
    SongNode* currentSong;
    vector<string> songQueue;

public:
    MusicPlayer() : head(nullptr), currentSong(nullptr) {}

    ~MusicPlayer() {
        while (head != nullptr) {
            SongNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addSongToEnd(const string& songTitle) {
        SongNode* newSong = new SongNode(songTitle);
        if (head == nullptr) {
            head = newSong;
            currentSong = head;
        } else {
            SongNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newSong;
        }
        songQueue.push_back(songTitle); // Add to queue
    }

    void playCurrentSong() {
        if (currentSong != nullptr) {
            cout << "Playing: " << currentSong->title << endl;
        } else {
            cout << "No song is currently playing." << endl;
        }
    }

    void playNextSong() {
        if (currentSong != nullptr && currentSong->next != nullptr) {
            currentSong = currentSong->next;
            playCurrentSong();
        } else {
            cout << "End of the playlist reached." << endl;
        }
    }

    void playPreviousSong() {
        if (currentSong != nullptr && currentSong != head) {
            SongNode* temp = head;
            while (temp != nullptr && temp->next != currentSong) {
                temp = temp->next;
            }
            currentSong = temp;
            playCurrentSong();
        } else {
            cout << "This is the first song in the playlist." << endl;
        }
    }

    void shufflePlaylist() {
        if (songQueue.size() < 2)
            return;

        string first = songQueue.front();
        songQueue.erase(songQueue.begin());
        songQueue.push_back(first);

        cout << "Playlist shuffled." << endl;
    }

    void displayPlaylist() {
        cout << "Current Playlist:" << endl;
        SongNode* temp = head;
        while (temp != nullptr) {
            if (temp == currentSong) {
                cout << "> " << temp->title << endl;
            } else {
                cout << "  " << temp->title << endl;
            }
            temp = temp->next;
        }
        cout << "Current queue: ";
        for (const auto& song : songQueue) {
            cout << song << " ";
        }
        cout << endl;
    }

    void showControls() {
        cout << "Controls:\n"
             << "  Space - Play Current Song\n"
             << "  s     - Shuffle the playlist\n"
             << "  n     - Next song\n"
             << "  b     - Previous song\n"
             << "  q     - Quit the program\n";
    }
};

int main() {
    MusicPlayer player;

    int numSongs;
    cout << "Enter the number of songs to add: ";
    cin >> numSongs;
    cin.ignore(); // Clear newline character from the buffer

    for (int i = 1; i <= numSongs; ++i) {
        string songTitle;
        cout << "Enter title for song " << i << ": ";
        getline(cin, songTitle);
        player.addSongToEnd(songTitle);
    }

    // Show controls
    player.showControls();

    // Display playlist after adding songs
    player.displayPlaylist();

    // Play the first song
    player.playCurrentSong();

    char command;
    while (true) {
        cout << "\nEnter command: ";
        cin >> command;

        switch (command) {
            case ' ':
                player.playCurrentSong();
                break;
            case 's':
                player.shufflePlaylist();
                break;
            case 'n':
                player.playNextSong();
                break;
            case 'b':
                player.playPreviousSong();
                break;
            case 'q':
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}
