#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
#include "Utils.h"

namespace sdds {
    void Utils::read(int& val, int min, int max, const char* ErrorMess, istream& is) {
        bool ok;
        char newline;
        const char* orgMes = ErrorMess;
        const char invalidInt[] = "Invalid Integer, try again: ";
        do {
            is >> val;
            newline = is.get();
            if (is.fail() || newline != '\n') {
                ok = false;
                is.clear();
                is.ignore(1000, '\n');
                ErrorMess = invalidInt;
            }
            else {
                ok = val <= max && val >= min;
                ErrorMess = orgMes;
            }
        } while (!ok && cout << ErrorMess);
    }
    void Utils::read(
        long long& val,
        long long min,
        long long max, const char* ErrorMess, istream& is) {
        bool ok;
        char newline;
        do {
            is >> val;
            newline = is.get();
            if (is.fail() || newline != '\n') {
                ok = false;
                is.clear();
                is.ignore(1000, '\n');
            }
            else {
                ok = val <= max && val >= min;
            }
        } while (!ok && cout << ErrorMess);
    }
    void Utils::read(char* str, int len, const char* errorMessage, istream& is) {
        bool ok;
        do {
            ok = true;
            is.getline(str, std::streamsize(len) + 1, '\n');
            if (is.fail()) {
                is.clear();
                is.ignore(1000, '\n');
                ok = false;
            }
        } while (!ok && cout << errorMessage);
    }
    void Utils::read(char* str, int minlen, int maxlen, const char* errorMessage, istream& is) {
        do {
            read(str, maxlen, errorMessage);
        } while (strlen(str) < size_t(minlen) && cout << errorMessage);
    }
    bool Utils::yes(istream& is) {
        char res;
        char newline;
        do {
            res = is.get();
            newline = is.get();
            if (newline != '\n') {
                is.ignore(1000, '\n');
                res = 'x';
            }
        } while (res != 'y' && res != 'Y' && res != 'n' && res != 'N'
            && cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ");
        return res == 'y' || res == 'Y';
    }
    bool Utils::confirmed(const char* action, istream& is) {
        cout << "This will " << action << '!' << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        return yes();
    }
    void Utils::toUpper(char* str) {
        while (*str) {
            *str = toupper(*str);
            str++;
        }
    }
    char* Utils::read(istream& is) {
        char* data = new char[ReadBufferSize];
        char* str = data;
        int noOfBuffers = 1;
        bool done;
        do {
            done = true;
            is.getline(str, ReadBufferSize, '\n');
            if (is.fail()) {
                noOfBuffers++;
                char* temp = new char[(ReadBufferSize - 1) * noOfBuffers + 1];
                strcpy(temp, data);
                delete[] data;
                data = temp;
                str = data + (ReadBufferSize - 1) * (noOfBuffers - 1);
                is.clear();
                done = false;
            }
        } while (!done);
        return data;
    }

}