#include "rle.h"
// Constructor
rle::rle(int gamma) : gamma(gamma) {}

// Convert integer to gamma-bit binary string
int pow(int b, int e)
{
    int result = 1;
    for (int i = 0; i < e; i++)
    {
        result = result * b;
    }
    return result;
}
string bin(int i)
{
    string binary = "";
    while (i > 0)
    {
        binary = std::to_string((i % 2)) + binary;
        i = i / 2;
    }
    return binary;
}
string bin(int i, int pad)
{
    string binary = "";
    while (i > 0)
    {
        binary = std::to_string((i % 2)) + binary;
        i = i / 2;
    }
    while (binary.size() < pad)
    {
        binary = '0' + binary;
    }
    return binary;
}

int bintoi(string s)
{
    int result = 0;
    for (int i = 0; i < s.size(); i++)
    {
        result = result * 2;
        if (s[i] == '1')
        {
            result = result + 1;
        }
    }
    return result;
}
string rle::f(int i)
{
    string gamma_bstr = "";
    string bstr = bin(i);
    gamma_bstr += bstr[0];
    int count = 0;
    char c = bstr[0];
    for (int i = 0; i < bstr.size(); i++)
    {
        if (bstr[i] == c)
        {
            if (count < pow(2, gamma) - 1)
                count++;
            else
            {
                for (int i = 0; i < gamma; i++)
                {
                    gamma_bstr = gamma_bstr + "1";
                }
                for (int i = 0; i < gamma; i++)
                {
                    gamma_bstr = gamma_bstr + "0";
                }
                gamma_bstr = gamma_bstr;
                count = 1;
            }
        }
        else
        {
            c = bstr[i];
            gamma_bstr = gamma_bstr + bin(count, gamma);
            count = 1;
        }
    }
    gamma_bstr = gamma_bstr + bin(count, gamma);
    return gamma_bstr;
}


// Convert gamma-bit binary string to integer
int rle::g(string i)
{
    string binstr = "";
    char start = i[0];
    for (int pos = 1; pos < i.size(); pos = pos + gamma)
    {
        int count = bintoi(i.substr(pos, gamma));
        while (count > 0)
        {
            binstr = binstr + start;
            count--;
        }
        if (start == '0')
            start = '1';
        else
            start = '0';
    }
    return bintoi(binstr);
}

// Compress the input file
string rle::compress(string input_string)
{
    return f(bintoi(input_string));

    bool isbin = true;
    for (int i = 0; i < input_string.size(); i++){
        if (input_string[i] != '0' && input_string[i] != '1'){
            isbin = false;
            break;
        }
    }
    
    if (isbin){
        return bin(g(input_string));
    }
    string encoded = "";
    char c = input_string[0];
    int count = 0;
    for (int i = 0; i < input_string.size(); i++)
    {
        if (input_string[i] == c)
            count++;
        else
        {
            encoded = encoded + c + std::to_string(count);
            c = input_string[i];
            count = 1;
        }
    }
    encoded = encoded + c + std::to_string(count);
    return encoded;
}

// Decompress the input file
string rle::decompress(string input_string)
{
    return bin(g(input_string));

    bool isbin = true;
    for (int i = 0; i < input_string.size(); i++){
        if (input_string[i] != '0' && input_string[i] != '1'){
            isbin = false;
            break;
        }
    }
    
    if (true){
        return f(bintoi(input_string));
    }
    // string decode = "";
    // char c = input_string[0];
    // int count = 0;
    // string count_str = "";

    // for (int i = 1; i < input_string.size(); i = i + 1)
    // {
    //     if (48 <= int(input_string[i]) && int(input_string[i]) < 58)
    //     {
    //         count_str += input_string[i];
    //     }
    //     else
    //     {
    //         count = stoi(count_str);
    //         while (count > 0)
    //         {
    //             decode += c;
    //             count--;
    //         }
    //         c = input_string[i];
    //         count_str = "";
    //     }
    // }
    // count = stoi(count_str);
    // while (count > 0)
    // {
    //     decode += c;
    //     count--;
    // }
    // return decode;
}