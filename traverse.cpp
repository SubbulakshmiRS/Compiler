//stmts
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
