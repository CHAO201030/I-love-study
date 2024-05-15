/*
 * Copyright (c) 2024, Wangdao programmer training camp CPP 58th
 *
 * Authors:
 *   - CHAO  
 *     GitHub:https://github.com/CHAO201030/I-love-study
 *     Gitee :https://gitee.com/chao201030/I-love-study
 *
 * This software is licensed under the MIT license.
 * For more information, please refer to the LICENSE file.
 *
 * Description:
 *   This is a simple C Lexical Analyzer based on C.
 *
 * Date: 2024-5-12
 */

#include"scanner.h"

static char* strtoken(Token token)
{
    switch (token.type)
    {
        // Single character Tokens
    case TOKEN_LEFT_PAREN:              return "(";
    case TOKEN_RIGHT_PAREN:             return ")";
    case TOKEN_LEFT_BRACKET:            return "[";
    case TOKEN_RIGHT_BRACKET:           return "]";
    case TOKEN_LEFT_BRACE:              return "{";
    case TOKEN_RIGHT_BRACE:             return "}";
    case TOKEN_COMMA:                   return ",";
    case TOKEN_DOT:                     return ".";
    case TOKEN_SEMICOLON:               return ";";
    case TOKEN_TILDE:                   return "~";
        // One or two character Tokens
    case TOKEN_PLUS:                    return "+";
    case TOKEN_PLUS_PLUS:               return "++";
    case TOKEN_PLUS_EQUAL:              return "+=";
    case TOKEN_MINUS:                   return "-";
    case TOKEN_MINUS_MINUS:             return "--";
    case TOKEN_MINUS_EQUAL:             return "-=";
    case TOKEN_MINUS_GREATER:           return "->";
    case TOKEN_STAR:                    return "*";
    case TOKEN_STAR_EQUAL:              return "*=";
    case TOKEN_SLASH:                   return "/";
    case TOKEN_SLASH_EQUAL:             return "/=";
    case TOKEN_PERCENT:                 return "%";
    case TOKEN_PERCENT_EQUAL:           return "%=";
    case TOKEN_AMPER:                   return "&";
    case TOKEN_AMPER_EQUAL:             return "&=";
    case TOKEN_AMPER_AMPER:             return "&&";
    case TOKEN_PIPE:                    return "|";
    case TOKEN_PIPE_EQUAL:              return "|=";
    case TOKEN_PIPE_PIPE:               return "||";
    case TOKEN_HAT:                     return "^";
    case TOKEN_HAT_EQUAL:               return "^=";
    case TOKEN_EQUAL:                   return "=";
    case TOKEN_EQUAL_EQUAL:             return "==";
    case TOKEN_BANG:                    return "!";
    case TOKEN_BANG_EQUAL:              return "!=";
    case TOKEN_LESS:                    return "<";
    case TOKEN_LESS_EQUAL:              return "<=";
    case TOKEN_LESS_LESS:               return "<<";
    case TOKEN_GREATER:                 return ">";
    case TOKEN_GREATER_EQUAL:           return ">=";
    case TOKEN_GREAER_GREATER: 	        return ">>";
        // three character Tokens
    case TOKEN_LESS_LESS_EQUAL:         return "<<=";
    case TOKEN_GREATER_GREATER_EQUAL:   return">>=";
        // Literal value : identifier, character, string, number
    case TOKEN_IDENTIFIER:              return "IDENTIFIER";
    case TOKEN_CHARACTER:               return "CHARACTER";
    case TOKEN_STRING:                  return "STRING";
    case TOKEN_NUMBER:                  return "NUMBER";
        // Key words
    case TOKEN_SIGNED:                  return "SIGNED";
    case TOKEN_UNSIGNED:                return "UNSIGNED";
    case TOKEN_CHAR:                    return "CHAR";
    case TOKEN_SHORT:                   return "SHORT";
    case TOKEN_INT:                     return "INT";
    case TOKEN_LONG:                    return "LONG";
    case TOKEN_FLOAT:                   return "FLOAT";
    case TOKEN_DOUBLE:                  return "DOUBLE";
    case TOKEN_STRUCT:                  return "STRUCT";
    case TOKEN_UNION:                   return "UNION";
    case TOKEN_ENUM:                    return "ENUM";
    case TOKEN_VOID:                    return "VOID";
    case TOKEN_IF:                      return "IF";
    case TOKEN_ELSE:                    return "ELSE";
    case TOKEN_SWITCH:                  return "SWITCH";
    case TOKEN_CASE:                    return "CASE";
    case TOKEN_DEFAULT:                 return "DEFAULT";
    case TOKEN_WHILE:                   return "WHILE";
    case TOKEN_DO:                      return "DO";
    case TOKEN_FOR:                     return "FOR";
    case TOKEN_BREAK:                   return "BREAK";
    case TOKEN_CONTINUE:                return "CONTINUE";
    case TOKEN_RETURN:                  return "RETURN";
    case TOKEN_GOTO:                    return "GOTO";
    case TOKEN_CONST:                   return "CONST";
    case TOKEN_SIZEOF:                  return "SIZEOF";
    case TOKEN_TYPEDEF:                 return "TYPEDEF";
        // Helper Token
    case TOKEN_ERROR:                   return "ERROR";
    case TOKEN_EOF:                     return "EOF";
    case TOKEN_PREPROCESSING:           return "PREPROCESS";
    default:
        break;
    }
}

static void run(const char* source)
{

    initScanner(source);
    int line = -1;

    // ANSI escape sequence : \033[32m  GREEN
    printf("\033[32mOut[%2d]:\n", pyNB);

    for (;;)
    {
        Token token = scanToken();

        if (token.type == TOKEN_ERROR) printf("\033[31m");
           
        if (token.line != line)
        {
            printf("%4d ", token.line);
            line = token.line;
        }
        else 
        {
            printf("   | ");
        }
        printf("%10s -> '%.*s'\n\033[32m", strtoken(token), token.length, token.start);

        if (token.type == TOKEN_EOF) break;
    }
}


// repl: read evaluate print loop
static void repl()
{
    char buf[MAX_BUFFER_SIZE] = { 0 };

    // ANSI escape sequence : \033[31m  RED
    printf("\033[31mIn [%2d]\033[0m: ",pyNB);

    while (fgets(buf, MAX_BUFFER_SIZE - 1, stdin) != NULL)
    {
        run(buf);
        printf("\033[31m\nIn [%2d]\033[0m: ", ++pyNB);
    }
}

char* readFile(const char* path) {
    // 1. 打开文件
    FILE* stream = fopen(path, "rb");
    if (!stream) {
        fprintf(stderr, "Open %s failed\n", path);
        exit(1);
    }

    // 2. 确定文件大小
    fseek(stream, 0, SEEK_END);
    long n = ftell(stream);
    char* content = malloc(n + 1);	// 1 for '\0'

    // 3. 读文件内容，填充content数组
    rewind(stream);	// 回到文件开头
    int bytes = fread(content, 1, n, stream);
    content[bytes] = '\0';

    // 4. 关闭文件
    fclose(stream);
    return content;
}

static void runFile(const char* path)
{
    char* source = readFile(path);

    run(source);

    printf("\033[0m");
    free(source);
}

int main(int argc, const char* argv[])
{
    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: scanner [path]\n");
        exit(1);
    }

    return 0;
}