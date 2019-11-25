#include <vector>
#include <string>
#include <iostream>

using namespace std;
#include "AST.h"

//node

//prog

//stmts
void AST_stmts::push_back(AST_stmt* stmt)
{
    this->stmt_list.push_back(stmt);
}
void AST_stmts::accept(Visitor & v)
{
    v.visit(this);
}
//stmt

//semicolon
void AST_semicolon::accept(Visitor & v)
{
    v.visit(this);
}

//keyword
AST_keyword::AST_keyword(string keyword_type)
{
    this->keyword_type = keyword_type;
}
void AST_keyword::accept(Visitor & v)
{
    v.visit(this);
}

//function_decl
AST_function_decl::AST_function_decl(string dtype, string functionName, AST_paramD_list* paramD_list, AST_stmts* stmts)
{
    this->dtype = dtype;
    this->functionName = functionName;
    this->paramD_list = paramD_list;
    this->stmts = stmts;
}
void AST_function_decl::accept(Visitor & v)
{
    v.visit(this);
}

//variable_decl
AST_variable_decl::AST_variable_decl(string dtype, AST_variable* variable)
{
    this->dtype = dtype;
    this->variable = variable;
}
void AST_variable_decl::accept(Visitor & v)
{
    v.visit(this);
}

//assignStmt

//assignStmt_old
AST_assignStmt_old::AST_assignStmt_old(AST_variable* varName, AST_expr* expr)
{
    this->varName = varName;
    this->expr = expr;
}
void AST_assignStmt_old::accept(Visitor & v)
{
    v.visit(this);
}

//AST_assignStmt_new
AST_assignStmt_new::AST_assignStmt_new(string dtype, AST_variable* varName, AST_expr* expr)
{
    this->dtype = dtype;
    this->varName = varName;
    this->expr = expr;
}
void AST_assignStmt_new::accept(Visitor & v)
{
    v.visit(this);
}

//functionCall 

//functionCall_noargs;
AST_functionCall_noargs::AST_functionCall_noargs(string functionName)
{
    this->functionName = functionName;
}
void AST_functionCall_noargs::accept(Visitor & v)
{
    v.visit(this);
}

//functionCall_param
AST_functionCall_args::AST_functionCall_args(string functionName, AST_param_list * param_list)
{
    this->functionName = functionName;
    this->param_list = param_list;
}
void AST_functionCall_args::accept(Visitor & v)
{
    v.visit(this);
}

//ifStmt

//ifWEStmt
AST_ifWEStmt::AST_ifWEStmt(AST_expr* expr, AST_stmts* ifStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
}
void AST_ifWEStmt::accept(Visitor & v)
{
    v.visit(this);
}

//ifEStmt
AST_ifElseStmt::AST_ifElseStmt(AST_expr * expr, AST_stmts* ifStmts, AST_stmts* ifEStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
    this->ifEStmts = ifEStmts;
}
void AST_ifElseStmt::accept(Visitor & v)
{
    v.visit(this);
}

//whileStmt
AST_whileStmt::AST_whileStmt(AST_expr* expr, AST_stmts* whileStmts)
{
    this->expr = expr;
    this->whileStmts = whileStmts;
}
void AST_whileStmt::accept(Visitor & v)
{
    v.visit(this);
}

//forStmt
AST_forStmt::AST_forStmt(AST_assignStmt* initialize, AST_expr* expr, AST_assignStmt* increment, AST_stmts* forStmts)
{
    this->initialize = initialize;
    this->expr = expr;
    this->increment = increment;
    this->forStmts = forStmts;
}
void AST_forStmt::accept(Visitor & v)
{
    v.visit(this);
}

//returnStmt
AST_returnStmt::AST_returnStmt(AST_expr* expr)
{
    this->expr = expr;
}
void AST_returnStmt::accept(Visitor & v)
{
    v.visit(this);
}

//inputStmt
AST_inputStmt::AST_inputStmt(AST_variable* var)
{
    this->var = var;
}
void AST_inputStmt::accept(Visitor & v)
{
    v.visit(this);
}

//outputStmt
AST_outputStmt::AST_outputStmt(AST_variable* var)
{
    this->var = var;
}
void AST_outputStmt::accept(Visitor & v)
{
    v.visit(this);
}

//expr

//expr_unary
AST_expr_unary::AST_expr_unary(string opType, AST_expr* expr)
{
    this->opType = opType;
    this->expr = expr;
}
void AST_expr_unary::accept(Visitor & v)
{
    v.visit(this);
}

//expr_binary
AST_expr_binary::AST_expr_binary(AST_expr* expr1, string opType, AST_expr* expr2)
{
    this->expr1 = expr1;
    this->opType = opType;
    this->expr2 = expr2;
}
void AST_expr_binary::accept(Visitor & v)
{
    v.visit(this);
}

//expr_ternary
AST_expr_ternary::AST_expr_ternary(AST_expr* expr1, AST_expr* expr2, AST_expr* expr3)
{
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
}
void AST_expr_ternary::accept(Visitor & v)
{
    v.visit(this);
}

//paramD_list
void AST_paramD_list::push_back(AST_paramD* paramD)
{
    this->paramDs.push_back(paramD);
}
void AST_paramD_list::accept(Visitor & v)
{
    v.visit(this);
}

//param_list
void AST_param_list::push_back(AST_param* param)
{
    this->params.push_back(param);
}
void AST_param_list::accept(Visitor & v)
{
    v.visit(this);
}

//paramD
AST_paramD::AST_paramD(string dtype, AST_param* param)
{
    this->dtype = dtype;
    this->param = param;
}
void AST_paramD::accept(Visitor & v)
{
    v.visit(this);
}

//param

//int
AST_int::AST_int(int value)
{
    this->value = value;
}
void AST_int::accept(Visitor & v)
{
    v.visit(this);
}

//bool
AST_bool::AST_bool(int value)
{
    this->value = value;
}
void AST_bool::accept(Visitor & v)
{
    v.visit(this);
}

//float
AST_float::AST_float(float value)
{
    this->value = value;
}
void AST_float::accept(Visitor & v)
{
    v.visit(this);
}

//variable

//variable_OD
AST_variable_0D::AST_variable_0D(string variableName)
{
    this->variableName = variableName;
}
void AST_variable_0D::accept(Visitor & v)
{
    v.visit(this);
}

//variable_1D
AST_variable_1D_v::AST_variable_1D_v(string variableName, AST_variable_0D* index)
{
    this->variableName = variableName;
    this->index = index;
}
void AST_variable_1D_v::accept(Visitor & v)
{
    v.visit(this);
}

AST_variable_1D_i::AST_variable_1D_i(string variableName, int index)
{
    this->variableName = variableName;
    this->index = index;
}
void AST_variable_1D_i::accept(Visitor & v)
{
    v.visit(this);
}

//variable_2D
AST_variable_2D_ii::AST_variable_2D_ii(string variableName, int index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
void AST_variable_2D_ii::accept(Visitor & v)
{
    v.visit(this);
}

AST_variable_2D_iv::AST_variable_2D_iv(string variableName, int index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
void AST_variable_2D_iv::accept(Visitor & v)
{
    v.visit(this);
}

AST_variable_2D_vi::AST_variable_2D_vi(string variableName, AST_variable_0D* index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
void AST_variable_2D_vi::accept(Visitor & v)
{
    v.visit(this);
}

AST_variable_2D_vv::AST_variable_2D_vv(string variableName, AST_variable_0D* index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
void AST_variable_2D_vv::accept(Visitor & v)
{
    v.visit(this);
}



//------------------------------
#include "traverse.cpp"