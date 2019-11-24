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


void Traverse::visit(AST_stmts * stmts)
{
    cout << "stmts" << endl;
    for(int i=0;i<(int)stmts->stmt_list.size();i++)
        stmts->stmt_list[i]->accept(*this);
}

//funtion_decl
void Traverse::visit(AST_function_decl * function_decl)
{
    cout<<"funtion decl"<<endl;
    cout<<"dtype "<<function_decl->dtype<<endl;
    cout<<"functionName "<<function_decl->functionName<<endl;
    function_decl->paramD_list->accept(*this);
    function_decl->stmts->accept(*this);
}

//variable_decl
void Traverse::visit(AST_variable_decl *variable_decl)
{
    cout<<"variable decl"<<endl;
    cout<<"dtype "<<variable_decl->dtype<<endl;
    variable_decl->variable->accept(*this);
}

void Traverse::visit(AST_semicolon* semicolon)
{
    cout<<"empty statement "<<endl;
}

void Traverse::visit(AST_keyword* keyword)
{
    cout<<"keyword statement "<<keyword->keyword_type<<endl;
}

//assign_stmt_old
void Traverse::visit(AST_assignStmt_old *assignStmt_old)
{
    cout<<"assignment of old variable"<<endl;
    assignStmt_old->varName->accept(*this);
    assignStmt_old->expr->accept(*this);
}

//assign_stmt_new
void Traverse::visit(AST_assignStmt_new *assignStmt_new)
{
    cout<<"assignment of new variable"<<endl;
    cout<<"dtype "<<assignStmt_new->dtype<<endl;
    assignStmt_new->varName->accept(*this);
    assignStmt_new->expr->accept(*this);
}

//functionCall_noargs
void Traverse::visit(AST_functionCall_noargs *functionCall_noargs)
{
    cout<<"functionCall with no args"<<endl;
    cout<<"functionName "<<functionCall_noargs->functionName<<endl;
}

//functionCall_args
void Traverse::visit(AST_functionCall_args *functionCall_args)
{
    cout<<"functionCall with args"<<endl;
    cout<<"functionName "<<functionCall_args->functionName<<endl;
    functionCall_args->param_list->accept(*this);
}

//ifWEStmt
void Traverse::visit(AST_ifWEStmt *ifWEStmt)
{
    cout<<"if stmt"<<endl;
    ifWEStmt->expr->accept(*this);
    ifWEStmt->ifStmts->accept(*this);
}

//ifElseStmt
void Traverse::visit(AST_ifElseStmt *ifElseStmt)
{   
    cout<<"if else stmt"<<endl;
    ifElseStmt->expr->accept(*this);
    ifElseStmt->ifStmts->accept(*this);
    ifElseStmt->ifEStmts->accept(*this);
}

void Traverse::visit(AST_whileStmt *whileStmt)
{
    cout<<"while stmt"<<endl;
    cout<<"while condition"<<endl;
    whileStmt->expr->accept(*this);
    cout<<"while stmts"<<endl;
    whileStmt->whileStmts->accept(*this);
}

void Traverse::visit(AST_forStmt *forStmt)
{
    cout<<"for stmt"<<endl;
    cout<<"for initialize"<<endl;
    forStmt->initialize->accept(*this);
    cout<<"for condition"<<endl;
    forStmt->expr->accept(*this);
    cout<<"for increment"<<endl;
    forStmt->increment->accept(*this);
    cout<<"for stmts"<<endl;
    forStmt->forStmts->accept(*this);
}

void Traverse::visit(AST_returnStmt *returnStmt)
{
    cout<<"return stmt"<<endl;
    returnStmt->expr->accept(*this);
}

void Traverse::visit(AST_inputStmt *inputStmt)
{
    cout<<"read input stmt"<<endl;
    inputStmt->var->accept(*this);
}

void Traverse::visit(AST_outputStmt *outputStmt)
{
    cout<<"write output stmt"<<endl;
    outputStmt->var->accept(*this);
}

void Traverse::visit(AST_expr_unary *expr_unary)
{
    cout<<"unary expression"<<endl;
    cout<<"operator "<<expr_unary->opType<<endl;
    expr_unary->expr->accept(*this);

}

void Traverse::visit(AST_expr_binary *expr_binary)
{
    cout<<"binary expression"<<endl;
    expr_binary->expr1->accept(*this);
    cout<<"operator "<<expr_binary->opType<<endl;
    expr_binary->expr2->accept(*this);
}

void Traverse::visit(AST_expr_ternary *expr_ternary)
{
    cout<<"ternary expression"<<endl;
    expr_ternary->expr1->accept(*this);
    cout<<"?"<<endl;
    expr_ternary->expr2->accept(*this);
    cout<<":"<<endl;
    expr_ternary->expr3->accept(*this);
}

void Traverse::visit(AST_paramD_list *paramD_list)
{
    cout<<"param list of declarations"<<endl;
    for(int i=0;i<(int)paramD_list->paramDs.size();i++)
        paramD_list->paramDs[i]->accept(*this);

}

void Traverse::visit(AST_param_list *param_list)
{
    cout<<"param list of variables"<<endl;
    for(int i=0;i<(int)param_list->params.size();i++)
        param_list->params[i]->accept(*this);

}

void Traverse::visit(AST_paramD *paramD)
{
    cout<<"param with declaration"<<endl;
    cout<<"dtype "<<paramD->dtype<<endl;
    paramD->param->accept(*this);
}

void Traverse::visit(AST_int *intVal)
{
    cout<<"int literal "<<intVal->value<<endl;
}

void Traverse::visit(AST_float *floatVal)
{
    cout<<"float literal "<<floatVal->value<<endl; 
}

void Traverse::visit(AST_bool* boolVal)
{
    cout<<"bool literal "<<boolVal->value<<endl;
}

void Traverse::visit(AST_variable_0D *variable_0D)
{
    cout<<"0D variable "<<variable_0D->variableName<<endl;
}

void Traverse::visit(AST_variable_1D_v *variable_1D_v)
{
    cout<<"1D variable "<<variable_1D_v->variableName<<endl;
    cout<<"index"<<endl;
    variable_1D_v->index->accept(*this);
}

void Traverse::visit(AST_variable_1D_i *variable_1D_i)
{
    cout<<"1D variable "<<variable_1D_i->variableName<<" index "<<variable_1D_i->index<<endl;
}

void Traverse::visit(AST_variable_2D_ii *variable_2D_ii)
{
    cout<<"2D variable "<<variable_2D_ii->variableName<<" index1 "<<variable_2D_ii->index1<<" index2 "<<variable_2D_ii->index2<<endl;
}

void Traverse::visit(AST_variable_2D_iv *variable_2D_iv)
{
    cout<<"2D variable "<<variable_2D_iv->variableName<<" index1 "<<variable_2D_iv->index1<<endl;
    cout<<"index2"<<endl;
    variable_2D_iv->index2->accept(*this); 
}

void Traverse::visit(AST_variable_2D_vi *variable_2D_vi)
{
    cout<<"2D variable "<<variable_2D_vi->variableName<<endl;
    cout<<"index1"<<endl;
    variable_2D_vi->index1->accept(*this);
    cout<<"index2 "<<variable_2D_vi->index2<<endl;
}

void Traverse::visit(AST_variable_2D_vv *variable_2D_vv)
{
    cout<<"2D variable "<<variable_2D_vv->variableName<<endl;
    cout<<"index1"<<endl;
    variable_2D_vv->index1->accept(*this);
    cout<<"index2"<<endl;
    variable_2D_vv->index2->accept(*this);
}
