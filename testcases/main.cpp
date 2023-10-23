#include <iostream>
#include <vector>
#include <string>
#include <regex>

class Dictionary {
public:
    std::vector<std::string> initKeywords = {"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const", "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype", "default", "define", "defined", "delete", "do", "double", "dynamic_cast", "elif", "elifdef", "elifndef", "else", "endif", "enum", "error", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "ifdef", "ifndef", "import", "include", "inline", "int", "line", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "pragma", "private", "protected", "public", "reflexpr", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synnextonized", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "undef", "union", "unsigned", "using", "virtual", "void", "volatile", "warning", "wchar_t", "while", "xor", "xor_eq", "__has_include", "__has_cpp_attribute"};

    std::vector<std::string> initOperators = {"=", "+", "-", "*", "/", "%", "++", "--", "<<", ">>", ">>>",
                                              "<<<", "&", "|", "^", "!", "~", "&&", "||", "->", ".", "?",
                                              ":", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "|=",
                                              "^=", "++", "--", "==", "!=", "<", ">", "<=", ">="};
};

class LexicalAnalyzer {
private:
    Dictionary dict;
    std::vector<std::string> keywords;
    std::vector<std::string> operators;
    std::vector<std::string> identifiers;
    std::vector<std::string> symbols;
    std::vector<std::string> constants;

public:
    void performLexAnalysis(const std::string &input) {
        std::regex symbolRegex("[\\W]*");
        std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
        std::regex constantRegex("[0-9]+");

        std::stringstream streamInput(input);
        std::string token;

        while(streamInput >> token) {
            if (std::find(dict.initKeywords.begin(), dict.initKeywords.end(), token)
                != dict.initKeywords.end()) {keywords.push_back(token);}

            else if (std::find(dict.initOperators.begin(), dict.initOperators.end(), token)
                     != dict.initOperators.end()) {operators.push_back(token);}

            else if (std::regex_search(token, symbolRegex)) {symbols.push_back(token);}

            else if (std::regex_search(token, identifierRegex)) {identifiers.push_back(token);}

            else if (std::regex_search(token, constantRegex)) {constants.push_back(token);}

            std::cout << "---- SUMMARY ----" << std::endl;
            std::cout << "Keyword: " << keywords.size() << std::endl;
            std::cout << "Operator: " << operators.size() << std::endl;
            std::cout << "Symbol: " << symbols.size() << std::endl;
            std::cout << "Identifier: " << identifiers.size() << std::endl;
            std::cout << "Constant: " << constants.size() << std::endl;
            std::cout << "-----------------" << "\n" <<std::endl;
        }

        std::cout << "---- SUMMARY ----" << std::endl;
        std::cout << "Keywords: " << keywords.size() << std::endl;
        for(const auto &element : keywords) {std::cout << element << std::endl;}
        std::cout << "Identifiers: " << identifiers.size() << std::endl;
        for(const auto &element : identifiers) {std::cout << element << std::endl;}
        std::cout << "Operators: " << operators.size() << std::endl;
        for(const auto &element : operators) {std::cout << element << std::endl;}
        std::cout << "Symbols: " << symbols.size() << std::endl;
        for(const auto &element : symbols) {std::cout << element << std::endl;}
        std::cout << "Constants: " << constants.size() << std::endl;
        for(const auto &element : constants) {std::cout << element << std::endl;}
        std::cout << "-----------------" << "\n" <<std::endl;

    }
};



int main() {
    LexicalAnalyzer run;
    std::string input = "#include <iostream>";
    run.performLexAnalysis(input);
    return 0;
}