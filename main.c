#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

FILE *infile, *outfile; //�ļ���ȡ
char token[MAX];   //�ַ����飬��ŵ�ǰ����ʶ��ĵ����ַ���
char ch; //�ַ���������ŵ�ǰ������ַ�
int pos = 0; //�ַ�����λ��ָ��
int lines = 1; //ͳ������
int words = 0; //ͳ�Ƶ��ʸ���,���Ϳո񲻼�Ϊ����
int chars = 0; //ͳ���ַ�����

char get_char()//��ȡ�ַ�
{
    ch = fgetc(infile);
    if (ch == EOF)
        printf("\n �ʷ����������,���������¼�� out.txt\n\n");
    chars++;
    return ch;
}

void get_nbc()//ÿ�ε���ʱ�����ch�е��ַ��Ƿ�Ϊ�ո������򷴸�����get_char()ֱ���ǿ�
{
    while (ch == ' ' || ch == '\t' || ch == '\b' || ch == '\n') {
        if (ch == '\n')
            lines++;
        get_char();
    }
}

void cat(char ch) //��ch�е��ַ����ӵ�token�ַ�����
{
    token[pos++] = ch;
}

int IsLetter(char ch) //�ж�ch�е��ַ��Ƿ�Ϊ��ĸ
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    else return 0;
}

int IsDigit(char ch) //�ж�ch�е��ַ��Ƿ�Ϊ����
{
    if (ch >= '0' && ch <= '9')
        return 1;
    else return 0;
}

int IsBound(char ch) //�ж�ch�е��ַ��Ƿ�Ϊ�ֽ��
{
    if (ch == '.' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == ',' ||
        ch == ';' ||
        ch == '#' || ch == '\'' || ch == '\"' || ch == '\?' || ch == ':')
        return 1;
    else return 0;
}

void Retract()  //��ǰָ����ˣ���ch�ÿ�
{
    pos--;
    ch = ' ';
}

int IsKey(char token[]) //�ж�token���Ƿ�Ϊ�ؼ���
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
    while (ch != EOF) {
        //ʶ������
        if (IsDigit(ch)) {
            pos = 0;
            while (IsDigit(ch)) {
                cat(ch);
                get_char();
            }
            //whileѭ���ڶ��� ���ֿ�ͷ+��ĸ ʱ����
            if (IsLetter(ch)) {
                token[0] = '\0';
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
                while (IsLetter(ch))
                    get_char();
            }
            token[pos++] = '\0';
            if (token[0] != '\0')
                fprintf(outfile, "%s      ����\n", token);
            words++;
            get_nbc();
        }

            //ʶ��ؼ��֡���ʶ��
        else if (IsLetter(ch)) {
            pos = 0;
            while (IsLetter(ch) || IsDigit(ch) || ch == '_') {
                cat(ch);
                get_char();
            }
            token[pos++] = '\0';
            if (IsKey(token) == 1)
                fprintf(outfile, "%s      �ؼ���\n", token);
            else fprintf(outfile, "%s      ��ʶ��\n", token);

            words++;
            get_nbc();
        }

            //ʶ�������(��������� ��ϵ����� �߼������ ��ֵ�����)
        else if (ch == '+') //+,++,+=
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '+' || ch == '=') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_nbc();
            }
        } else if (ch == '-') //-,--,-=
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '-' || ch == '=') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_nbc();
            }
        } else if (ch == '*' || ch == '%' || ch == '!' || ch == '>' || ch == '<' ||
                   ch == '=') //*,*=,%,%=!,!=,>,>=,<,<=,=,==
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '=') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_nbc();
            }
        } else if (ch == '&') // &&
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '&') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
                get_char();
                get_nbc();
            }
        } else if (ch == '|') // ||
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '|') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
                get_char();
                get_nbc();
            }
        } else if (ch == '/') // /,/=,//,/*
        {
            pos = 0;
            cat(ch);
            get_char();
            if (ch == '=') {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_char();
                get_nbc();
            } else if (ch == '/') // ����//��ע��
            {
                cat(ch);
                token[pos++] = '\0';
                fprintf(outfile, "%s      ע��\n", token);
                Retract();
                while (ch != '\n' && ch != EOF) //���������һ�����Կ���EOF
                    get_char();
                get_nbc();
            } else if (ch == '*') // ����/**/��ע��
            {
                cat(ch);
                while (1) {
                    get_char();
                    while (ch != '*') //һֱѭ��ֱ������*/
                    {
                        get_nbc(); //ע��Ҳ���������
                        get_char();
                    }
                    cat(ch);
                    get_char();
                    if (ch == '/') {
                        cat(ch);
                        token[pos++] = '\0';
                        fprintf(outfile, "%s      ע��\n", token);
                        Retract();
                        get_char();
                        get_nbc();
                        break;
                    }
                }

            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s      �����\n", token);
                get_nbc();
            }
        }

            //ʶ��ֽ��
        else if (IsBound(ch)) {
            pos = 0;
            cat(ch);
            token[pos++] = '\0';
            fprintf(outfile, "%s      �ֽ��\n", token);
            get_char();
            get_nbc();
        } else {
            fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
            get_char();
            get_nbc();
        }
    }

    //��ӡԴ������Ϣ
    printf("\n����%d��\n", lines);
    printf("\n���ʸ���Ϊ%d��(�����ؼ��֡���ʶ�������ָ���)\n", words);
    printf("\n�ַ�����Ϊ%d��(�����ո񡢻��С�ע���е��ַ����ڵ������ַ�)\n\n\n", chars - 1); //�ַ�������Ҫȥ��EOF
    system("pause");
    return 0;
}

