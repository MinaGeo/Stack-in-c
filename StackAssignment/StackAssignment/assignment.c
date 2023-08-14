#include <stdio.h>

#define STACK_SIZE 25

typedef unsigned char uint8_t;
typedef signed int int8_t;

typedef struct stack {
    uint8_t elements[STACK_SIZE];
    int8_t top;
} ST_STACK_T;

void createEmptyStack(ST_STACK_T* stack)
{
    int i;
    for (i = 0; i < STACK_SIZE; i++) {
        stack->elements[i] = 0;
    }
    stack->top = -1;
}

int8_t push(ST_STACK_T* stack, uint8_t data)
{
    if (stack->top == STACK_SIZE - 1) {
        return -1;
    }
    else {
        stack->top++;
        stack->elements[stack->top] = data;
        return 0;
    }
}

int8_t pop(ST_STACK_T* stack, uint8_t* data)
{
    if (isEmpty(stack) == -2) {
        return -2;
    }
    else {
        *data = stack->elements[stack->top];
        stack->elements[stack->top] = 0; // Set the value of the popped element to 0
        stack->top--;
        return 0;
    }
}

int8_t printStack(ST_STACK_T* stack)
{
    if (isEmpty(stack) == -2) {
        return -2;
    }
    else if (isFull(stack) == -1) {
        printf("The stack is [");
        for (int8_t i = stack->top; i >= 0; i--) {
            printf("%c", stack->elements[i]);
        }
        printf("]\n");
        return -1;
    }
    else {
        printf("The stack is [");
        for (int8_t i = stack->top; i >= 0; i--) {
            printf("%c", stack->elements[i]);
        }
        printf("]\n");
        return 0;
    }
}

int8_t getStackTop(ST_STACK_T* stack, uint8_t* topData)
{
    if (isEmpty(stack) == -2) {
        return -2;
    }
    else {
        *topData = stack->elements[stack->top];
        return 0;
    }
}

int8_t isFull(ST_STACK_T* stack)
{
    if (stack->top == STACK_SIZE - 1) {
        return -1;
    }
    else {
        return 0;
    }
}

int8_t isEmpty(ST_STACK_T* stack)
{
    if (stack->top == -1) {
        return -2;
    }
    else {
        return 0;
    }
}

int8_t isBalancedParanthethes(uint8_t* expression)
{
    ST_STACK_T stack;
    createEmptyStack(&stack);
    uint8_t currentIter;
    for (int8_t i = 0; expression[i] != '\0'; i++) {
        currentIter = expression[i];
        if (currentIter == '{' || currentIter == '(') {
            push(&stack, currentIter);
        }
        else if (currentIter == '}' || currentIter == ')') {
            int8_t result;
            uint8_t characterAtTop;
            result = getStackTop(&stack, &characterAtTop);
            if (result == -2) {
                return -1; // Closing parenthesis without an opening one
            }
            if ((currentIter == '}' && characterAtTop == '{') || (currentIter == ')' && characterAtTop == '(')) {
                int8_t data;
                pop(&stack, &data);
            }
            else {
                return -1; // Mismatched parentheses
            }
        }
    }
    if (isEmpty(&stack) == -2) {
        return -2; // Balanced parentheses
    }
    else {
        return 0;
    }
}

int main()
{
    uint8_t expression[STACK_SIZE];
    uint8_t input;
    int8_t result;
    uint8_t  characterAtTop, data;
    int8_t n, counter, printVal, element, topVal;
    ST_STACK_T stack;
    createEmptyStack(&stack);
    while (1) {
        printf("Enter operation (p=push, m=pop, k=print, q=quit, t=stack's top, b=check Balanced parantheses): ");
        scanf_s("%c", &input);
        getchar(); // consume any remaining characters in the input stream

        switch (input) {
        case 'p':
  
            printf("Enter number of elements to push: ");
            scanf_s("%d", &n);
            getchar(); // consume newline character

            for (int8_t i = 0; i < n; i++) {
                if (isFull(&stack) == -1)
                {
                    printf("Can't add more elements, Stack is full\n");
                }
                else {
                    printf("Enter element %d: ", i + 1);
                    scanf_s("%c", &element);
                    getchar(); // consume newline character

                    push(&stack, element);
                }
               
            }
          
            break;
        case 'm':
            element = pop(&stack, &data);
            if (element == -2) {
                printf("Stack is empty, can't pop\n");
            }
            else if (element == 0) {
                printf("Popped element: %c\n",data);
            }
            break;
        case 'k':
            printVal = printStack(&stack);
            if (printVal == -1)
            {
                printf("Stack is full\n");

            }
            else if (printVal == -2)
            {
                printf("Stack is empty\n");
            }
            else
            {
                printf("Succesfully printing stack\n");
            }
            break;
        case 't':
            topVal = getStackTop(&stack, &characterAtTop);
            if (topVal == -2)
            {
                printf("Stack is empty, stack top is 0 (initial value)\n");
            }
            else {
                printf("The stack top is: %C\n", characterAtTop);
            }
            break;
        case 'b':
            printf("Enter expression: ");
            scanf_s("%24s", expression, sizeof(expression));
            getchar(); // consume newline character

            result = isBalancedParanthethes(expression);
            if (result == -2) {
                printf("Parentheses are balanced\n");
            }
            else if (result == -1) {
                printf("Parentheses are not balanced\n");
            }
            else {
                printf("No parentheses found\n");
            }
            break;
        case 'q':
            exit(0);
        default:
            printf("Error: Invalid input\n");
            break;
        }

    }
    return 0;
}