/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the C- compiler                              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(TokenType token, const char* tokenString) {
    switch (token) {
        /* Reserved words */
        case IF:
        case ELSE:
        case INT:
        case VOID:
        case RETURN:
        case WHILE:
        case DO:
        case FOR:
        case BREAK:
        case CONTINUE:
            fprintf(listing, "reserved word: %s\n", tokenString);
            break;
        
        /* Operators */
        case ASSIGN: fprintf(listing, "=\n"); break;
        case EQ: fprintf(listing, "==\n"); break;
        case LT: fprintf(listing, "<\n"); break;
        case GT: fprintf(listing, ">\n"); break;
        case LE: fprintf(listing, "<=\n"); break;
        case GE: fprintf(listing, ">=\n"); break;
        case NE: fprintf(listing, "!=\n"); break;
        case PLUS: fprintf(listing, "+\n"); break;
        case MINUS: fprintf(listing, "-\n"); break;
        case TIMES: fprintf(listing, "*\n"); break;
        case OVER: fprintf(listing, "/\n"); break;
        case AND: fprintf(listing, "&&\n"); break;
        case OR: fprintf(listing, "||\n"); break;
        case NOT: fprintf(listing, "!\n"); break;
        case PLUSEQ: fprintf(listing, "+=\n"); break;
        case MINUSEQ: fprintf(listing, "-=\n"); break;
        case TIMESEQ: fprintf(listing, "*=\n"); break;
        case DIVEQ: fprintf(listing, "/=\n"); break;
        case PLUSPLUS: fprintf(listing, "++\n"); break;
        case MINUSMINUS: fprintf(listing, "--\n"); break;
        
        /* Brackets/punctuation */
        case LPAREN: fprintf(listing, "(\n"); break;
        case RPAREN: fprintf(listing, ")\n"); break;
        case SEMI: fprintf(listing, ";\n"); break;
        case LBRACKET: fprintf(listing, "[\n"); break;
        case RBRACKET: fprintf(listing, "]\n"); break;
        case COMMA: fprintf(listing, ",\n"); break;
        
        /* Literals/identifiers */
        case NUM:
            fprintf(listing, "NUM, val= %s\n", tokenString);
            break;
        case ID:
            fprintf(listing, "ID, name= %s\n", tokenString);
            break;
        
        /* Special cases */
        case ENDFILE: fprintf(listing, "EOF\n"); break;
        case ERROR:
            fprintf(listing, "ERROR: %s\n", tokenString);
            break;
        default:
            fprintf(listing, "Unknown token: %d\n", token);
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newStmtNode(StmtKind kind) {
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    if (t == NULL) {
        fprintf(listing, "Out of memory error at line %d\n", lineno);
        return NULL;
    }
    for (int i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
    return t;
}

typedef enum { WhileK, ForK, ReturnK } StmtKind;

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = (char *)malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode* tree) {
    static int indentno = 0;
    #define INDENT indentno += 2
    #define UNINDENT indentno -= 2

    INDENT;
    while (tree != NULL) {
        printSpaces();  // Helper to print indentation
        
        if (tree->nodekind == StmtK) {
            switch (tree->kind.stmt) {
                case IfK:
                    fprintf(listing, "If\n");
                    break;
                case WhileK:
                    fprintf(listing, "While\n");
                    break;
                case ForK:
                    fprintf(listing, "For\n");
                    break;
                case ReturnK:
                    fprintf(listing, "Return\n");
                    break;
                case AssignK:  // Add a proper case label for assignment
                    fprintf(listing, "Assign to: %s\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown StmtNode kind\n");
            }
        } else if (tree->nodekind == ExpK) {
            switch (tree->kind.exp) {
                case OpK:
                    fprintf(listing, "Op: ");
                    printToken(tree->attr.op, "\0");
                    break;
                case ConstK:
                    fprintf(listing, "Const: %d\n", tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing, "Id: %s\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode kind\n");
            }
        }
        
        for (int i = 0; i < MAXCHILDREN; i++)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
