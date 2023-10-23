#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool at(const string &tok, const vector<string> &check)
{
    return find(check.begin(), check.end(), tok) != check.end();
}

bool is_word(const string &token)
{
    for (char ch : token)
    {
        if (!isalpha(ch))
            return false;
    }
    return true;
}

bool is_string_literal(const string &token)
{
    return (token.size() > 1) && (token.front() == '\"' && token.back() == '\"') || (token.front() == '\'' && token.back() == '\'');
}

int main()
{
    // open a txt file using fstream and put contents in a string
    ifstream file("test.txt");

    string test;
    while (file)
    {
        string line;
        getline(file, line);
        test += line + "\n";
    }

    cout << test << endl;
    // exit(0);

    // vector of c++ operators
    vector<string> operators = {
        "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=",
        "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", ">>>", "+=", "-=",
        "*=", "/=", "%=", "<<=", ">>=", ">>>=", "&=", "^=", "|=", "=", ".*",
        "->*", "->", "()", "[]", "new", "delete", "new[]", "delete[]"};

    // vector of c++ symbols
    vector<string> symbols = {
        "{", "}", "[", "]", "#", "(", ")", "<", ">", "<<", ">>", "::", ".",
        ".*", "->*", "->", "?", ":", ";", "...", "/*", "*/"};

    // vector of c++ keywords
    vector<string> keywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
        "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
        "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
        "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return",
        "co_yield", "decltype", "default", "define", "defined", "delete", "do", "double",
        "dynamic_cast", "elif", "elifdef", "elifndef", "else", "endif", "enum", "error",
        "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if",
        "ifdef", "ifndef", "import", "include", "inline", "int", "line", "long", "module",
        "mutable", "namespace", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "pragma", "private", "protected", "public", "reflexpr", "register",
        "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
        "static_assert", "static_cast", "struct", "switch", "synnextonized", "template",
        "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",
        "undef", "union", "unsigned", "using", "virtual", "void", "volatile", "warning",
        "wchar_t", "while", "xor", "xor_eq", "__has_include", "__has_cpp_attribute"};

    stringstream ss(test);
    string token;
    vector<string> tokens;

    while (ss >> token)
    {
        tokens.push_back(token);
    }

    vector<string> foundOperators;
    vector<string> foundSymbols;
    vector<string> foundKeywords;
    vector<string> foundIdentifiers;
    vector<string> foundConstants;

    bool inside_multiline_comment = false;

    for (auto tok : tokens)
    {
        int index = 0;

        // If the token starts a multi-line comment
        if (!inside_multiline_comment && tok.find("/*") != string::npos) {
            inside_multiline_comment = true;

            // If the token also ends the multi-line comment in the same token (like /* comment */)
            if (tok.find("*/") != string::npos) {
                inside_multiline_comment = false;
            }

            continue; // move to the next token without processing this one
        }

        // If we're inside a multi-line comment and this token ends it
        if (inside_multiline_comment && tok.find("*/") != string::npos) {
            inside_multiline_comment = false;
            continue; // move to the next token
        }

        // If we're inside a multi-line comment but the token doesn't end it
        if (inside_multiline_comment) {
            continue; // simply skip the token
        }

        // If the token starts a single-line comment
        if (tok.find("//") != string::npos) {
            break; // discard this token and all following tokens in the same line
        }

        if (is_string_literal(tok))
        {
            foundConstants.push_back(tok.substr(1, tok.length() - 2)); // Remove quotation marks.
            continue;
        }

        while (index < tok.length())
        {
            string ch(1, tok[index]);

            if (at(ch, operators))
            {
                foundOperators.push_back(ch);
                tok[index] = ' ';
            }
            else if (at(ch, symbols))
            {
                foundSymbols.push_back(ch);
                tok[index] = ' ';
            }

            index++;
        }

        stringstream ss(tok);
        string token;
        while (ss >> token)
        {
            if (at(token, keywords))
            {
                foundKeywords.push_back(token);
            }
            else if (is_word(token))
            {
                foundIdentifiers.push_back(token);
            }
            else
            {
                foundConstants.push_back(token);
            }
        }

        cout << "---- SUMMARY ----" << endl;
        cout << "Operators: " << foundOperators.size() << endl;
        cout << "Symbols: " << foundSymbols.size() << endl;
        cout << "Keywords: " << foundKeywords.size() << endl;
        cout << "Identifiers: " << foundIdentifiers.size() << endl;
        cout << "Constants: " << foundConstants.size() << endl;
        cout << "-----------------\n" << endl;
    }

    cout << "---- SUMMARY ----" << endl;
    cout << "Operators: " << foundOperators.size() << endl;
    for (auto op : foundOperators)
    {
        cout << op << endl;
    }
    cout << "\nSymbols: " << foundSymbols.size() << endl;
    for (auto sym : foundSymbols)
    {
        cout << sym << endl;
    }
    cout << "\nKeywords: " << foundKeywords.size() << endl;
    for (auto key : foundKeywords)
    {
        cout << key << endl;
    }
    cout << "\nIdentifiers: " << foundIdentifiers.size() << endl;
    for (auto id : foundIdentifiers)
    {
        cout << id << endl;
    }
    cout << "\nConstants: " << foundConstants.size() << endl;
    for (auto con : foundConstants)
    {
        cout << con << endl;
    }
    cout << "-----------------\n"
         << endl;

    return 0;
}