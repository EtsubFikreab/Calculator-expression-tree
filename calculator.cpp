/*
 ----------------------------
|Group Members (DRB 2002)	|
|---------------------------|
|                           |
|Bereket Alemayehu - GH7511	|
|                           |
|Etsub Fikreab - OG8653		|
|                           |
-----------------------------
 */

#include "Tree.cpp"
#include "Stack.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <cmath>
const float PI = 3.14159265;
enum symbolType
{
    OPERATOR,
    OPERAND,
    UNKNOWN
}; // defining symbol types in expression
enum preced
{
    PCPAR = 0,
    PADD = 10,
    PMULT = 15,
    PEXP = 20,
    PSIGN = 25, // SIN COS TAN
    POPAR = 30
}; // defining precedance of operators
enum Operators
{
    CPAR = ')',
    ADD = '+',
    SUB = '-',
    MULT = '*',
    DIV = '/',
    EXP = '^',
    OPAR = '(',
    ABS = 'a',
    SQRT = '#',
    SIN = 's',
    COS = 'c',
    TAN = 't'
}; // operators
struct token
{
    double operand;
    char _op;
    int type;
};

int symbolType(char symbol);
int precValue(char symbol);
int cmpPrec(char oprStk, char oprInp);
int associativity(char opr);
int toPostfix(std::string infix, nodeTree<token> *&postfix);
double evaluate(nodeTree<token> *exp);
int mainMenuChoice();
void help();
int main()
{
    int choice;
    do
    {
        choice = mainMenuChoice();
        if (choice == 1)
        {
            std::cout << "Enter a mathematical expression:\n";
            std::string i;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, i);
            nodeTree<token> *p;
            if (toPostfix(i, p) == -1)
            {
                std::cout << "There is a syntactical error in the expression,\n"
                             "please rerun the program after correcting the expression\n"
                             "Press enter to continue... ";
                std::cin.get();
                continue;
            }
            double eval = evaluate(p);
            if (eval != -1)
            {
                cout << "Result: " << eval << endl;
            }
            else
            {
                std::cout << "Sorry, the expression could not be evaluated\n"
                             "Press enter to continue... ";
                std::cin.get();
            }
        }
        else if (choice == 2)
        {
            help();
        }
    } while (choice != 3);
}

int mainMenuChoice()
{
    int choice;
    do
    {
        std::cout << "Main Menu\n"
                     "----------\n"
                     "1. Evaluate Expression\n"
                     "2. Help\n"
                     "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (!std::cin)
        {
            std::cout << "\nInvalid input, press Enter to try again... ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        system("cls");
    } while (!std::cin);
    return choice;
}
void help()
{
    std::cout << "List of operators\n"
                 "------------------\n"
                 "+ addition\n"
                 "- subtraction\n"
                 "* multiplication\n"
                 "/ division\n"
                 "( open parenthesis\n"
                 ") close parenthesis\n"
                 "^ Exponent\n"
                 "s sin\n"
                 "c cos\n"
                 "t tan\n"
                 "a absolute\n"
                 "# square root\n";

    std::cout << "\nPress enter to continue... ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("cls");
}
int symbolType(char symbol)
{
    if (
        symbol == CPAR || symbol == ADD || symbol == SUB || symbol == MULT ||
        symbol == DIV || symbol == EXP || symbol == OPAR || symbol == SIN ||
        symbol == COS || symbol == TAN || symbol == SQRT || symbol == ABS)
        return OPERATOR;
    else if (isdigit(symbol) || symbol == '.')
        return OPERAND;
    return UNKNOWN;
}
int precValue(char symbol)
{
    if (symbol == CPAR)
        return PCPAR;
    else if (symbol == ADD || symbol == SUB)
        return PADD;
    else if (symbol == MULT || symbol == DIV)
        return PMULT;
    else if (symbol == EXP)
        return PEXP;
    else if (symbol == SIN || symbol == COS || symbol == TAN || symbol == SQRT || symbol == ABS)
        return PSIGN;
    return -1;
}
int cmpPrec(char oprStk, char oprInp)
{
    if (precValue(oprStk) < precValue(oprInp))
        return -1;
    else if (precValue(oprStk) == precValue(oprInp))
        return 0;
    return 1;
}
int associativity(char opr)
{
    if (opr == EXP || opr == SIN || opr == COS || opr == TAN || opr == SQRT)
        return 1;
    return 2;
}

int toPostfix(std::string infix, nodeTree<token> *&postfix)
{
    char ch;
    int type, cmp;

    std::stringstream exp(infix);
    Stack<nodeTree<token> *> tree;

    Stack<char> op;
    nodeTree<token> *t, *t1, *t2;
    int i = 1;
    while (exp.peek() != EOF)
    {
        if (isdigit(exp.peek()))
        {
            t = new nodeTree<token>;
            exp >> t->data.operand;
            t->data.type = 1;

            t->left = t->right = NULL;

            tree.push(t);
        }
        else if (symbolType(exp.peek()) == UNKNOWN)
            return -1;
        else
        {
            exp >> ch;
            if (ch == OPAR)
            {
                op.push(ch);
            }
            else if (ch == CPAR)
            {
                while (op.peep() != OPAR)
                {
                    t1 = tree.pop();
                    t2 = tree.pop();

                    t = new nodeTree<token>;
                    t->data._op = op.pop();
                    t->data.type = 0;

                    t->left = t1;
                    t->right = t2;

                    tree.push(t);
                }
                op.pop();
            }
            else
            {
                while (!op.isEmpty() && cmpPrec(op.peep(), ch) >= 0)
                {
                    if (associativity(ch) == 1 && associativity(op.peep()) == 1)
                        break;
                    else
                    {
                        if (cmpPrec('^', op.peep()) == -1)
                        {
                            // unary operators
                            t1 = tree.pop();
                            t = new nodeTree<token>;
                            t->data._op = op.pop();
                            t->data.type = 0;
                            t->left = t1;
                            t->right = NULL;
                            tree.push(t);
                        }
                        else
                        {
                            t1 = tree.pop();
                            t2 = tree.pop();
                            t = new nodeTree<token>;
                            t->data._op = op.pop();
                            t->data.type = 0;

                            t->left = t1;
                            t->right = t2;

                            tree.push(t);
                        }
                    }
                }
                op.push(ch);
            }
        }
    }

    while (!op.isEmpty())
    {
        // unary operators
        if (cmpPrec('^', op.peep()) == -1)
        {
            t1 = tree.pop();
            t = new nodeTree<token>;
            t->data._op = op.pop();
            t->data.type = 0;
            t->left = t1;
            t->right = NULL;
            tree.push(t);
        }
        else
        {
            t1 = tree.pop();
            t2 = tree.pop();
            t = new nodeTree<token>;
            t->data._op = op.pop();
            t->data.type = 0;

            t->left = t1;
            t->right = t2;
            tree.push(t);
        }
    }
    postfix = tree.pop();
    return 0;
}

double evaluate(nodeTree<token> *exp)
{
    if (exp == NULL)
    {
        return 0;
    }
    else
    {
        double t1, t2;
        t1 = evaluate(exp->right);
        t2 = evaluate(exp->left);
        if (exp->data.type == 0)
        {
            switch (exp->data._op)
            {
            case ADD:
                exp->data.operand = t1 + t2;
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case SUB:
                exp->data.operand = t1 - t2;
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case MULT:

                exp->data.operand = t1 * t2;
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case DIV:

                exp->data.operand = t1 / t2;
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case EXP:

                exp->data.operand = pow(t1, t2);
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case ABS:
                exp->data.operand = abs(t2);
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case SQRT:
                exp->data.operand = sqrt(t2);
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case SIN:
                exp->data.operand = sin((t2)*PI / 180);
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case COS:

                exp->data.operand = cos((t2)*PI / 180);
                exp->data.type = 1;
                return exp->data.operand;
                break;
            case TAN:
                exp->data.operand = tan((t2)*PI / 180);
                exp->data.type = 1;
                return exp->data.operand;
                break;

            default:
                return -1;
                break;
            }
        }

        else
            return exp->data.operand;
    }
}