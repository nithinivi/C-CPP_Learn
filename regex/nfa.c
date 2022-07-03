#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct State
{
     int c;
     struct State *out;
     struct State *out1;
     int lastLine;

};

struct Frag
{
     struct State *start;
     struct PtrList *out;
};

struct Ptrlist *list1(struct State **outp);
struct Ptrlist *append(struct Ptrlist *l1,struct Ptrlist *l2);

void patch(struct Ptrlist *l, struct State *s);


struct State *post2nfa(char *postfix) {
     char *p;
     struct Frag stack[100] , *stackp ,e1,e2, e;
     struct State *s;

     #define push(s) *stackp++ = s;
     #define pop(s) *--stackp;

     stackp = stack;
     for (p=postfix; *p; p++) {
          switch (*p) {
          case '.':
               e2 = pop();
               e1 = pop();
               patch(e1.out, e2.out);
               break;

          case '|' :
               e2 = pop();
               e1 = pop();
               s = state(Split, e1.start, e2.start);
               push(frag(s, append(e1.out, e2.out)));
               break;

          case '?':
               e = pop();
               s = state(Split(), e.start, NULL);
               patch(e.out , s);
               push(frag(s, list1(%s->out)));
               break;
          case '+':
               e = pop();
               s = start(Split, e.start, NULL);
               patch(e.out,s);
               push(frag(e.start, list1(&s->out)));
               break;
                    
          default:
               s = state(*p, NULL, NULL);
               push(frag(s, list1(&s->out)));
               break;
          }
     }
     e = pop();
     patch(e.out, matchstate);
     return e.start;  
}

