#include <bits/stdc++.h>

using namespace std;
class Sport {
protected:
    int minutes, level;

public:
    Sport(int minutes, int level) : minutes(minutes),
                                    level(level) {
    }
    virtual string getDescription() = 0;
    virtual int getSportIntensity() = 0;
};
class SportRun : public Sport {
public:
    SportRun(int m, int l) : Sport(m, l) {}
    // 实现getDescription
    string getDescription() {
        return "You're running for " + to_string(minutes) + " minute(s)";
    }
    // 实现getSportIntensity
    int getSportIntensity() {
        return minutes / 10 * level;
    }
};

class SportBicycle : public Sport {
public:
    SportBicycle(int m, int l) : Sport(m, l) {}
    // 实现getDescription
    string getDescription() {
        return "You're riding for " + to_string(minutes) + " minute(s)";
    }
    // 实现getSportIntensity
    int getSportIntensity() {
        return (minutes / 5) * (minutes / 5) * level;
    }
};

int main() {
    Sport *sp = new SportRun(2, 3);
    cout << sp->getDescription();
    return 0;
}