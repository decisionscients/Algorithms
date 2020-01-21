#include <iostream>
#include <string>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))


std::string Add(std::string x, std::string y) {
    unsigned int length = max(x.size(), y.size());
    int carry = 0;
    int sum_col;  // sum of two digits in the same column
    std::string result;

    // pad the shorter string with zeros
    while (x.size() < length)
        x.insert(0, "0");

    while (y.size() < length)
        y.insert(0, "0");

    // build result string from right to left
    for (int i = length - 1; i >= 0; i--) {
        sum_col = (x[i] - '0') + (y[i] - '0') + carry;
        carry = sum_col / 10;
        result.insert(0, std::to_string(sum_col % 10));
    }

    if (carry)
        result.insert(0, std::to_string(carry));

    // remove leading zeros
    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

std::string Subtract(std::string x, std::string y) {
    unsigned int length = max(x.size(), y.size());
    int diff;
    std::string result;

    while (x.size() < length)
        x.insert(0, "0");

    while (y.size() < length)
        y.insert(0, "0");

    for (int i = length - 1; i >= 0; i--) {
        diff = (x[i] - '0') - (y[i] - '0');
        if (diff >= 0)
            result.insert(0, std::to_string(diff));
        else {

            // borrow from the previous column
            int j = i - 1;
            while (j >= 0) {
                x[j] = ((x[j] - '0') - 1) % 10 + '0';
                if (x[j] != '9')
                    break;
                else
                    j--;
            }
            result.insert(0, std::to_string(diff + 10));
        }

    }

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

std::string Karatsuba(std::string x, std::string y) {
    unsigned int length = max(x.size(), y.size());

    while (x.size() < length)
        x.insert(0, "0");

    while (y.size() < length)
        y.insert(0, "0");

    if (length == 1)
        return std::to_string((x[0] - '0') * (y[0] - '0'));

    std::string a = x.substr(0, length / 2);
    std::string b = x.substr(length / 2, length - length / 2);
    std::string c = y.substr(0, length / 2);
    std::string d = y.substr(length / 2, length - length / 2);
    std::string p = Add(a, b);
    std::string q = Add(c, d);

    std::string ac = Karatsuba(a, c);
    std::string bd = Karatsuba(b, d);
    std::string pq = Karatsuba(p, q);
    std::string adbc = Subtract(pq, Add(ac, bd));

    for (unsigned int i = 0; i < 2 * (length - length / 2); i++)
        ac.append("0");
    for (unsigned int i = 0; i < length - length / 2; i++)
        adbc.append("0");

    std::string result = Add(Add(ac, adbc), bd);

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

int main() {
    std::string s1, s2;
    std::cout << "Enter the first number: ";
    std::cin >> s1;
    std::cout << "\nEnter the second number: ";
    std::cin >> s2;
    std::cout << Karatsuba(s1, s2) << std::endl;
    return 0;
}
