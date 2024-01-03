#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const double weightTolerance = 0.1;
const double cementWeightMin = 24.9;
const double cementWeightMax = 25.1;
const double gravelSandWeightMin = 49.9;
const double gravelSandWeightMax = 50.1;
const double cementPrice = 3.0;
const double gravelSandPrice = 2.0;
const double specialPackPrice = 10.0;

struct Sack {
    char contents;
    double weight;
};

// Function to check a single sack
bool checkSingleSack(Sack sack) {
    if (sack.contents != 'C' && sack.contents != 'G' && sack.contents != 'S') {
        cout << "Invalid contents. Please use C, G, or S." << endl;
        return false;
    }

    if (sack.contents == 'C' && (sack.weight < cementWeightMin || sack.weight > cementWeightMax)) {
        cout << "Invalid weight for cement sack." << endl;
        return false;
    }

    if ((sack.contents == 'G' || sack.contents == 'S') &&
        (sack.weight < gravelSandWeightMin || sack.weight > gravelSandWeightMax)) {
        cout << "Invalid weight for gravel or sand sack." << endl;
        return false;
    }

    return true;
}

// Function to check a customer's order
double checkCustomerOrder(const vector<Sack>& order) {
    double totalWeight = 0.0;
    int rejectedSacks = 0;

    for (const auto& sack : order) {
        if (checkSingleSack(sack)) {
            totalWeight += sack.weight;
        } else {
            rejectedSacks++;
        }
    }

    cout << "Total weight of the order: " << fixed << setprecision(2) << totalWeight << " kg" << endl;
    cout << "Number of rejected sacks: " << rejectedSacks << endl;

    return totalWeight;
}

// Function to calculate the price for a customer's order
void calculateOrderPrice(double totalWeight, const vector<Sack>& order) {
    double regularPrice = 0.0;

    for (const auto& sack : order) {
        if (sack.contents == 'C') {
            regularPrice += cementPrice;
        } else {
            regularPrice += gravelSandPrice;
        }
    }

    int specialPacks = 0;
    for (const auto& sack : order) {
        if (sack.contents == 'C') {
            specialPacks++;
        }
    }

    double discountPrice = regularPrice - (specialPacks * specialPackPrice);

    cout << "Regular price for the order: $" << fixed << setprecision(2) << regularPrice << endl;

    if (specialPacks > 0) {
        cout << "Discount price for special packs: -$" << specialPacks * specialPackPrice << endl;
        cout << "New price for the order: $" << fixed << setprecision(2) << discountPrice << endl;
        cout << "Amount saved: $" << fixed << setprecision(2) << (regularPrice - discountPrice) << endl;
    }
}

int main() {
    int sackCount;
    cout << "Enter the number of sacks for the order: ";
    cin >> sackCount;

    vector<Sack> order;
    for (int i = 0; i < sackCount; ++i) {
        Sack sack;
        cout << "Enter contents for sack " << i + 1 << " (C for cement, G for gravel, S for sand): ";
        cin >> sack.contents;

        cout << "Enter weight for sack " << i + 1 << " (in kilograms): ";
        cin >> sack.weight;

        order.push_back(sack);
    }

    double totalWeight = checkCustomerOrder(order);
    calculateOrderPrice(totalWeight, order);

    return 0;
}