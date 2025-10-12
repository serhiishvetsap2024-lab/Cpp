#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SignalGenerator {
    string signalType;
    double maxFreq;
    bool hasModulation;

public:
    SignalGenerator() : signalType("Unknown"), maxFreq(0), hasModulation(false) {}

    SignalGenerator(string type, double freq, bool mod) {
        setData(type, freq, mod);
    }

    SignalGenerator(const SignalGenerator& s) {
        signalType = s.signalType;
        maxFreq = s.maxFreq;
        hasModulation = s.hasModulation;
        cout << "copied " << signalType << "\n";
    }

    SignalGenerator& operator=(const SignalGenerator& s) {
        if (this != &s) {
            signalType = s.signalType;
            maxFreq = s.maxFreq;
            hasModulation = s.hasModulation;
        }
        return *this;
    }

    ~SignalGenerator() {
        cout << "deleted " << signalType << "\n";
    }

    void setData(string type, double freq, bool mod) {
        if (freq <= 0) {
            cerr << "bad data\n";
            signalType = "Unknown";
            maxFreq = 0;
            hasModulation = false;
            return;
        }
        signalType = type;
        maxFreq = freq;
        hasModulation = mod;
    }

    void print() const {
        cout << signalType << " "
             << maxFreq << "Hz "
             << (hasModulation ? "with modulation" : "no modulation") << "\n";
    }

    bool matchType(const string& type) const {
        return signalType == type;
    }

    bool highFreq(double freq) const {
        return maxFreq >= freq;
    }

    bool modulationEnabled() const {
        return hasModulation;
    }
};

int main() {
    vector<SignalGenerator> generators;
    generators.emplace_back("Sine", 20000, true);
    generators.emplace_back("Square", 10000, false);
    generators.emplace_back("Triangle", 15000, true);

    cout << "All signal generators:\n";
    for (const auto& g : generators) {
        g.print();
    }

    cout << "\nCopying first generator:\n";
    SignalGenerator copyGen = generators[0];
    copyGen.print();

    cout << "\nGenerators of type 'Sine':\n";
    for (const auto& g : generators) {
        if (g.matchType("Sine")) {
            g.print();
        }
    }

    cout << "\nGenerators with frequency >= 15000Hz:\n";
    for (const auto& g : generators) {
        if (g.highFreq(15000)) {
            g.print();
        }
    }

    cout << "\nGenerators with modulation:\n";
    for (const auto& g : generators) {
        if (g.modulationEnabled()) {
            g.print();
        }
    }

    cout << "\n---Creating new signal generator---\n";
    string type;
    double freq;
    char modChar;
    bool mod;

    cout << "Enter signal type: ";
    cin >> type;
    cout << "Enter max frequency (Hz): ";
    cin >> freq;
    cout << "Has modulation? (y/n): ";
    cin >> modChar;
    mod = (modChar == 'y' || modChar == 'Y');

    SignalGenerator userGen(type, freq, mod);
    cout << "Created generator: ";
    userGen.print();

    return 0;
}
