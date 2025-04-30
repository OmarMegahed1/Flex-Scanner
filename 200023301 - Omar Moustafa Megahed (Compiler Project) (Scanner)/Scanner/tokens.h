#ifndef _TOKENS_H_
#define _TOKENS_H_

/* C- Token Types */
typedef enum {
    /* Book-keeping tokens */
    ENDFILE, ERROR,
    
    /* Reserved words */
    IF, ELSE, INT, VOID, RETURN, WHILE, DO, FOR, BREAK, CONTINUE,
    
    /* Multicharacter tokens */
    ID, NUM,
    
    /* Special symbols */
    ASSIGN, EQ, LT, GT, LE, GE, NE,
    PLUS, MINUS, TIMES, OVER,
    LPAREN, RPAREN, SEMI, LBRACKET, RBRACKET, COMMA,
    AND, OR, NOT,
    PLUSEQ, MINUSEQ, TIMESEQ, DIVEQ,
    PLUSPLUS, MINUSMINUS
} TokenType;

#endif /* _TOKENS_H_ */