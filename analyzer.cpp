#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#define MAX 100

string filename = "";
std::ifstream infile;

char token[MAX];
char C;
int pos = 0;
int lines = 1;
int words = 0;
int keys = 0;
int flags = 0;
int dig = 0;
int ass = 0;
int ope = 0;
int sep = 0;

string getFilename() {
    if (filename == "") {
        char s[20];
        cin.getline(s, 20);
        string fs = "/data/workspace/myshixun/词法分析C/src/step1/";
        return fs + string(s).substr(2, 20);
    }
    return filename;
}

char get_char() {
    C = infile.get();
//    if (C == EOF) {
//        std::cout << "\n 词法分析已完成，分析结果记录在out.txt\n\n";
//    }
    return C;
}

void get_nbc() {
    while (C == ' ' || C == '\t' || C == '\b' || C == '\n') {
        if (C == '\n') {
            lines++;
        }
        get_char();
    }
}

void cat(char C) {
    token[pos++] = C;
}

int letter(char C) {
    if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}

int digit(char C) {
    if (C >= '0' && C <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int bound(char C) {
    if (C == '{' || C == '}' || C == '[' || C == ']' || C == '(' || C == ')' || C == ';') {
        return 1;
    } else {
        return 0;
    }
}

int IsKey(const char *token) {
    if (std::string(token) == "int" || std::string(token) == "char" || std::string(token) == "bool" ||
        std::string(token) == "void" || std::string(token) == "if" || std::string(token) == "else" ||
        std::string(token) == "while" || std::string(token) == "for" || std::string(token) == "continue" ||
        std::string(token) == "break" || std::string(token) == "return" || std::string(token) == "int" ||
        std::string(token) == "char" || std::string(token) == "string" || std::string(token) == "float" ||
        std::string(token) == "delete" || std::string(token) == "struct" || std::string(token) == "const") {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    filename = getFilename();
    infile.open(filename);
    if (!infile.is_open()) {
        std::cout << "Open source file error!" << std::endl;
        return 1;
    }

    get_char();
    get_nbc();

    while (C != EOF) {
        if (digit(C)) {
            pos = 0;
            while (digit(C)) {
                cat(C);
                get_char();
            }

            if (C == '.') {
                cat(C);
                get_char();

                if (!digit(C)) {
                    token[0] = '\0';
                }

                while (digit(C)) {
                    cat(C);
                    get_char();
                }
            }

            if (C == 'E' || C == 'e') {
                cat(C);
                get_char();

                if (C == '+' || C == '-') {
                    cat(C);
                    get_char();
                }

                if (!digit(C)) {
                    token[0] = '\0';
                }

                while (digit(C)) {
                    cat(C);
                    get_char();
                }
            }

            if (letter(C)) {
                token[0] = '\0';
                std::cerr << "错误：第" << lines << "行有非法字符！" << std::endl;
                while (letter(C)) {
                    get_char();
                }
            }

            token[pos++] = '\0';

            if (token[0] != '\0') {
                std::cout << token << "常数\n";
            }

            dig++;
            words++;
            get_nbc();
        } else if (letter(C)) {
            pos = 0;

            while (letter(C) || digit(C) || C == '_') {
                cat(C);
                get_char();
            }

            token[pos++] = '\0';

            if (IsKey(token) == 1) {
                std::cout << token << "关键字\n";
                keys++;
            } else {
                std::cout << token << "标识符\n";
                flags++;
            }

            words++;
            get_nbc();
        } else if (C == '+') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '+' || C == '=') {
                cat(C);
                token[pos++] = '\0';

                if (C == '=') {
                    std::cout << token << "赋值\n";
                    ass++;
                } else {
                    std::cout << token << "运算符\n";
                    ope++;
                }

                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                std::cout << token << "运算符\n";
                ope++;
                words++;
                get_nbc();
            }
        } else if (C == '-') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '-' || C == '=') {
                cat(C);
                token[pos++] = '\0';

                if (C == '=') {
                    std::cout << token << "赋值\n";
                    ass++;
                } else {
                    std::cout << token << "运算符\n";
                    ope++;
                }

                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                std::cout << token << "运算符\n";
                ope++;
                words++;
                get_nbc();
            }
        } else if (C == '*' || C == '%' || C == '!' || C == '>' || C == '<' || C == '=') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '=') {
                cat(C);
                token[pos++] = '\0';

                if (token[0] == '*' || token[0] == '%') {
                    std::cout << token << "赋值\n";
                    ass++;
                } else {
                    std::cout << token << "运算符\n";
                    ope++;
                }

                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';

                if (token[0] == '=') {
                    std::cout << token << "赋值\n";
                    ass++;
                } else {
                    std::cout << token << "运算符\n";
                    ope++;
                }

                words++;
                get_nbc();
            }
        } else if (C == '&') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '&') {
                cat(C);
                token[pos++] = '\0';
                std::cout << token << "运算符\n";
                ope++;
                words++;
                get_char();
                get_nbc();
            } else {
                std::cerr << "错误：第" << lines << "行有非法字符！" << std::endl;
                get_char();
                get_nbc();
            }
        } else if (C == '|') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '|') {
                cat(C);
                token[pos++] = '\0';
                std::cout << token << "运算符\n";
                ope++;
                words++;
                get_char();
                get_nbc();
            } else {
                std::cerr << "错误：第" << lines << "行有非法字符！" << std::endl;
                get_char();
                get_nbc();
            }
        } else if (C == '/') {
            pos = 0;
            cat(C);
            get_char();

            if (C == '=') {
                cat(C);
                token[pos++] = '\0';
                std::cout << token << "赋值\n";
                ass++;
                words++;
                get_char();
                get_nbc();
            } else if (C == '/') {
                cat(C);
                token[pos++] = '\0';

                while (C != '\n' && C != EOF) {
                    get_char();
                }

                get_nbc();
            } else if (C == '*') {
                cat(C);

                while (1) {
                    get_char();

                    while (1) {
                        get_nbc();
                        if(C == '*')
                            break;
                        get_char();
                    }

                    cat(C);
                    get_char();

                    if (C == '/') {
                        cat(C);
                        token[pos++] = '\0';
                        get_char();
                        get_nbc();
                        break;
                    }
                }
            } else {
                token[pos++] = '\0';
                std::cout << token << "运算符\n";
                ope++;
                get_nbc();
                words++;
            }
        } else if (bound(C)) {
            pos = 0;
            cat(C);
            token[pos++] = '\0';
            std::cout << token << "分隔符\n";
            sep++;
            get_char();
            get_nbc();
            words++;
        } else {
            std::cerr << "错误：第" << lines << "行有非法字符！" << std::endl;
            get_char();
            get_nbc();
        }
    }

    std::cout << lines << "行" << std::endl;
    std::cout << words << "个词语" << std::endl;
    std::cout << keys << "关键字" << std::endl;
    std::cout << flags << "标识符" << std::endl;
    std::cout << dig << "常数" << std::endl;
    std::cout << ass << "赋值" << std::endl;
    std::cout << ope << "运算符" << std::endl;
    std::cout << sep << "分隔符" << std::endl;

    infile.close();
    return 0;
}