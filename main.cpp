#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool at(const string &tok, const vector<string> &check) {
    return find(check.begin(), check.end(), tok) != check.end();
}

bool is_word(const string &token) {
    for (char ch : token) {if (!isalpha(ch)) return false;}
    return true;
}

bool is_string_literal(const string &token) {
    return (token.size() > 1) && (token.front() == '\"' && token.back() == '\"')
        || (token.front() == '\'' && token.back() == '\'');
}

bool is_include_angled(const string &token) {
    return (token.front() == '<' && token.back() == '>');
}

int main()
{
    ifstream file("test.txt");
    string currentLine;
    vector<string> extraSymbols;

    string test;
    while (file) {
        string line;
        getline(file, line);
        if (line.find("//") != string::npos) {
            line = line.substr(0, line.find("//"));
        }
        test += line + "\n";
    }

    cout << test << endl;

    vector<string> operators = {
            "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=",
            "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", ">>>", "+=", "-=",
            "*=", "/=", "%=", "<<=", ">>=", ">>>=", "&=", "^=", "|=", "=", ".*",
            "->*", "->", "()", "[]", "new", "delete", "new[]", "delete[]"};

    vector<string> symbols = {
            "{", "}", "[", "]", "#", "(", ")", "<", ">", "<<", ">>", "::", ".",
            ".*", "->*", "->", "?", ":", ";", "...", "/*", "*/"};

    vector<string> keywords = {
            "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
            "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
            "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
            "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return",
            "co_yield", "decltype", "default", "define", "defined", "delete", "do", "double",
            "dynamic_cast", "elif", "elifdef", "elifndef", "else", "endif", "enum", "error",
            "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if",
            "import", "inline", "int", "line", "long", "module",
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

    while (ss >> token) {tokens.push_back(token);}

    vector<string> foundOperators;
    vector<string> foundSymbols;
    vector<string> foundKeywords;
    vector<string> foundIdentifiers;
    vector<string> foundConstants;

    for (auto tok : tokens) {
        int index = 0;

        if (is_string_literal(tok)) {
            foundConstants.push_back(tok.substr(1, tok.length() - 2));
            continue;
        }

        if (is_include_angled(tok)) {
            foundConstants.push_back(tok.substr(1, tok.length() - 2));
            foundSymbols.emplace_back("<");
            foundSymbols.emplace_back(">");
            continue;
        }

        if (at(tok, operators)) {
            foundOperators.push_back(tok);
            continue;
        }

        if (at(tok, symbols)) {
            foundSymbols.push_back(tok);
            continue;
        }

        while (index < tok.length()) {
            string ch(1, tok[index]);

            if (at(ch, operators)) {
                foundOperators.push_back(ch);
                tok[index] = ' ';
            }
            else if (at(ch, symbols)) {
                foundSymbols.push_back(ch);
                tok[index] = ' ';
            }
            index++;
        }

        stringstream ss(tok);
        string token;
        while (ss >> token) {
            if (at(token, keywords)) {
                foundKeywords.push_back(token);
            }
            else if (is_word(token)) {
                foundIdentifiers.push_back(token);
            }
            else {
                foundConstants.push_back(token);
            }
        }
    }

    cout << "---- SUMMARY ----" << endl;
    cout << "Operators: " << foundOperators.size() << endl;
    for (const auto& op : foundOperators) {
        cout << op << endl;
    }
    cout << "\nSymbols: " << foundSymbols.size() << endl;
    for (const auto& sym : foundSymbols) {
        cout << sym << endl;
    }
    cout << "\nKeywords: " << foundKeywords.size() << endl;
    for (const auto& key : foundKeywords) {
        cout << key << endl;
    }
    cout << "\nIdentifiers: " << foundIdentifiers.size() << endl;
    for (const auto& id : foundIdentifiers) {
        cout << id << endl;
    }
    cout << "\nConstants: " << foundConstants.size() << endl;
    for (const auto& con : foundConstants) {
        cout << con << endl;
    }
    cout << "-----------------\n" << endl;

    return 0;
}
