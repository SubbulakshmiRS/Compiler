#include <vector>
#include <string>
using namespace std;


class AST_node ;                                
class AST_prog ;                                        
class AST_stmts ;                                         
class AST_stmt;
class AST_semicolon;
class AST_keyword;
class AST_function_decl;
class AST_variable_decl;
class AST_assignStmt;
class AST_assignStmt_old;
class AST_assignStmt_new;
class AST_functionCall;
class AST_functionCall_noargs;
class AST_functionCall_args;
class AST_ifStmt;
class AST_ifWEStmt;
class AST_ifElseStmt;
class AST_whileStmt;
class AST_forStmt;
class AST_returnStmt;
class AST_inputStmt;
class AST_outputStmt;
class AST_expr;
class AST_expr_unary;
class AST_expr_binary;
class AST_expr_ternary;
class AST_paramD_list;
class AST_param_list;
class AST_paramD;
class AST_param ;
class AST_int;
class AST_bool;
class AST_float;
class AST_variable;
class AST_variable_0D;
class AST_variable_1D_i;
class AST_variable_1D_v;
class AST_variable_2D_ii;
class AST_variable_2D_iv;
class AST_variable_2D_vi;
class AST_variable_2D_vv;

union _NODE_
{
	char name[20];
    int number;
    float fnumber;
    int bvalue;
    char boperator[3];
    char uoperator[3];
    char roperator[3];
    char aoperator[3];
    char aboperator[3];
    char dtype[20];
    AST_node* node;
    AST_prog* prog;
    AST_stmts* stmts;
    AST_stmt* stmt;
    AST_semicolon* semicolon;
    AST_keyword* keyword;
    AST_function_decl* function_decl;
    AST_variable_decl* variable_decl;
    AST_assignStmt* assignStmt;
    AST_assignStmt_old* assignStmt_old;
    AST_assignStmt_new* assignStmt_new;
    AST_functionCall* functionCall;
    AST_functionCall_noargs* functionCall_noargs;
    AST_functionCall_args* functionCall_args;
    AST_ifStmt* ifStmt;
    AST_ifWEStmt* ifWEStmt;
    AST_ifElseStmt* ifElseStmt;
    AST_whileStmt* whileStmt;
    AST_forStmt* forStmt;
    AST_returnStmt* returnStmt;
    AST_inputStmt* inputStmt;
    AST_outputStmt* outputStmt;
    AST_expr* expr;
    AST_expr_unary* expr_unary;
    AST_expr_binary* expr_binary;
    AST_expr_ternary* expr_ternary;
    AST_paramD_list* paramD_list;
    AST_param_list* param_list;
    AST_paramD* paramD;
    AST_param * param ;
    AST_int* intVal;
    AST_bool* boolVal;
    AST_float* floatVal;
    AST_variable* variable;
    AST_variable_0D* variable_0D;
    AST_variable_1D_i* variable_1D_i;
    AST_variable_1D_v* variable_1D_v;
    AST_variable_2D_ii* variable_2D_ii;
    AST_variable_2D_iv* variable_2D_is;
    AST_variable_2D_vi* variable_2D_vi;
    AST_variable_2D_vv* variable_2D_vv;

};

typedef union _NODE_ YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class AST_node
{

};

class AST_prog : public AST_node
{

};


class AST_stmts : public AST_prog
{
private:
    vector<AST_stmt*> stmt_list;
public:
    void push_back(AST_stmt * stmt);
};

class AST_stmt : public AST_node
{

};

class AST_semicolon : public AST_stmt{

};

class AST_keyword : public AST_stmt
{
private:
    string keyword_type; 
public:
    AST_keyword(string keyword_type);

};

class AST_function_decl: public AST_stmt
{
private:
    string dtype;
    string functionName;
    AST_paramD_list* paramD_list;
    AST_stmts* stmts;  

public:
    AST_function_decl(string dtype, string functionName, AST_paramD_list* paramD_list, AST_stmts* stmts);
};

class AST_variable_decl: public AST_stmt
{
private:
    string dtype;
    AST_variable* variable;  

public:
    AST_variable_decl(string dtype, AST_variable* variable);
};

class AST_assignStmt : public AST_stmt
{

};

class AST_assignStmt_old: public AST_assignStmt
{
private:
    AST_variable* varName;
    AST_expr* expr;
public:
    AST_assignStmt_old(AST_variable* varName, AST_expr* expr);

};

class AST_assignStmt_new: public AST_assignStmt
{
private:
    string dtype;
    AST_variable* varName;
    AST_expr* expr;
public:
    AST_assignStmt_new(string dtype, AST_variable* varName, AST_expr* expr);

};

class AST_ifStmt : public AST_stmt
{

};

class AST_ifWEStmt : public AST_ifStmt
{
private:
    AST_expr* expr;
    AST_stmts* ifStmts;
public:
    AST_ifWEStmt(AST_expr* expr, AST_stmts* ifStmts);
};

class AST_ifElseStmt : public AST_ifStmt
{
private:
    AST_expr* expr;
    AST_stmts* ifStmts;
    AST_stmts* ifEStmts;
public:
    AST_ifElseStmt(AST_expr * expr, AST_stmts* ifStmts, AST_stmts* ifEStmts);
};

class AST_whileStmt : public AST_stmt
{
private:
    AST_expr* expr;
    AST_stmts* whileStmts;
public:
    AST_whileStmt(AST_expr* expr, AST_stmts* whileStmts);
};

class AST_forStmt : public AST_stmt
{
private:
    AST_assignStmt* initialize;
    AST_expr* expr;
    AST_assignStmt* increment;
    AST_stmts* forStmts;
public:
    AST_forStmt(AST_assignStmt* initialize, AST_expr* expr, AST_assignStmt* increment, AST_stmts* forStmts);
};

class AST_returnStmt : public AST_stmt
{
private:
    AST_expr* expr;
public:
    AST_returnStmt(AST_expr* expr);
};

class AST_inputStmt : public AST_stmt
{
private:
    AST_variable* var;
public:
    AST_inputStmt(AST_variable* var);
};

class AST_outputStmt : public AST_stmt
{
private:
    AST_variable* var;
public:
    AST_outputStmt(AST_variable* var);
};

class AST_expr: public AST_node
{

};

class AST_expr_unary: public AST_expr
{
private:
    string opType;
    AST_expr* expr;
public:
    AST_expr_unary(string opType, AST_expr* expr);
};

class AST_expr_binary: public AST_expr
{
private:
    string opType;
    AST_expr* expr1, *expr2;
public:
    AST_expr_binary(AST_expr* expr1, string opType, AST_expr* expr2);
};

class AST_expr_ternary: public AST_expr
{
private:
    AST_expr* expr1, *expr2, *expr3;
public:
    AST_expr_ternary(AST_expr* expr1, AST_expr* expr2, AST_expr* expr3);
};

class AST_functionCall : public AST_expr
{

};

class AST_functionCall_noargs : public AST_functionCall
{
private:
    string functionName;
public:
    AST_functionCall_noargs(string functionName);
};

class AST_functionCall_args : public AST_functionCall
{
private:
    string functionName;
    AST_param_list * param_list;
public:
    AST_functionCall_args(string functionName, AST_param_list * param_list);
};

class AST_paramD_list : public AST_node
{
private:
    vector<AST_paramD*> paramDs;
public:
    void push_back(AST_paramD* paramD);
};

class AST_param_list : public AST_node
{
private:
    vector<AST_param*> params;
public:
    void push_back(AST_param* param);
};


class AST_paramD : public AST_node
{
private:
    string dtype;
    AST_param* param;
public:
    AST_paramD(string dtype, AST_param* param);
};

class AST_param : public AST_expr
{

};

class AST_int : public AST_param 
{
private:
    int value;
public:
    AST_int(int value);
};

class AST_bool : public AST_param 
{
private:
    int value;
public:
    AST_bool(int value);
};

class AST_float : public AST_param 
{
private:
    float value;
public:
    AST_float(float value);
};

class AST_variable : public AST_param
{

};

class AST_variable_0D : public AST_variable 
{
private:
    string variableName;
public:
    AST_variable_0D(string variableName);
};

class AST_variable_1D_v : public AST_variable
{
private:
    string variableName;
    AST_variable_0D* index;
public:
    AST_variable_1D_v(string variableName, AST_variable_0D* index);
};

class AST_variable_1D_i : public AST_variable
{
private:
    string variableName;
    int index;
public:
    AST_variable_1D_i(string variableName, int index);
};

class AST_variable_2D_ii : public AST_variable
{
private:
    string variableName;
    int index1,index2;
public:
    AST_variable_2D_ii(string variableName, int index1,int index2);
};

class AST_variable_2D_iv : public AST_variable
{
private:
    string variableName;
    int index1;
    AST_variable_0D* index2;
public:
    AST_variable_2D_iv(string variableName, int index1,AST_variable_0D* index2);
};

class AST_variable_2D_vi : public AST_variable
{
private:
    string variableName;
    AST_variable_0D* index1;
    int index2;
public:
    AST_variable_2D_vi(string variableName, AST_variable_0D* index1, int index2);
};

class AST_variable_2D_vv : public AST_variable
{
private:
    string variableName;
    AST_variable_0D* index1,*index2;
public:
    AST_variable_2D_vv(string variableName, AST_variable_0D* index1,AST_variable_0D* index2);
};