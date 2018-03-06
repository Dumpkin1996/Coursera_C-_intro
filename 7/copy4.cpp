#include <iostream>
#include <string>
using namespace std;

const string keyword[] = {"copy", "add", "find", "rfind", "insert", "reset", "print"};
const int keywordNumber = 7;
string Input[21];

int convert(string toConvert) {
    int result = 0;
    while (toConvert[0] == '0')
        toConvert = toConvert.substr(1, toConvert.length() - 1);
    while (!toConvert.empty()) {
        result = result * 10 + toConvert[0] - '0';
        toConvert = toConvert.substr(1, toConvert.length() - 1);
    }
    return result;
}

bool check(string input) {
    for (int i = 0; i < keywordNumber; i++)
        if (input == keyword[i])
            return true;
    return false;
}

string ext(string &input) {
    string temp = input.substr(0, input.find(' '));
    input = input.substr(input.find(' ') + 1);
    return temp;
}

bool checkNumber(string input) {
    for (int i = 0; i < input.length(); i++)
        if (input[i] < '0' || input[i] > '9')
            return false;
    return convert(input) < 100000;
}

string convertBack(int input) {
    if (input == 0) return "0";
    string temp = "";
    while (input != 0) {
        temp = (char) (input % 10 + '0') + temp;
        input /= 10;
    }
    return temp;
}

string apply(string func, string argu) {
    int n, x, l;
    string s, s1, s2;
    if (func == "copy") {
        n = convert(ext(argu));
        x = convert(ext(argu));
        l = convert(ext(argu));
        return Input[n].substr((unsigned long) x, (unsigned long) l) + ' ' + argu;
    } else if (func == "add") {
        s1 = ext(argu);
        s2 = ext(argu);
        if (checkNumber(s1) && checkNumber(s2)) {
            int temp = convert(s1) + convert(s2);
            return convertBack(temp) + ' ' + argu;
        } else return s1 + s2 + ' ' + argu;
    } else if (func == "find") {
        s = ext(argu);
        n = convert(ext(argu));
        if (Input[n].find(s) == string::npos)
            return convertBack((int) Input[n].length()) + ' ' + argu;
        else {
            string temp = convertBack((int) Input[n].find(s));
            return temp + ' ' + argu;
        }
    } else if (func == "rfind") {
        s = ext(argu);
        n = convert(ext(argu));
        if (Input[n].rfind(s) == string::npos)
            return convertBack((int) Input[n].length()) + ' ' + argu;
        else return convertBack((int) Input[n].rfind(s)) + ' ' + argu;
    } else if (func == "insert") {
        s = ext(argu);
        n = convert(ext(argu));
        x = convert(ext(argu));
        Input[n].insert((unsigned long) x, s);
    } else if (func == "reset") {
        s = ext(argu);
        n = convert(ext(argu));
        Input[n] = s;
    } else if (func == "print") {
        n = convert(ext(argu));
        cout << Input[n] << endl;
    }
    return "";
}

string dispose1(string input) {
    if (input.find(' ') == string::npos) return input;
    string func = input.substr(0, input.find(' '));
    string argu = input.substr(input.find(' ') + 1);
    if (check(func)) {
        string temp = apply(func, dispose1(argu));
        return temp;
    }
    else return func + ' ' + dispose1(argu);
}

int main() {
    int n;
    string manipulate;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> Input[i];
        cin.ignore();
    }
    while (getline(cin, manipulate)) {
        if (manipulate == "over") break;
        if (manipulate == "printall") {
            for (int i = 1; i <= n; i++)
                cout << Input[i] << endl;
            continue;
        }
        dispose1(manipulate);
    }
    return 0;
}