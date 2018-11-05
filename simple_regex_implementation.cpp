#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <set>
#include <map>

using namespace std;

#define MAX_STR_LEN 1024
#define START_STATE_CHAR 0
#define SPLIT_CHAR 256
#define FINAL_STATE_CHAR 257

char regex[MAX_STR_LEN], postfix_regex[MAX_STR_LEN + MAX_STR_LEN];

map<char, int> operator_priority_map = {
  {')', 5},  // lowest of all
  {'|' , 10},
  {'.' , 20},
  {'*' , 30},
  {'+' , 30},
  {'?' , 30},
  {'(', 40},  // highest of all
};

bool is_higher_pri(char a, char b) {
  auto it_a = operator_priority_map.find(a);
  auto it_b = operator_priority_map.find(b);

  if (it_a == operator_priority_map.end() || it_b == operator_priority_map.end()) {
    fprintf(stderr, "Found operator(s) with unknown priority: %d(%c), %d(%c)", a, a, b, b);
    throw "Found operator(s) with unknown priority";
  }
  return (it_a->second > it_b->second);
}

bool is_literal(char a) {
  return (operator_priority_map.count(a) == 0);
}

bool is_binary_operator(char a) {
  return (a == '|');
}

bool is_left_unary_operator(char a) {
  return (a == '(');
}

void insert_concatenation_operators_regex() {
  char temp[MAX_STR_LEN];
  strncpy(temp, regex, MAX_STR_LEN);
  int j = 1;
  for (int i = 1; temp[i]; i++) {
    if (is_literal(temp[i]) || is_left_unary_operator(temp[i])) {
      if (!(is_binary_operator(temp[i-1]) || is_left_unary_operator(temp[i-1]))) {
        regex[j++] = '.';
      }
    }
    regex[j++] = temp[i];
  }
  regex[j] = '\0';
  fprintf(stderr, "Concatenated Regex: %s\n", regex);
}

void generate_postfix_for_infix_regex() {
  insert_concatenation_operators_regex();
  stack<char> operator_stack;
  int j = 0;
  for (int i = 0; regex[i]; i++) {
    char c = regex[i];
      switch(c) {
        case '.':
        case '*':
        case '+':
        case '?':
        case '|':
        case '(':
        case ')':
          {
            while (!operator_stack.empty()) {
              auto op2 = operator_stack.top();
              if (op2 == '(' || is_higher_pri(c, op2)) {
                break;
              } else {
                postfix_regex[j++] = op2; operator_stack.pop();
              }
            }
            if (c == ')') {
              if (operator_stack.top() != '(') {
                throw "Invalid Infix expression: no matching '(' before ')'";
              }
              operator_stack.pop();
            } else {
              operator_stack.push(c);
            }
          }
          break;
        default:
          postfix_regex[j++] = c;
          break;
     }
  }
  while(!operator_stack.empty()) {
    postfix_regex[j++] = operator_stack.top();
    operator_stack.pop();
  }
  postfix_regex[j] = '\0';
  fprintf(stderr, "Postfix Regex: %s\n", postfix_regex);
}

struct nfa_state {
  int char_in;
  nfa_state *out;
  nfa_state *out1;
  nfa_state(int p_char_in, nfa_state *p_out = NULL, nfa_state *p_out1 = NULL) {
    char_in = p_char_in;
    out = p_out;
    out1 = p_out1;
  }
};

typedef vector<nfa_state **> state_ref_vector;

struct nfa_fragment {
  nfa_state *start_state;
  state_ref_vector *out_ref_list;
  nfa_fragment(nfa_state *p_start_state, state_ref_vector *p_out_ref_list) {
    start_state = p_start_state;
    out_ref_list = p_out_ref_list;
  }
};

vector<nfa_state *> all_nfa_states;
vector<nfa_fragment *> all_nfa_fragments;

nfa_state *new_nfa_state(int p_char_in, nfa_state *p_out = NULL, nfa_state *p_out1 = NULL) {
  auto x = new nfa_state(p_char_in, p_out, p_out1);
  all_nfa_states.push_back(x);
  return x;
}

nfa_fragment *new_nfa_fragment(nfa_state *p_start_state, state_ref_vector *p_out_ref_list) {
  auto x = new nfa_fragment(p_start_state, p_out_ref_list);
  all_nfa_fragments.push_back(x);
  return x;
}

nfa_fragment *new_nfa_fragment(nfa_state *p_start_state, nfa_state **p_out_state_ref) {
  auto p_out_ref_list = new state_ref_vector();
  p_out_ref_list->push_back(p_out_state_ref);
  auto x = new nfa_fragment(p_start_state, p_out_ref_list);
  all_nfa_fragments.push_back(x);
  return x;
}

void frag_connect(state_ref_vector *out1, nfa_state *in2) {
  for(int i = 0; i < out1->size(); ++i) {
    *((*out1)[i]) = in2;
  }
}

nfa_state *compile_regex() {
  generate_postfix_for_infix_regex();
  stack<nfa_fragment *> nfa_stack;
  for (char *p = postfix_regex; *p; p++) {
    switch(*p) {
      case '*':
        {
          auto frag = nfa_stack.top(); nfa_stack.pop();
          auto state = new_nfa_state(SPLIT_CHAR, frag->start_state);
          frag_connect(frag->out_ref_list, state);
          auto frag1 = new_nfa_fragment(state, &(state->out1));
          nfa_stack.push(frag1);
        }
        break;
      case '+':
        {
          auto frag = nfa_stack.top(); nfa_stack.pop();
          auto state = new_nfa_state(SPLIT_CHAR, frag->start_state);
          frag_connect(frag->out_ref_list, state);
          auto frag1 = new_nfa_fragment(frag->start_state, &(state->out1));
          nfa_stack.push(frag1);
        }
        break;
      case '?':
        {
          auto frag = nfa_stack.top(); nfa_stack.pop();
          auto state = new_nfa_state(SPLIT_CHAR, frag->start_state);
          auto v = new state_ref_vector(*frag->out_ref_list);
          v->push_back(&(state->out1));
          auto frag1 = new_nfa_fragment(state, v);
          nfa_stack.push(frag1);
        }
        break;
      case '|':
        {
          auto frag2 = nfa_stack.top(); nfa_stack.pop();
          auto frag1 = nfa_stack.top(); nfa_stack.pop();
          auto state = new_nfa_state(SPLIT_CHAR, frag1->start_state, frag2->start_state);
          auto v = new state_ref_vector(*frag1->out_ref_list);
          v->insert(v->end(), frag2->out_ref_list->begin(), frag2->out_ref_list->end());
          auto frag3 = new_nfa_fragment(state, v);
          nfa_stack.push(frag3);
        }
        break;
      case '.':
        {
          auto frag2 = nfa_stack.top(); nfa_stack.pop();
          auto frag1 = nfa_stack.top(); nfa_stack.pop();
          frag_connect(frag1->out_ref_list, frag2->start_state);
          auto frag3 =  new_nfa_fragment(frag1->start_state, frag2->out_ref_list);
          nfa_stack.push(frag3);
        }
        break;
      default:  // literal character
        {
          auto state = new_nfa_state(*p);
          auto frag = new_nfa_fragment(state, &(state->out));
          nfa_stack.push(frag);
        }
        break;
    }
  }
  auto nfa = nfa_stack.top(); nfa_stack.pop();
  auto first_state = new_nfa_state(START_STATE_CHAR, nfa->start_state);
  auto final_state = new_nfa_state(FINAL_STATE_CHAR);
  frag_connect(nfa->out_ref_list, final_state);
  return first_state;
}

void print_nfa() {
  fprintf(stderr, "PRINT NFA\n");
  for (const auto &state: all_nfa_states) {
    auto x = state->char_in;
    char type[MAX_STR_LEN] = "LITERAL";
    if (x == SPLIT_CHAR) {
      strncpy(type, "SPLIT", MAX_STR_LEN);
    } else if (x == FINAL_STATE_CHAR) {
      strncpy(type, "FINAL_STATE", MAX_STR_LEN);
    } else if (x == START_STATE_CHAR) {
      strncpy(type, "START_STATE", MAX_STR_LEN);
    }
    fprintf(stderr, "state(%p): %c(%d) type:%s, out:%p, out1:%p\n",
      state, x, x, type, state->out, state->out1);
  }
  fprintf(stderr, "\n");
}

void add_state_to_state_list(nfa_state *state, set<nfa_state *>& state_list) {
  if (state == NULL) {
    return;
  }
  auto insert_info = state_list.insert(state);
  if (insert_info.second == false) {
    // element existed in state_list already
    return;
  }
  // fprintf(stderr, "add_state_to_state_list::%d(%c) %p\n", state->char_in, state->char_in, state);
  if (state->char_in == FINAL_STATE_CHAR) {
    return;  // final state reached
  }
  if (state->out && (state->out->char_in == SPLIT_CHAR || state->out->char_in == FINAL_STATE_CHAR)) {
    add_state_to_state_list(state->out, state_list);
  }
  if (state->out1 && (state->out1->char_in == SPLIT_CHAR || state->out1->char_in == FINAL_STATE_CHAR)) {
    add_state_to_state_list(state->out1, state_list);
  }
}

bool final_state_reached(const set<nfa_state *>& state_list) {
  for (const auto &state: state_list) {
    if (state->char_in == FINAL_STATE_CHAR) {
      return true;
    }
  }
  return false;
}

bool match(nfa_state *nfa_first_state, char *str) {
  set<nfa_state *> current_state_list, next_state_list;
  add_state_to_state_list(nfa_first_state, current_state_list);
  for(int c = 0; str[c] && !current_state_list.empty(); c++) {
    // fprintf(stderr, "process char: %c, current_state_list_size(%lu)\n", str[c], current_state_list.size());
    next_state_list.clear();
    for (auto &current_state: current_state_list) {
      if (current_state->out && current_state->out->char_in == str[c]) {
        add_state_to_state_list(current_state->out, next_state_list);
      }
      if (current_state->out1 && current_state->out1->char_in == str[c]) {
        add_state_to_state_list(current_state->out1, next_state_list);
      }
    }
    current_state_list = next_state_list;
  }
  return final_state_reached(current_state_list);
}

int main() {
  char str[MAX_STR_LEN];
  fgets(regex, MAX_STR_LEN, stdin);
  regex[strlen(regex) - 1] = '\0';
  auto regex_nfa_first_state = compile_regex();
  print_nfa();
  while(fgets(str, MAX_STR_LEN, stdin)) {
    str[strlen(str) - 1] = '\0';
    printf("%s\n", match(regex_nfa_first_state, str) ? "True" : "False");
  }
  return 0;
}
