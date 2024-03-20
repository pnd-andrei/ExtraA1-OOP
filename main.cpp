#include <iostream>
#include <fstream>
#include <string.h>
#include<string>

// ifmmp xpsme -> decoded in hello world

using namespace std;

void ReadDistribution(float frequencies[]) {
    ifstream read_init_dis("distribution.txt");
    float frequency;

    for (int i = 0; i < 26; ++i) {
        read_init_dis >> frequency;
        frequencies[i] = frequency;
    }

    read_init_dis.close();
}

void ExpectedDistribution(float expectedFreq[]) {
    float frequency;
    ifstream read_expected_dis("expected_distribution.txt");

    for (int i = 0; i < 26; ++i) {
        read_expected_dis >> frequency;
        expectedFreq[i] = frequency;
    }

    read_expected_dis.close();
}

// unused
void NormalizedFrequency(float expectedFreq[], int nrOfLetters, float normalizedFreq[]) {
    for (int i = 0; i < 26; ++i) {
        normalizedFreq[i] = expectedFreq[i] * nrOfLetters;
    }
}

float ChiSquaredDistance(float freq1[], float freq2[]) {
    float distance = 0;
    for (int i = 0; i < 26; ++i) {
        distance += (freq1[i] - freq2[i]) * (freq1[i] - freq2[i]) / freq2[i];
    }

    return distance;
}

void BreakCaesarCypher(int option, string& text, float freq[], float expectedFreq[]) {
    if (option == 2) {
        for (int i = 0; i < text.length(); ++i) {
            if (isalpha(text[i])) {
                text[i] = tolower(text[i]);
                freq[int(text[i]) - 97]++;
            }
        }
    }

    float originalFreq[26];
    if (option == 2) {
        copy(freq, freq + 26, originalFreq);
    }

    float minimumChiDistance = ChiSquaredDistance(freq, expectedFreq);
    string currText = text;

    for (int shift = 0; shift < 26; ++shift) {
        if (option == 2) {
			copy(originalFreq, originalFreq + 26, freq);
		}

        for (int i = 0; i < text.length(); ++i) {
            if (isalpha(text[i])) {
                if (text[i] == 'a') {
                    text[i] = 'z';
                }
                else if (text[i] == 'A') {
                    text[i] = 'Z';
                }
                else {
                    text[i] -= 1;
                }
            }
        }

        float temp = freq[0];
        for (int i = 0; i < 25; ++i) {
            freq[i] = freq[i + 1];
        }
        freq[25] = temp;

        float newChiDistance = ChiSquaredDistance(freq, expectedFreq);

        if (minimumChiDistance > newChiDistance) {
            minimumChiDistance = newChiDistance;
            currText = text;
        }
    }

    text = currText;
}

int main()
{
    string menu = "1 - Decode the input string.\n2 - Decode a given string.\nPress anything else to exit\n";
    float expectedFrequencies[26];

    ExpectedDistribution(expectedFrequencies);

    int option = 1;
    while (option != 0) {
        cout << menu;
        cin >> option;

        if (option == 1) {
            string input_string = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr,uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.";
            float defaultFrequencies[26];

            ReadDistribution(defaultFrequencies);
            BreakCaesarCypher(option, input_string, defaultFrequencies, expectedFrequencies);
            cout << "\n" << input_string << "\n\n";
        }
		else if (option == 2) {
        	string new_string;

            float frequencies[26];

            for (int i = 0; i < 26; ++i) {
                frequencies[i] = 0;
            }

        	cout << "Enter the string to decode: ";
        	cin.ignore();
        	getline(cin, new_string);
        
        	BreakCaesarCypher(option, new_string, frequencies, expectedFrequencies);
        	cout << "\n" << new_string << "\n\n";
        }
        else {
            option = 0;
        }
    }

    return 0;
}