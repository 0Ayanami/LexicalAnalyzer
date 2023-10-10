#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

FILE *infile, *outfile; //文件读取
char token[MAX];   //字符数组，存放当前正在识别的单词字符串
char C; //字符变量，存放当前读入的字符
int pos = 0; //字符串的位置指针
int lines = 1; //统计行数
int words = 0; //统计单词个数,标点和空格不计为单词
int chars = 0; //统计字符个数

char get_char()//每调用一次就从infile中读取一个字符，并把它放入变量C中
{
    C = fgetc(infile);
    if (C == EOF)
        printf("\n 词法分析已完成,分析结果记录在 out.txt\n\n");
    chars++;
    return C;
}

void get_nbc()//每次调用时，检查C中的字符是否为空格，若是则反复调用get_char()直至非空
{
    while (C == ' ' || C == '\t' || C == '\b' || C == '\n') {
        if (C == '\n')
            lines++;
        get_char();
    }
}

void cat(char C) //将C中的字符连接到token字符串后
{
    token[pos++] = C;
}

int letter(char C) //判断C中的字符是否为字母
{
    if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
        return 1;
    else return 0;
}

int digit(char C) //判断C中的字符是否为数字
{
    if (C >= '0' && C <= '9')
        return 1;
    else return 0;
}

int bound(char C) //判断C中的字符是否为分界符
{
    if (C == '.' || C == '{' || C == '}' || C == '[' || C == ']' || C == '(' || C == ')' || C == ',' ||
        C == ';' ||
        C == '#' || C == '\'' || C == '\"' || C == '\?' || C == ':')
        return 1;
    else return 0;
}

//void Retract()  //向前指针回退，将C置空
//{
//    pos--;
//    C = ' ';
//}

int IsKey(char token[]) //判断token中是否为关键字
{
    if (strcmp(token, "int") == 0)
        return 1;
    else if (strcmp(token, "char") == 0)
        return 1;
    else if (strcmp(token, "bool") == 0)
        return 1;
    else if (strcmp(token, "void") == 0)
        return 1;
    else if (strcmp(token, "if") == 0)
        return 1;
    else if (strcmp(token, "else") == 0)
        return 1;
    else if (strcmp(token, "while") == 0)
        return 1;
    else if (strcmp(token, "for") == 0)
        return 1;
    else if (strcmp(token, "continue") == 0)
        return 1;
    else if (strcmp(token, "break") == 0)
        return 1;
    else if (strcmp(token, "return") == 0)
        return 1;
    else if (strcmp(token, "int") == 0)
        return 1;
    else if (strcmp(token, "char") == 0)
        return 1;
    else if (strcmp(token, "string") == 0)
        return 1;
    else if (strcmp(token, "new") == 0)
        return 1;
    else if (strcmp(token, "delete") == 0)
        return 1;
    else if (strcmp(token, "struct") == 0)
        return 1;
    else if (strcmp(token, "const") == 0)
        return 1;
    else if (strcmp(token, "void") == 0)
        return 1;
    else return 0;
}

int main() {
    if ((infile = fopen("D:\\\\analyser\\\\source.txt", "r")) == NULL) {
        printf("Open source file error!\n");
        exit(0);
    }
    if ((outfile = fopen("D:\\\\analyser\\\\out.txt", "w")) == NULL) {
        printf("Open out file error!\n");
        exit(0);
    }
    get_char();
    get_nbc();
    while (C != EOF) {
        //识别数字
        if (digit(C)) {
            pos = 0;
            while (digit(C)) {
                cat(C);
                get_char();
            }
            //在读到小数点时继续往后读数字
            if (C == '.') {
                cat(C);
                get_char();
                //小数点后必须要有数字，如果不是数字则报错
                if (!digit(C))
                    token[0] = '\0';
                while (digit(C)) {
                    cat(C);
                    get_char();
                }
            }
            //在读到指数部分时继续往后读数字
            if (C == 'E' || C == 'e') {
                cat(C);
                get_char();
                //判断是否有正负号
                if (C == '+' || C == '-') {
                    cat(C);
                    get_char();
                }
                if (!digit(C))
                    token[0] = '\0';
                while (digit(C)) {
                    cat(C);
                    get_char();
                }
            }
            //while循环在读到 数字开头+字母 时报错
            if (letter(C)) {
                token[0] = '\0';
                fprintf(stderr, "错误：第%d行有非法字符！\n", lines); // 输出错误信息到标准错误流
                while (letter(C))
                    get_char();
            }
            token[pos++] = '\0';
            if (token[0] != '\0')
                fprintf(outfile, "%s      数字\n", token);
            words++;
            get_nbc();
        }

        //识别关键字、标识符
        else if (letter(C)) {
            pos = 0;
            while (letter(C) || digit(C) || C == '_') {
                cat(C);
                get_char();
            }
            token[pos++] = '\0';
            if (IsKey(token) == 1)
                fprintf(outfile, "%s      关键字\n", token);
            else fprintf(outfile, "%s      标识符\n", token);

            words++;
            get_nbc();
        }

            //识别运算符(算术运算符 关系运算符 逻辑运算符 赋值运算符)
        else if (C == '+') //+,++,+=
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '+' || C == '=') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_nbc();
            }
        } else if (C == '-') //-,--,-=
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '-' || C == '=') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_nbc();
            }
        } else if (C == '*' || C == '%' || C == '!' || C == '>' || C == '<' ||
                   C == '=') //*,*=,%,%=!,!=,>,>=,<,<=,=,==
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '=') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_nbc();
            }
        } else if (C == '&') // &&
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '&') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "错误：第%d行有非法字符！\n", lines); // 输出错误信息到标准错误流
                get_char();
                get_nbc();
            }
        } else if (C == '|') // ||
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '|') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "错误：第%d行有非法字符！\n", lines); // 输出错误信息到标准错误流
                get_char();
                get_nbc();
            }
        } else if (C == '/') // /,/=,//,/*
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '=') {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_char();
                get_nbc();
            } else if (C == '/') // 处理//型注释
            {
                cat(C);
                token[pos++] = '\0';
                fprintf(outfile, "%s      注释\n", token);
//                Retract();
                while (C != '\n' && C != EOF) //可能是最后一行所以考虑EOF
                    get_char();
                get_nbc(


                        );
            } else if (C == '*') // 处理/**/型注释
            {
                cat(C);
                while (1) {
                    get_char();
                    while (C != '*') //一直循环直到出现*/
                    {
                        get_nbc(); //注释也需计算行数
                        get_char();
                    }
                    cat(C);
                    get_char();
                    if (C == '/') {
                        cat(C);
                        token[pos++] = '\0';
                        fprintf(outfile, "%s      注释\n", token);
//                        Retract();
                        get_char();
                        get_nbc();
                        break;
                    }
                }

            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      运算符\n", token);
                get_nbc();
            }
        }

            //识别分界符
        else if (bound(C)) {
            pos = 0;
            cat(C);
            token[pos++] = '\0';
            fprintf(outfile, "%s      分界符\n", token);
            get_char();
            get_nbc();
        } else {
            fprintf(stderr, "错误：第%d行有非法字符！\n", lines); // 输出错误信息到标准错误流
            get_char();
            get_nbc();
        }
    }

    //打印源程序信息
    printf("\n共计%d行\n", lines);
    printf("\n单词个数为%d个(包括关键字、标识符和数字个数)\n", words);
    printf("\n字符总数为%d个(包括空格、换行、注释中的字符在内的所有字符)\n\n\n", chars - 1); //字符个数需要去掉EOF
    system("pause");
    return 0;
}

