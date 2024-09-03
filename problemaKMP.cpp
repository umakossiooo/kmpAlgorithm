#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isPatternInText(const std::string& text, const std::string& pattern) {
    size_t lastPos = 0;
    std::string::size_type pos = 0;
    size_t start = 0;

    for (size_t i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == '*') {
            std::string subPattern = pattern.substr(start, i - start);
            pos = text.find(subPattern, lastPos);
            if (pos == std::string::npos) {
                return false;
            }
            lastPos = pos + subPattern.length();
            start = i + 1;
        }
    }

    // Check for the last part after the last '*'
    std::string lastPart = pattern.substr(start);
    if (!lastPart.empty()) {
        pos = text.find(lastPart, lastPos);
        if (pos == std::string::npos) {
            return false;
        }
    }
    
    return true;
}

int main() {
    std::ifstream infile("problemaKMPInput.txt");
    if (!infile) {
        std::cerr << "No se puede abrir el archivo de entrada.\n";
        return 1;
    }

    int n;
    std::string text;
    infile >> n;
    infile.ignore();  // Ignorar el salto de línea después del entero
    std::getline(infile, text);

    std::vector<std::string> patterns(n);
    for (int i = 0; i < n; ++i) {
        std::getline(infile, patterns[i]);
    }

    for (const std::string& pattern : patterns) {
        if (isPatternInText(text, pattern)) {
            std::cout << pattern << " SI\n";
        } else {
            std::cout << pattern << " NO\n";
        }
    }

    return 0;
}
