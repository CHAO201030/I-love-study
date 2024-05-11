#include"scanner.h"

int pyNB = 1;

typedef struct scanner_t{
    const char* start;
    const char* current;
    int line;
} Scanner;

// 全局变量
Scanner scanner;

void initScanner(const char* source)
{
    // 初始化scanner
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

/***************************************************************************************
 *                                   辅助方法										   *
 ***************************************************************************************/

// If c is alpha return True, else return False
static bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

// If c is digit return True, else return False
static bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

// If pointer variable Scanner.current point to '\0\ return True, else return False 
static bool isAtEnd()
{
    return *scanner.current == '\0';
}

// Scanner.current point to next position and return it
static char advance()
{
    return *scanner.current++;
}

// Return the object pointed by Scanner.current
static char peek()
{
    return *scanner.current;
}

// Return the next object pointed by Scanner.current
static char peekNext()
{
    if (isAtEnd()) return '\0';
    return *(scanner.current + 1);
}

// If next == expect return true and cur mv to next pos
static bool match(char expected)
{
    if (isAtEnd()) return false;
    if (peek() != expected) return false;
    scanner.current++;
    return true;
}

// 传入TokenType, 创建对应类型的Token，并返回。
static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;

    return token;
}

// 遇到不能解析的情况时，我们创建一个ERROR Token.
// 比如：遇到'$' 等符号时，或字符串，字符没有对应的右引号时。
static Token errorToken(const char* message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;

    return token;
}

static void skipWhitespace()
{
    // 跳过空白字符: ' ', '\r', '\t', '\n'和注释
    // 注释以'//'开头, 一直到行尾
    // 注意更新scanner.line！
    while (*scanner.current)
    {
        switch (*scanner.current)
        {
        case ' ':case '\r':case '\t':advance(); break;
        case '\n':advance(); scanner.line++; break;
        case '/':
        {
            if (peekNext() == '/')
            {
                while (peek() != '\n')
                {
                    advance();
                }
                break;
            }
        }
        default:
            return;
        }
    }
}

// 参数说明：
// start: 从哪个索引位置开始比较
// length: 要比较字符的长度
// rest: 要比较的内容
// type: 如果完全匹配，则说明是type类型的关键字

static TokenType checkKeyword(int start, int length, const char* rest, TokenType type)
{
    int len = (int)(scanner.current - scanner.start); // TOKEN的长度
    // start + length: 关键字的长度
    if (start + length == len && memcmp(scanner.start + start, rest, length) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

// 判断当前Token到底是标识符还是关键字
static TokenType identifierType()
{
    // 确定identifier类型主要有两种方式：
    // 1. 将所有的关键字放入哈希表中，然后查表确认
    // 2. 将所有的关键字放入Trie树中，然后查表确认
    // Trie树的方式不管是空间上还是时间上都优于哈希表的方式
    char c = scanner.start[0];
    TokenType helper;
    // 用switch语句实现Trie树
    switch (c)
    {
    case 'b':return checkKeyword(1, 4, "reak", TOKEN_BREAK);
    case 'c':
    {
        // case
        helper = checkKeyword(1, 3, "ase", TOKEN_CASE);
        if (helper == TOKEN_CASE)return helper;
        
        // char
        helper = checkKeyword(1, 3, "har", TOKEN_CHAR);
        if (helper == TOKEN_CHAR)return helper;
        
        // continue
        helper = checkKeyword(1, 7, "ontinue", TOKEN_CONTINUE);
        if (helper == TOKEN_CONTINUE)return helper;

        // const or identifier
        helper = checkKeyword(1, 4, "onst", TOKEN_CONST);
        
        return helper;    
    }
    case 'd':
    {
        // default
        helper = checkKeyword(1, 6, "efault", TOKEN_DEFAULT);
        if (helper == TOKEN_DEFAULT)return helper;

        // double
        helper = checkKeyword(1, 5, "ouble", TOKEN_DOUBLE);

        return helper;
    }
    case 'e':
    {
        // enum
        helper = checkKeyword(1, 3, "num", TOKEN_ENUM);
        if (helper == TOKEN_ENUM)return helper;

        // else
        helper = checkKeyword(1, 3, "lse", TOKEN_ELSE);

        return helper;
    }
    case 'f':
    {
        // float
        helper = checkKeyword(1, 4, "loat", TOKEN_FLOAT);
        if (helper == TOKEN_FLOAT)return helper;

        // for
        helper = checkKeyword(1, 2, "or", TOKEN_FOR);

        return helper;
    }
    case 'g':return checkKeyword(1, 3, "oto", TOKEN_GOTO);
    case 'i':
    {
        // if
        helper = checkKeyword(1, 1, "f", TOKEN_IF);
        if (helper == TOKEN_IF)return helper;

        // int
        helper = checkKeyword(1, 2, "nt", TOKEN_INT);

        return helper;
    }
    case 'l':return checkKeyword(1, 3, "ong", TOKEN_LONG);
    case 'r':return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's':
    {
        // short
        helper = checkKeyword(1, 4, "hort", TOKEN_SHORT);
        if (helper == TOKEN_SHORT)return helper;

        // signed
        helper = checkKeyword(1, 5, "igned", TOKEN_SIGNED);
        if (helper == TOKEN_SIGNED)return helper;

        // sizeof
        helper = checkKeyword(1, 5, "izeof", TOKEN_SIZEOF);
        if (helper == TOKEN_SIZEOF)return helper;

        // struct
        helper = checkKeyword(1, 5, "truct", TOKEN_STRUCT);
        if (helper == TOKEN_STRUCT)return helper;

        // switch
        helper = checkKeyword(1, 5, "witch", TOKEN_SWITCH);
        
        return helper;
    }
    case 't':return checkKeyword(1, 6, "ypedef", TOKEN_TYPEDEF);
    case 'u':
    {
        // unsigned
        helper = checkKeyword(1, 7, "nsigned", TOKEN_UNSIGNED);
        if (helper == TOKEN_UNSIGNED)return helper;

        // union
        helper = checkKeyword(1, 4, "nion", TOKEN_UNION);

        return helper;
    }
    case 'v':return checkKeyword(1, 3, "oid", TOKEN_VOID);
    case 'w':return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    // identifier
    return TOKEN_IDENTIFIER;
}

static Token identifier()
{
    // IDENTIFIER包含: 字母，数字和下划线
    while (isAlpha(peek()) || isDigit(peek()))
    {
        advance();
    }
    // 这样的Token可能是标识符, 也可能是关键字, identifierType()是用来确定Token类型的
    return makeToken(identifierType());
}

static Token number()
{
    // 简单起见，我们将NUMBER的规则定义如下:
    // 1. NUMBER可以包含数字和最多一个'.'号
    // 2. '.'号前面要有数字
    // 3. '.'号后面也要有数字
    // 这些都是合法的NUMBER: 123, 3.14
    // 这些都是不合法的NUMBER: 123., .14
    while (isDigit(peek()))
    {
        advance();
    }// peek 为 . 或者结尾

    if (peek() == '.')
    {
        advance();
        
        while (peek() && peek() != '\n')
        {
            // '.'的后面不是数字 返回errorToken
            if (!isDigit(peek()))
            {
                /*
                    BUG
                    当传入 3..时多一个'\n'字符 导致打印结果多换行一次
                */
                return errorToken(scanner.start);
            }
            advance();
        }
    }
 
    return makeToken(TOKEN_NUMBER);
}

static Token string()
{
    // 字符串以"开头，以"结尾，而且不能跨行
}

static Token character()
{
    // 字符'开头，以'结尾，而且不能跨行   
}

/***************************************************************************************
 *                                   	分词										   *
 ***************************************************************************************/

Token scanToken()
{
    // 跳过前置空白字符和注释
    skipWhitespace();
    // 记录下一个Token的起始位置
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();
    if (isAlpha(c)) return identifier();
    if (isDigit(c)) return number();

    switch (c)
    {
        // single-character tokens
    case '(':return makeToken(TOKEN_LEFT_PAREN);
    case ')':return makeToken(TOKEN_RIGHT_PAREN);
    case '[':return makeToken(TOKEN_LEFT_BRACKET);
    case ']':return makeToken(TOKEN_RIGHT_BRACKET);
    case '{':return makeToken(TOKEN_LEFT_BRACE);
    case '}':return makeToken(TOKEN_RIGHT_BRACE);
    case ',':return makeToken(TOKEN_COMMA);
    case '.':return makeToken(TOKEN_DOT);
    case ';':return makeToken(TOKEN_SEMICOLON);
    case '~':return makeToken(TOKEN_TILDE);

        // one or two characters tokens
    case '+':
    {
        if (match('+')) return makeToken(TOKEN_PLUS_PLUS);
        else if (match('=')) return makeToken(TOKEN_PLUS_EQUAL);
        else return makeToken(TOKEN_PLUS);
    }
    case '-':
    {
        if (match('-'))return makeToken(TOKEN_MINUS_MINUS);
        else if (match('='))return makeToken(TOKEN_MINUS_EQUAL);
        else if (match('>'))return makeToken(TOKEN_MINUS_GREATER);
        else return makeToken(TOKEN_MINUS);
    }
    case '*':
    {
        if (match('='))return makeToken(TOKEN_STAR_EQUAL);
        else return makeToken(TOKEN_STAR);
    }
    case '/':
    {
        if (match('='))return makeToken(TOKEN_SLASH_EQUAL);
        else return makeToken(TOKEN_SLASH);
    }
    case '%':
    {
        if (match('='))return makeToken(TOKEN_PERCENT);
        else return makeToken(TOKEN_PERCENT_EQUAL);
    }
    case '&':
    {
        if (match('='))return makeToken(TOKEN_AMPER_EQUAL);
        else if (match('&'))return makeToken(TOKEN_AMPER_EQUAL);
        else return makeToken(TOKEN_AMPER_AMPER);
    }
    case '|':
    {
        if (match('='))return makeToken(TOKEN_PIPE_EQUAL);
        else if (match('|'))return makeToken(TOKEN_PIPE_PIPE);
        else return makeToken(TOKEN_PIPE);
    }
    case '^':
    {
        if (match('='))return makeToken(TOKEN_HAT_EQUAL);
        else return makeToken(TOKEN_HAT);
    }
    case '=':
    {
        if (match('='))return makeToken(TOKEN_EQUAL_EQUAL);
        else return makeToken(TOKEN_EQUAL);
    }
    case '!':
    {
        if (match('='))return makeToken(TOKEN_BANG_EQUAL);
        else return makeToken(TOKEN_BANG);
    }
    case '<':
    {
        if (match('='))return makeToken(TOKEN_LESS_EQUAL);
        else if (match('<'))return makeToken(TOKEN_LESS_LESS);
        else return makeToken(TOKEN_LESS);
    }
    case '>':
    {
        if (match('='))return makeToken(TOKEN_GREATER_EQUAL);
        else if (match('>'))return makeToken(TOKEN_GREAER_GREATER);
        else return makeToken(TOKEN_GREATER);
    }
        // various-character tokens
    case '"': return string();
    case '\'': return character();
    }

    return errorToken("Unexpected character.");
}