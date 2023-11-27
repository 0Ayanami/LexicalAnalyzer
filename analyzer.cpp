#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX 100

string filename = "";

std::ifstream infile;//文件读取

char token[MAX];//字符数组，存放当前正在识别的单词字符串
char C;//字符变量，存放当前读入的字符
int pos = 0;//字符串的位置指针
int lines = 1;//统计行数
int words = 0;//统计单词个数,标点和空格不计为单词
int keys = 0;//统计关键字个数
int flags = 0;//统计标识符个数
int dig = 0;//统计常数个数
int ass = 0;//统计赋值个数
int ope = 0;//统计运算符个数
int sep = 0;//统计分隔符个数

string getFilename() {
    if (filename == "") {
        char s[20];
        cin.getline(s, 20);
        string fs = "/data/workspace/myshixun/词法分析C/src/step1/";
        return fs + string(s).substr(2, 20);
    }
    return filename;
}

char get_char() {//每调用一次就从infile中读取一个字符，并把它放入变量C中
    C = infile.get();
//    if (C == EOF) {
//        std::cout << "\n 词法分析已完成，分析结果记录在out.txt\n\n";
//    }
    return C;
}

void get_nbc() {//每次调用时，检查C中的字符是否为空格，若是则反复调用get_char()直至非空
    while (C == ' ' || C == '\t' || C == '\b' || C == '\n') {
        if (C == '\n') {
            lines++;
        }
        get_char();
    }
}

void cat(char C) {//将C中的字符连接到token字符串后
    token[pos++] = C;
}

int letter(char C) {//判断C中的字符是否为字母
    if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}

int digit(char C) {//判断C中的字符是否为数字
    if (C >= '0' && C <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int bound(char C) {//判断C中的字符是否为分界符
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