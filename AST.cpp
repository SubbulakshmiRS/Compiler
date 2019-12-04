#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;
#include "AST.h"

//node

//prog

//stmts
void AST_stmts::push_back(AST_stmt* stmt)
{
    this->stmt_list.push_back(stmt);
}
Value* AST_stmts::accept(Visitor & v)
{
    cout<<"stmts visited\n";
    return v.visit(this);
}
//stmt

//semicolon
Value* AST_semicolon::accept(Visitor & v)
{
    return v.visit(this);
}

//keyword
AST_keyword::AST_keyword(string keyword_type)
{
    this->keyword_type = keyword_type;
}
Value* AST_keyword::accept(Visitor & v)
{
    return v.visit(this);
}

//function_decl
AST_function_decl::AST_function_decl(string dtype, string functionName, AST_paramD_list* paramD_list, AST_stmts* stmts)
{
    this->dtype = dtype;
    this->functionName = functionName;
    this->paramD_list = paramD_list;
    this->stmts = stmts;
}
Value* AST_function_decl::accept(Visitor & v)
{
    return v.visit(this);
}

//variable_decl
AST_variable_decl::AST_variable_decl(string dtype, AST_variable* variable)
{
    this->dtype = dtype;
    this->variable = variable;
}
Value* AST_variable_decl::accept(Visitor & v)
{
    return v.visit(this);
}

//assignStmt

//assignStmt_old
AST_assignStmt_old::AST_assignStmt_old(AST_variable* varName, AST_expr* expr)
{
    this->varName = varName;
    this->expr = expr;
}
Value* AST_assignStmt_old::accept(Visitor & v)
{
    return v.visit(this);
}

//AST_assignStmt_new
AST_assignStmt_new::AST_assignStmt_new(string dtype, AST_variable* varName, AST_expr* expr)
{
    this->dtype = dtype;
    this->varName = varName;
    this->expr = expr;
}
Value* AST_assignStmt_new::accept(Visitor & v)
{
    return v.visit(this);
}

//functionCall 

//functionCall_noargs;
AST_functionCall_noargs::AST_functionCall_noargs(string functionName)
{
    this->functionName = functionName;
}
Value* AST_functionCall_noargs::accept(Visitor & v)
{
    return v.visit(this);
}

//functionCall_param
AST_functionCall_args::AST_functionCall_args(string functionName, AST_param_list * param_list)
{
    this->functionName = functionName;
    this->param_list = param_list;
}
Value* AST_functionCall_args::accept(Visitor & v)
{
    return v.visit(this);
}

//ifStmt

//ifWEStmt
AST_ifWEStmt::AST_ifWEStmt(AST_expr* expr, AST_stmts* ifStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
}
Value* AST_ifWEStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//ifEStmt
AST_ifElseStmt::AST_ifElseStmt(AST_expr * expr, AST_stmts* ifStmts, AST_stmts* ifEStmts)
{
    this->expr = expr;
    this->ifStmts = ifStmts;
    this->ifEStmts = ifEStmts;
}
Value* AST_ifElseStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//whileStmt
AST_whileStmt::AST_whileStmt(AST_expr* expr, AST_stmts* whileStmts)
{
    this->expr = expr;
    this->whileStmts = whileStmts;
}
Value* AST_whileStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//forStmt
AST_forStmt::AST_forStmt(AST_assignStmt* initialize, int end, int increment, AST_stmts* forStmts)
{
    this->initialize = initialize;
    this->end = end;
    this->increment = increment;
    this->forStmts = forStmts;
}
Value* AST_forStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//returnStmt
AST_returnStmt::AST_returnStmt(AST_expr* expr)
{
    this->expr = expr;
}
Value* AST_returnStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//inputStmt
AST_inputStmt::AST_inputStmt(AST_variable* var)
{
    this->var = var;
}
Value* AST_inputStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//outputStmt
AST_outputStmt::AST_outputStmt(AST_variable* var)
{
    this->var = var;
}
Value* AST_outputStmt::accept(Visitor & v)
{
    return v.visit(this);
}

//expr

//expr_unary
AST_expr_unary::AST_expr_unary(string opType, AST_expr* expr)
{
    this->opType = opType;
    this->expr = expr;
}
Value* AST_expr_unary::accept(Visitor & v)
{
    return v.visit(this);
}

//expr_binary
AST_expr_binary::AST_expr_binary(AST_expr* expr1, string opType, AST_expr* expr2)
{
    this->expr1 = expr1;
    this->opType = opType;
    this->expr2 = expr2;
}
Value* AST_expr_binary::accept(Visitor & v)
{
    return v.visit(this);
}

//expr_ternary
AST_expr_ternary::AST_expr_ternary(AST_expr* expr1, AST_expr* expr2, AST_expr* expr3)
{
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
}
Value* AST_expr_ternary::accept(Visitor & v)
{
    return v.visit(this);
}

//paramD_list
void AST_paramD_list::push_back(AST_paramD* paramD)
{
    this->paramDs.push_back(paramD);
}
Value* AST_paramD_list::accept(Visitor & v)
{
    return v.visit(this);
}

//param_list
void AST_param_list::push_back(AST_param* param)
{
    this->params.push_back(param);
}
Value* AST_param_list::accept(Visitor & v)
{
    return v.visit(this);
}

//paramD
AST_paramD::AST_paramD(string dtype, AST_variable* var)
{
    this->dtype = dtype;
    this->var = var;
}
Value* AST_paramD::accept(Visitor & v)
{
    return v.visit(this);
}

//param

//int
AST_int::AST_int(int value)
{
    this->value = value;
}
Value* AST_int::accept(Visitor & v)
{
    return v.visit(this);
}

//bool
AST_bool::AST_bool(int value)
{
    this->value = value;
}
Value* AST_bool::accept(Visitor & v)
{
    return v.visit(this);
}

//float
AST_float::AST_float(float value)
{
    this->value = value;
}
Value* AST_float::accept(Visitor & v)
{
    return v.visit(this);
}

//variable

//variable_OD
AST_variable_0D::AST_variable_0D(string variableName)
{
    this->variableName = variableName;
}
Value* AST_variable_0D::accept(Visitor & v)
{
    return v.visit(this);
}

//variable_1D
AST_variable_1D_v::AST_variable_1D_v(string variableName, AST_variable_0D* index)
{
    this->variableName = variableName;
    this->index = index;
}
Value* AST_variable_1D_v::accept(Visitor & v)
{
    return v.visit(this);
}

AST_variable_1D_i::AST_variable_1D_i(string variableName, int index)
{
    this->variableName = variableName;
    this->index = index;
}
Value* AST_variable_1D_i::accept(Visitor & v)
{
    return v.visit(this);
}

//variable_2D
AST_variable_2D_ii::AST_variable_2D_ii(string variableName, int index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
Value* AST_variable_2D_ii::accept(Visitor & v)
{
    return v.visit(this);
}

AST_variable_2D_iv::AST_variable_2D_iv(string variableName, int index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
Value* AST_variable_2D_iv::accept(Visitor & v)
{
    return v.visit(this);
}

AST_variable_2D_vi::AST_variable_2D_vi(string variableName, AST_variable_0D* index1,int index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
Value* AST_variable_2D_vi::accept(Visitor & v)
{
    return v.visit(this);
}

AST_variable_2D_vv::AST_variable_2D_vv(string variableName, AST_variable_0D* index1,AST_variable_0D* index2)
{
    this->variableName = variableName;
    this->index1 = index1;
    this->index2 = index2;
}
Value* AST_variable_2D_vv::accept(Visitor & v)
{
    return v.visit(this);
}



//------------------------------
#include "codegen.cpp"

