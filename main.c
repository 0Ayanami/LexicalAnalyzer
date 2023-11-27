#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

FILE *infile, *outfile; //�ļ���ȡ
char token[MAX];   //�ַ����飬��ŵ�ǰ����ʶ��ĵ����ַ���
char C; //�ַ���������ŵ�ǰ������ַ�
int pos = 0; //�ַ�����λ��ָ��
int lines = 1; //ͳ������
int words = 0; //ͳ�Ƶ��ʸ���,���Ϳո񲻼�Ϊ����
int keys = 0; //ͳ�ƹؼ��ָ���
int flags = 0;//ͳ�Ʊ�ʶ������
int dig = 0;//ͳ�Ƴ�������
int ass = 0;//ͳ�Ƹ�ֵ����
int ope = 0;//ͳ�����������
int sep = 0;//ͳ�Ʒָ�������

char get_char()//ÿ����һ�ξʹ�infile�ж�ȡһ���ַ����������������C��
{
    C = fgetc(infile);
    if (C == EOF)
    {
        printf("\n �ʷ����������,���������¼�� out.txt\n\n");
    }

    return C;
}

void get_nbc()//ÿ�ε���ʱ�����C�е��ַ��Ƿ�Ϊ�ո������򷴸�����get_char()ֱ���ǿ�
{
    if (C != EOF){
        while (C == ' ' || C == '\t' || C == '\b' || C == '\n') {
            if (C == '\n'){
                lines++;
            }
            get_char();
        }
    }
}

void cat(char C) //��C�е��ַ����ӵ�token�ַ�����
{
    token[pos++] = C;
}

int letter(char C) //�ж�C�е��ַ��Ƿ�Ϊ��ĸ
{
    if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
        return 1;
    else return 0;
}

int digit(char C) //�ж�C�е��ַ��Ƿ�Ϊ����
{
    if (C >= '0' && C <= '9')
        return 1;
    else return 0;
}

int bound(char C) //�ж�C�е��ַ��Ƿ�Ϊ�ֽ��
{
    if (C == '{' || C == '}' || C == '[' || C == ']' || C == '(' || C == ')' ||
        C == ';')
        return 1;
    else return 0;
}

//void Retract()  //��ǰָ����ˣ���C�ÿ�
//{
//    pos--;
//    C = ' ';
//}

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
    else if (strcmp(token, "float") == 0)
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
        //ʶ������
        if (digit(C)) {
            pos = 0;
            while (digit(C)) {
                cat(C);
                get_char();
            }
            //�ڶ���С����ʱ�������������
            if (C == '.') {
                cat(C);
                get_char();
                //С��������Ҫ�����֣�������������򱨴�
                if (!digit(C))
                    token[0] = '\0';
                while (digit(C)) {
                    cat(C);
                    get_char();
                }
            }
            //�ڶ���ָ������ʱ�������������
            if (C == 'E' || C == 'e') {
                cat(C);
                get_char();
                //�ж��Ƿ���������
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
            //whileѭ���ڶ��� ���ֿ�ͷ+��ĸ ʱ����
            if (letter(C)) {
                token[0] = '\0';
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
                while (letter(C))
                    get_char();
            }
            token[pos++] = '\0';
            if (token[0] != '\0')
                fprintf(outfile, "%s����\n", token);
            dig++;
            words++;
            get_nbc();
        }

            //ʶ��ؼ��֡���ʶ��
        else if (letter(C)) {
            pos = 0;
            while (letter(C) || digit(C) || C == '_') {
                cat(C);
                get_char();
            }
            token[pos++] = '\0';
            if (IsKey(token) == 1) {
                fprintf(outfile, "%s�ؼ���\n", token);
                keys++;
            } else {
                fprintf(outfile, "%s��ʶ��\n", token);
                flags++;
            }
            words++;
            get_nbc();
        }

            //ʶ�������(��������� ��ϵ����� �߼������ ��ֵ�����)
        else if (C == '+') //+,++,+=
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '+' || C == '=') {
                cat(C);
                token[pos++] = '\0';
                if (C == '=') {
                    fprintf(outfile, "%s��ֵ\n", token);
                    ass++;
                } else {
                    fprintf(outfile, "%s�����\n", token);
                    ope++;
                }
                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s�����\n", token);
                ope++;
                words++;
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
                if (C == '=') {
                    fprintf(outfile, "%s��ֵ\n", token);
                    ass++;

                } else {
                    fprintf(outfile, "%s�����\n", token);
                    ope++;

                }
                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s�����\n", token);
                ope++;
                words++;
                get_nbc();
            }

        } else if (C == '*' || C == '%' || C == '!' || C == '>' || C == '<' ||
                   C == '=') //*,*=,%,%=,!,!=,>,>=,<,<=,=,==
        {
            pos = 0;
            cat(C);
            get_char();
            if (C == '=') {
                cat(C);
                token[pos++] = '\0';
                if (token[0] == '*' || token[0] == '%') {
                    fprintf(outfile, "%s��ֵ\n", token);
                    ass++;

                } else {
                    fprintf(outfile, "%s�����\n", token);
                    ope++;
                }
                words++;
                get_char();
                get_nbc();
            } else {
                token[pos++] = '\0';
                if (token[0] == '=') {
                    fprintf(outfile, "%s��ֵ\n", token);
                    ass++;

                } else {
                    fprintf(outfile, "%s�����\n", token);
                    ope++;
                }
                words++;
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
                fprintf(outfile, "%s�����\n", token);
                ope++;
                words++;
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
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
                fprintf(outfile, "%s�����\n", token);
                ope++;
                words++;
                get_char();
                get_nbc();
            } else {
                fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
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
                fprintf(outfile, "%s��ֵ\n", token);
                ass++;
                words++;
                get_char();
                get_nbc();
            } else if (C == '/') // ����//��ע��
            {
                cat(C);
                token[pos++] = '\0';
//                fprintf(outfile, "%sע��\n", token);
//                Retract();
                while (C != '\n' && C != EOF) //���������һ�����Կ���EOF
                    get_char();
                get_nbc();
            } else if (C == '*') // ����/**/��ע��
            {
                cat(C);

                while (1) {
                    get_char();
                    while (1) //һֱѭ��ֱ������*/
                    {
                        get_nbc(); //ע��Ҳ���������
                        if(C == '*')
                            break;
                        get_char();
                    }
                    cat(C);
                    get_char();
                    if (C == '/') {
                        cat(C);
                        token[pos++] = '\0';
//                        fprintf(outfile, "%sע��\n", token);
//                        Retract();
                        get_char();
                        get_nbc();
                        break;
                    }

                }

            } else {
                token[pos++] = '\0';
                fprintf(outfile, "%s�����\n", token);
                ope++;
                get_nbc();
                words++;
            }
        }
            //ʶ��ֽ��
        else if (bound(C)) {
            pos = 0;
            cat(C);
            token[pos++] = '\0';
            fprintf(outfile, "%s�ָ���\n", token);
            sep++;
            get_char();
            get_nbc();
            words++;
        } else {
            fprintf(stderr, "���󣺵�%d���зǷ��ַ���\n", lines); // ���������Ϣ����׼������
            get_char();
            get_nbc();
        }
    }


    //��ӡԴ������Ϣ
    fprintf(outfile, "%d��\n", lines);
    fprintf(outfile, "%d������\n", words);
    fprintf(outfile, "%d�ؼ���\n", keys);
    fprintf(outfile, "%d��ʶ��\n", flags);
    fprintf(outfile, "%d����\n", dig);
    fprintf(outfile, "%d��ֵ\n", ass);
    fprintf(outfile, "%d�����\n", ope);
    fprintf(outfile, "%d�ָ���", sep);
    system("pause");
    return 0;
}

