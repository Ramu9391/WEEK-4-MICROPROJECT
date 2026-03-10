#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX 100

/* -------- STACK FOR CHAR -------- */
char cstack[MAX];
int ctop = -1;

void cpush(char x) { cstack[++ctop] = x; }
char cpop() { return cstack[ctop--]; }
char cpeek() { return cstack[ctop]; }
int cisEmpty() { return ctop == -1; }

/* -------- STACK FOR INT -------- */
int istack[MAX];
int itop = -1;

void ipush(int x) { istack[++itop] = x; }
int ipop() { return istack[itop--]; }

/* -------- BALANCED SYMBOL CHECK -------- */
int isMatching(char o, char c) {
    if (o=='(' && c==')') return 1;
    if (o=='{' && c=='}') return 1;
    if (o=='[' && c==']') return 1;
    return 0;
}

void checkBalanced(char exp[]) {
    ctop = -1;
    for (int i = 0; exp[i]; i++) {
        if (exp[i]=='(' || exp[i]=='{' || exp[i]=='[')
            cpush(exp[i]);
        else if (exp[i]==')' || exp[i]=='}' || exp[i]==']') {
            if (cisEmpty() || !isMatching(cpop(), exp[i])) {
                printf("Unbalanced\n");
                return;
            }
        }
    }
    if (cisEmpty())
        printf("Balanced\n");
    else
        printf("Unbalanced\n");
}

/* -------- INFIX TO POSTFIX -------- */
int priority(char x) {
    if (x=='+' || x=='-') return 1;
    if (x=='*' || x=='/') return 2;
    if (x=='^') return 3;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    ctop = -1;
    int k = 0;

    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];

        if (isalnum(ch))
            postfix[k++] = ch;
        else if (ch == '(')
            cpush(ch);
        else if (ch == ')') {
            while (!cisEmpty() && cpeek() != '(')
                postfix[k++] = cpop();
            cpop();
        } else {
            while (!cisEmpty() && priority(cpeek()) >= priority(ch))
                postfix[k++] = cpop();
            cpush(ch);
        }
    }

    while (!cisEmpty())
        postfix[k++] = cpop();

    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

/* -------- POSTFIX EVALUATION -------- */
int apply(int a, int b, char op) {
    switch (op) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        case '^': return pow(a,b);
    }
    return 0;
}

void evaluatePostfix(char postfix[]) {
    itop = -1;

    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i]))
            ipush(postfix[i]-'0');
        else {
            int b = ipop();
            int a = ipop();
            ipush(apply(a, b, postfix[i]));
        }
    }
    printf("Final Value: %d\n", ipop());
}

/* -------- MAIN MENU -------- */
int main() {
    int ch;
    char exp[MAX], postfix[MAX];

    while (1) {
        printf("\n1.Check Balanced Symbols");
        printf("\n2.Convert Infix to Postfix");
        printf("\n3.Evaluate Postfix");
        printf("\n4.Convert + Evaluate");
        printf("\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter expression: ");
                scanf("%s", exp);
                checkBalanced(exp);
                break;

            case 2:
                printf("Enter infix: ");
                scanf("%s", exp);
                infixToPostfix(exp, postfix);
                break;

            case 3:
                printf("Enter postfix: ");
                scanf("%s", postfix);
                evaluatePostfix(postfix);
                break;

            case 4:
                printf("Enter infix: ");
                scanf("%s", exp);
                infixToPostfix(exp, postfix);
                evaluatePostfix(postfix);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

