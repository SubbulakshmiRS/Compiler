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

//stmt

//keyword
AST_keyword::AST_keyword(string keyword_type)
{
    this->keyword_type = keyword_type;
}

//function_decl
AST_function_decl::AST_function_decl(string dtype, string functionName, AST_paramD_list* paramD_list, AST_stmts* stmts)
{
    this->dtype = dtype;
    this->functionName = functionName;
    this->paramD_list = paramD_list;
    this->stmts = stmts;
}

//variable_decl
AST_variable_decl::AST_variable_decl(string dtype, AST_variable* variable)
{
    this->dtype = dtype;
    this->variable = variable;
}

//assignStmt

//assignStmt_old
AST_assignStmt_old::AST_assignStmt_old(AST_variable* varName, AST_expr* expr)
{
    this->varName = varName;
    this->expr = expr;
}

//AST_assignStmt_new
AST_assignStmt_new::AST_assignStmt_new(string dtype, AST_variable* varName, AST_expr* expr)
{
    this->dtype = dtype;
    this->varName = varName;
    this->expr = expr;
}

//functionCall 

//functionCall_noargs;
AST_functionCall_noargs::AST_functionCall_noargs(string functionName)
{
    this->functionName = functionName;
}

//functionCall_param
AST_functionCall_args::AST_functionCall_args(string functionName, AST_param_list * param_list)
{
    this->functionName = functionName;
    this->param_list = param_list;
}

//ifStmt

//ifWEStmt
AST_ifWEStmt::AST_ifWEStmt(AST_expr* expr, AST_stmts* ifStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
}

//ifEStmt
AST_ifElseStmt::AST_ifElseStmt(AST_expr * expr, AST_stmts* ifStmts, AST_stmts* ifEStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
    this->ifEStmts = ifEStmts;
}

//whileStmt
AST_whileStmt::AST_whileStmt(AST_expr* expr, AST_stmts* whileStmts)
{
    this->expr = expr;
    this->whileStmts = whileStmts;
}

//forStmt
AST_forStmt::AST_forStmt(AST_variable* intialize_var, AST_variable* start, AST_variable*  step, AST_variable* end, AST_stmts* forStmts)
{
    this->intialize_var = intialize_var;
    this->start = start;
    this->step = step;
    this->end = end;
    this->forStmts = forStmts;
}

//returnStmt
AST_returnStmt::AST_returnStmt(AST_expr* expr)
{
    this->expr = expr;
}

//inputStmt
AST_inputStmt::AST_inputStmt(AST_variable* var)
{
    this->var = var;
}

//outputStmt
AST_outputStmt::AST_outputStmt(AST_variable* var)
{
    this->var = var;
}

//expr

//expr_unary
AST_expr_unary::AST_expr_unary(string opType, AST_expr* expr)
{
    this->opType = opType;
    this->expr = expr;
}

//expr_binary
AST_expr_binary::AST_expr_binary(AST_expr* expr1, string opType, AST_expr* expr2)
{
    this->expr1 = expr1;
    this->opType = opType;
    this->expr2 = expr2;
}

//expr_ternary
AST_expr_ternary::AST_expr_ternary(AST_expr* expr1, AST_expr* expr2, AST_expr* expr3)
{
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
}

//paramD_list
void AST_paramD_list::push_back(AST_paramD* paramD)
{
    this->paramDs.push_back(paramD);
}

//param_list
void AST_param_list::push_back(AST_param* param)
{
    this->params.push_back(param);
}

//paramD
AST_paramD::AST_paramD(string dtype, AST_variable* var)
{
    this->dtype = dtype;
    this->var =  var;
}

//param

//int
AST_int::AST_int(int value)
{
    this->value = value;
}

//bool
AST_bool::AST_bool(int value)
{
    this->value = value;
}

//float
AST_float::AST_float(float value)
{
    this->value = value;
}

//variable

//variable_OD
AST_variable_0D::AST_variable_0D(string variableName)
{
    this->variableName = variableName;
}

//variable_1D
AST_variable_1D_v::AST_variable_1D_v(string variableName, AST_variable_0D* index)
{
    this->variableName = variableName;
    this->index = index;
}
AST_variable_1D_i::AST_variable_1D_i(string variableName, int index)
{
    this->variableName = variableName;
    this->index = index;
}

//variable_2D
AST_variable_2D_ii::AST_variable_2D_ii(string variableName, int index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
AST_variable_2D_iv::AST_variable_2D_iv(string variableName, int index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
AST_variable_2D_vi::AST_variable_2D_vi(string variableName, AST_variable_0D* index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
AST_variable_2D_vv::AST_variable_2D_vv(string variableName, AST_variable_0D* index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}