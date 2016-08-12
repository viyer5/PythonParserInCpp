#include "UBCalculator.h"
#include <sstream>
#include <cstdlib>

using namespace std;

const std::map<char, char> UBCalculator::delimMatch = UBCalculator::createDelimMatch();
const  std::map<char, int> UBCalculator::precedenceMap = UBCalculator::createPrecedenceMap();
const std::string UBCalculator::openDelims = "([{";
const std::string UBCalculator::closeDelims = ")]}";
const string UBCalculator::OPERATORS = "+-*/";

void UBCalculator::print_stack_testing(stack<Token> s ) {
    while(s.empty() == false){
        Token x = s.top();
        cout<<x.value<<endl;
        s.pop();
    }// end while
    /*for(int i=0;i<s.size();i++){
        cout<<s.top().value<<endl;
        s.pop();
    }*/
}
// Evaluate str 
void UBCalculator::setLine(std::string str)
{

   stack<Token> mainStack;
   map<Token, Token> mapStore;
   vector<Token> variables;
   Lexer lexer;
   Token tok;
    bool a = syntax_err(str);
    //cout<<a<<endl;
   bool b = check_well_formed(str);

    if (b== true && a== false)
    {
        lexer.set_input(str);
        vector<Token> my_tok_vec = lexer.tokenize();
//    vector<Token> lavda = multiple_operators(str);
        //cout<<my_tok_vec.size()<<endl;
        vector<Token> jhatu = infix2postfix(my_tok_vec);
        /*for (int i = 0; i < jhatu.size(); i++) {
            cout << jhatu.at(i).value << "  " << flush;
        }*/
      //  cout << endl;
        double q = evaluate_postfix(jhatu);
        cout << q << endl;
        /*for(int i=0; i<my_tok_vec.size();i++){
            mainStack.push(my_tok_vec[i]);
            cout<<mainStack.top().value<<endl;
        }*/
        lexer.restart();

        // cout<<lexer.has_more_token()<<endl;
/*   while(lexer.has_more_token()){
       bool b;
       tok = lexer.next_token();


*//*      if(tok.type == IDENT){

      }// end if*//*
       switch (tok.type) {
           case IDENT:
           {
              if(mainStack.empty()){
                  mainStack.push(tok);
              }
               //else if()

               break;
           }
           case DELIM:   {

               break;
           }
           case OPERATOR:{
               if(mainStack.top().type == IDENT || mainStack.top().type == NUMBER){
                   mainStack.push(tok);
               }
               break;
           }
           case COMMENT:  {

               break;
           }
           case NUMBER:  {
                if(mainStack.top().type == OPERATOR || mainStack.top().type == DELIM){
                    mainStack.push(tok);
                }
               break;
           }
           case STRING:  {

               break;
           }
           case ENDTOK:  {

               break;
           }
           case ERRTOK:  {

               break;
           }
       }// end switch

   }// end while*/
        /*if(mainStack.empty()){
            cout<<"Matolu chutiya hai"<<endl;
        }
        print_stack_testing(mainStack);*/
    }// end if
}// end setLine

bool UBCalculator::check_for_element_vector(vector<Token> x, Token y) {
   bool b;
   for ( int i = 0; i < x.size(); i++){
      Token z = x[i];
      if(y.value == z.value){
         b = true;
      }
   }// end for
    return b;
}// end check_vector

bool UBCalculator::check_well_formed(string line) {
    Lexer lexer; Token tok;  size_t p;
    stack<Token> mystack;
    bool b = true;

    lexer.set_input(line);
    while (lexer.has_more_token()) {
        if ( (tok = lexer.next_token()).type != DELIM ) continue;

        if (openDelims.find(tok.value) != string::npos) {
            // tok is open delim
            mystack.push(tok);
            continue;
        }

        p = closeDelims.find(tok.value); // 0, 1, 2, or string::npos
        if (p != string::npos) {          // tok is a close delim
            if (mystack.empty() ||
                openDelims.find(mystack.top().value) != p) {
                mystack.push(tok); // make sure it's not empty
                break;
            } else {
                mystack.pop();
            }
        }
    } // end while(lexer.has_more_token())

    if (!mystack.empty()) {
        cout << "** ERROR **"<<endl;
        cout<<"Syntax Error: Expression not well formed"<<endl;
        b = false;
        while (!mystack.empty()) mystack.pop();
    } else {
       // cout << "Well-formed!"<<endl;
        b = true;
    }

    return b;
}// end check_well_formed

/*vector<Token> UBCalculator::infix2postfix( vector<Token> &p){

    std::map<char, char> n;
    n[')'] = '(';
    n['}'] = '{';
    n[']'] = '[';

    std::map<char, int> m;
    m['+'] = 0;
    m['-'] = 0;
    m['*'] = 1;
    m['/'] = 1;
    m['('] = -1;
    m['{'] = -1;
    m['['] = -1;
    vector<Token> _nums;
    stack<Token> _ops;
    Token tok;
    char c='a';

    for(int i = 0; i < p.size(); i++){

        tok = p[i];
        cout<<"before"<<endl;
        cout<<tok.type<<endl;
        cout<<tok.value<<endl;
        cout<<"after"<<endl;
        c = tok.value.at(0);
        if(tok.type == token_types_t::NUMBER){
            _nums.push_back(tok);
        }
        else if(tok.type == token_types_t::OPERATOR){
            if(_ops.empty())
            {
                _ops.push(tok);
            }
            else
            {
                int x = m[c];
                cout << "Priority " << x << endl;
                cout << "Top value " << _ops.top().value.at(0);
                int q = m[_ops.top().value.at(0)];
                if(x>q)
                {
                    _ops.push(tok);
                }
                else
                {
                  while(x<=q)
                  {
                      Token t = _ops.top();
                      _nums.push_back(t);
                      _ops.pop();
                      //error
                        cout<<_ops.top().value.at(0)<<endl;
                      q = m[_ops.top().value.at(0)];

                  }// end while
                    _ops.push(tok);
                }
            }// end nested else
        }
        else if(tok.type == token_types_t::DELIM)
        {
            if(_ops.empty())
            {
                _ops.push(tok);
            }
            else
            {
                int x = m[c];
                if (x==-1)
                {
                   _ops.push(tok);
                }
                else
                {
                    char z = n[c];
                    char b = _ops.top().value.at(0);
                    while(b!=z)
                    {
                        Token t = _ops.top();
                        _nums.push_back(t);
                        _ops.pop();
                        b = _ops.top().value.at(0);
                    }
                    // note that ye while loop opening brace ko bhi daal dega vector mein
                    _ops.pop();

                }
            }
        }// end else if
    }// end for
    while(!_ops.empty()){
        Token o = _ops.top();
        _nums.push_back(o);
        _ops.pop();
    }// end while
    return _nums;
}*/


/*vector<Token> UBCalculator::infix2postfix( vector<Token> &p)
{
    std::map<char, char> n;
    n[')'] = '(';
    n['}'] = '{';
    n[']'] = '[';


    std::map<char, int> m;
    m['+'] = 1;
    m['-'] = 1;
    m['*'] = 2;
    m['/'] = 2;
    m['('] = -1;
    m['{'] = -1;
    m['['] = -1;
    m[')'] = -2;
    m[']'] = -2;
    m['}'] = -2;

    Token tok;
    char c;
    vector<Token> _nums;
    stack<Token> _ops;


    for ( int i = 0; i < p.size(); i++)
    {
       tok = p[i];
        c = tok.value.at(0);
        int l = m[c];
        // pushing an opening bracket on stack
        if (l== -1)
        {
            _ops.push(tok);
        }
        if (l==-2)
        {
            // checking for the opening paranthesis
            char j = n[c];
            while (!_ops.empty() && _ops.top().value.at(0) != j) {
                Token q = _ops.top();
                _nums.push_back(q);
                _ops.pop();

            }// end while
            if(!_ops.empty()){
                _ops.pop();
            }
            continue;
        }// end if l==-2
        int weight = getWeight(c);
        if(weight!=10 && weight!=20)
        {
            _nums.push_back(tok);
        }
       *//* if(tok.type == token_types_t::OPERATOR)
        {
            if(_ops.empty())
            {
                _ops.push(tok);
            }*//*
            else
            {
                while(!_ops.empty() && m[_ops.top().value.at(0)] != -1 &&
                        weight <= getWeight(_ops.top().value.at(0)))
                {
                    _nums.push_back(_ops.top());
                    _ops.pop();
                }// end while
              *//*  while(!_ops.empty() && m[_ops.top().value.at(0)] != -1
                        && l <= m[_ops.top().value.at(0)])
                {
                    _nums.push_back(_ops.top());
                    _ops.pop();
                }// end while*//*
                _ops.push(tok);
            }

    }// end for
    while(!_ops.empty())
    {
        _nums.push_back(_ops.top());
        _ops.pop();
    }
    return _nums;
}// end method infix2po*/


int UBCalculator::get_priority(char ch){
   /*
    * function referenced from
    * http://www.csegeek.com/csegeek/view/tutorials/algorithms/stacks_queues/stk_que_part5.php
    */
    switch(ch){
        case '/': return 2;
        case '*': return 2;
        case '+': return 1;
        case '-': return 1;
        default: return 0;

    }
}

vector<Token> UBCalculator::infix2postfix(vector<Token> p) {
    /*
     * the logic of this function was referenced from
     * http://www.csegeek.com/csegeek/view/tutorials/algorithms/stacks_queues/stk_que_part5.php
     * I have teared and rewritten the code by myself.
     */
    stack<Token> _ops;
    vector<Token> _nums;
    int priority_value;
    char ch;
    Token tok;
    for(int i = 0; i < p.size(); i++){
        tok = p[i];
        ch = tok.value.at(0);
        if (openDelims.find(ch)!= -1) {
            _ops.push(tok);
            continue;
        }

        if (closeDelims.find(ch)!= -1) {
            while (!_ops.empty() && openDelims.find(_ops.top().value.at(0))==-1) {
                _nums.push_back(_ops.top());
                _ops.pop();
            }
            if (!_ops.empty()) {
                _ops.pop();
            }
            continue;
        }


        priority_value = get_priority(ch);
        if (priority_value == 0) {
            _nums.push_back(tok);
        }
        else {

            while (!_ops.empty() && openDelims.find(_ops.top().value.at(0))==-1 &&
                    priority_value <= get_priority(_ops.top().value.at(0))) {
                _nums.push_back(_ops.top());
                _ops.pop();
            }// end while
            _ops.push(tok);
        }// end else

    } // end for
    while(!_ops.empty()){
        _nums.push_back(_ops.top());
        _ops.pop();
    }
    return _nums;
}// end infix2postfix

/*
vector<Token> UBCalculator::multiple_operators(string l)
{
    vector<Token> output;
    string ans = "";
    Lexer lexer;
    char w = l.at(l.size()-1);
    for(int i = 0; i < l.size()-1; i++){
        char x = l.at(i);
        char y = l.at(i+1);
        char z;
        if (x == '+' && y == '-'){
           z = '-';
            ans = ans + z;
        }
        else if(x == '+' && y == '+')
        {
            z = '+';
            ans = ans + z;
        }
        else if (x=='-' && y=='-'){
            z = '+';
            ans = ans + z;
        }
        else{
            ans = ans + x ;
        }
    }
    lexer.set_input(ans);
    output = lexer.tokenize();
    return output;

}// end method*/

bool UBCalculator::is_operator(char a)
{
    return OPERATORS.find(a) !=  -1;
}// is_operator

bool UBCalculator::IsNumericDigit(char C)
{
    return (C>= '0' && C<= '9');
}

float UBCalculator::perform_Operation(float x, float y, char z)
{
    float ans;
    switch(z){
        case '+' :
            ans =  x + y;
            break;
        case '*' :
            ans =  x * y;
            break;
        case '-' :
            ans =  y - x;
            break;
        case '/' :
            if (x == 0)
            {
               // throw DBZ_Exception().runtime_error("**  ERROR  ** \n Divide by zero");
                cout<<"** ERROR **"<<endl;
                cout<<"Divide By Zero"<<endl;
            }
            else
            ans =  y / x;
            break;
        default:
        {
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error: Undefined Operator"<<endl;
            return 0;
            break;
        }
    }// end switch
    return ans;
}// end method

float UBCalculator::evaluate_postfix(vector<Token> u)
/*
 * https://gist.github.com/mycodeschool/7702441
 * This code has been refernced from this link.
 * Here again just the algorithm has been refernced, the entire code is mine.
 */
{

    stack<float> num_stack;
    Token t;
    char c;

    for ( int i = 0; i < u.size(); i++)
    {
        t = u.at(i);
        c = t.value.at(0);
        if(t.type== token_types_t::OPERATOR)
        {
            float op2 = num_stack.top();
            num_stack.pop();
            float op1 = num_stack.top();
            num_stack.pop();
            float ans = perform_Operation(op2, op1, c);
            num_stack.push(ans);
        }// end if
        else if (t.type == token_types_t::NUMBER)
        {
            string s = t.value;
            int q = atoi(s.c_str());
            float w = (float)q;
            num_stack.push(w);
        }// end else if
    }// end for
    return num_stack.top();
}// end evaluate opstfix

bool UBCalculator::syntax_err(string s)
{
    bool out = false;
    for(int i = 0; i < s.size()-1; i++){
        char c = s.at(i);
        char d = s.at(i+1);
        if( c == '/' && d == '+'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '/' && d == '-'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '*' && d == '+'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '*' && d == '-'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '*' && d == '/'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '+' && d == '/'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '+' && d == '*'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '-' && d == '*'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
        else if ( c == '-' && d == '/'){
            out = true;
            cout<<"** ERROR **"<<endl;
            cout<<"Syntax Error"<<endl;
        }
      //  else { out = false;}
    }
    return out;
}// end meth

