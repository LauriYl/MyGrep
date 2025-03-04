#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void grepFile(const string& searchString, const string& filePath, bool showLineNumbers, bool countOccurrences) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    int occurrenceCount = 0;

    while (getline(file, line)) {
        if (line.find(searchString) != string::npos) {
            if (showLineNumbers) {
                cout << lineNumber << ": ";
            }
            cout << line << endl;
            occurrenceCount++;
        }
        lineNumber++;
    }

    if (countOccurrences) {
        cout << "\nOccurrences of lines containing \"" << searchString << "\": " << occurrenceCount << endl;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    cout << "argc = " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }

    // Jos ei ole argumentteja, käytetään manuaalista syötettä
    if (argc == 1) {
        string text, pattern;
        cout << "Give a string from which to search for: ";
        getline(cin, text);
        cout << "Give search string: ";
        getline(cin, pattern);

        size_t pos = text.find(pattern);
        if (pos != string::npos) {
            cout << "\"" << pattern << "\" found in \"" << text << "\" at position " << pos << endl;
        } else {
            cout << "\"" << pattern << "\" NOT found in \"" << text << "\"" << endl;
        }
        return 0;
    }

    bool showLineNumbers = false;
    bool countOccurrences = false;
    string searchString, filePath;

    // Käsitellään komentoriviargumentit
    if (argc == 4 && string(argv[1]).rfind("-o", 0) == 0) {
        string options = string(argv[1]).substr(2);
        if (options.find('l') != string::npos) showLineNumbers = true;
        if (options.find('o') != string::npos) countOccurrences = true;

        searchString = argv[2];
        filePath = argv[3];
    } else if (argc == 3) {
        searchString = argv[1];
        filePath = argv[2];
    } else {
        cerr << "Usage: " << argv[0] << " [-ol | -oo | -olo] <search_string> <file_path>" << endl;
        return 1;
    }

    // Suoritetaan tiedostohaku
    grepFile(searchString, filePath, showLineNumbers, countOccurrences);
    return 0;
}
