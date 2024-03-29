//stmts
Literal Traverse::visit(AST_stmts * stmts)
{
    //cout <<"stmts" <<endl;
    Literal ans; 
    for(int i=0;i<(int)stmts->stmt_list.size();i++)
    {
        ans = stmts->stmt_list[i]->accept(*this);
        if(ans.dtype != "None" || ans.value != "")
        {
            cout<<"Stmts interrupt\n";
            return ans;
        }
    }
    ans.dtype = "None"; ans.value = ""; return ans;  
}

//funtion_decl
Literal Traverse::visit(AST_function_decl * function_decl)
{
    // cout<<"funtion decl"<<endl;
    // cout<<"dtype "<<function_decl->dtype<<endl;
    // cout<<"functionName "<<function_decl->functionName<<endl;

    Function f;
    f.dtype = function_decl->dtype;
    f.functionName = function_decl->functionName;
    vector<string> temp;
    vector<AST_variable*> tvar;
    for(int i=0;i<(int)function_decl->paramD_list->paramDs.size();i++)
    {
        temp.push_back(function_decl->paramD_list->paramDs[i]->dtype);
        tvar.push_back(function_decl->paramD_list->paramDs[i]->var);
    }
    f.parameters = temp;
    StmtStore[f] = function_decl->stmts;
    ParamStore[f] = tvar;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

//variable_decl
Literal Traverse::visit(AST_variable_decl *variable_decl)
{
    // cout<<"variable decl"<<endl;
    // cout<<"dtype "<<variable_decl->dtype<<endl;

    Variable v;
    v.dtype = variable_decl->dtype;
    v.var = variable_decl->variable;
    Literal l ;
    l.dtype = "None"; l.value="";
    VarStore[v] = l;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

Literal Traverse::visit(AST_semicolon* semicolon)
{
    // cout<<"empty statement "<<endl;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

Literal Traverse::visit(AST_keyword* keyword)
{
    // cout<<"keyword statement "<<keyword->keyword_type<<endl;
    Literal ans; ans.dtype = "keyword"; ans.value = keyword->keyword_type; return ans;  
}

//assign_stmt_old
Literal Traverse::visit(AST_assignStmt_old *assignStmt_old)
{
    // cout<<"assignment of old variable"<<endl;
    Literal l = assignStmt_old->expr->accept(*this);
    Variable v;
    v.dtype = l.dtype;
    v.var = assignStmt_old->varName;
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it == VarStore.end())
    {
        cout<<"Unable to find the variable of that data type\n";
        assignStmt_old->varName->accept(*this);
        cout<<"Contents of variable map\n";
        for(it = VarStore.begin();it!= VarStore.end();it++)
            cout<<"var : "<<it->first.var->variableName<<endl;

    }
    else 
    {
        VarStore[v] = l;
    }
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;      
}

//assign_stmt_new
Literal Traverse::visit(AST_assignStmt_new *assignStmt_new)
{
    // cout<<"assignment of new variable"<<endl;
    // cout<<"dtype "<<assignStmt_new->dtype<<endl;
    Literal l = assignStmt_new->expr->accept(*this);
    if(l.dtype == assignStmt_new->dtype)
    {
        Variable v;
        v.dtype = assignStmt_new->dtype;
        v.var = assignStmt_new->varName;
        VarStore[v] = l;
    }
    else 
    {
        cout<<"Data type doesnot match between the assigned one and the incoming value"<<endl;
        assignStmt_new->varName->accept(*this);
    }
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

//functionCall_noargs
Literal Traverse::visit(AST_functionCall_noargs *functionCall_noargs)
{
    Function f;
    f.functionName = functionCall_noargs->functionName;
    vector<string> temp;
    f.parameters = temp;
    
    f.dtype = "void";
    map<Function, AST_stmts*>::iterator it = StmtStore.find(f);
    if(it != StmtStore.end())  
        return StmtStore[f]->accept(*this);

    f.dtype = "int";
    it =  StmtStore.find(f);;
    if(it != StmtStore.end())  
        return StmtStore[f]->accept(*this);    

    f.dtype = "bool";
    it =  StmtStore.find(f);;
    if(it != StmtStore.end())  
        return StmtStore[f]->accept(*this); 

    cout<<"Unable to find function(not declared before\n";
    cout<<"functionName with no args"<<functionCall_noargs->functionName<<endl;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;
}

//functionCall_args
Literal Traverse::visit(AST_functionCall_args *functionCall_args)
{
    // cout<<"functionCall with args"<<endl;

    vector<string> ttypes,tvals;
    for(int i=0;i<(int)functionCall_args->param_list->params.size();i++)
    {
        Literal l = functionCall_args->param_list->params[i]->accept(*this);
        ttypes.push_back(l.dtype);
        tvals.push_back(l.value);
    }
    Function f;
    f.functionName = functionCall_args->functionName;
    f.parameters = ttypes;
    
    f.dtype = "void";
    map<Function, AST_stmts*>::iterator it = StmtStore.find(f);
    map<Function, vector<AST_variable*>>::iterator it1 = ParamStore.find(f);
    if(it != StmtStore.end() && it1 != ParamStore.end())
    {
        vector<Variable> keys;
        for(int i=0;i<tvals.size();i++)
        {
            Literal l; Variable v;
            l.dtype = ttypes[i];
            l.value = tvals[i];

            v.dtype = ttypes[i];
            v.var = it1->second[i];
            VarStore[v] = l;
            keys.push_back(v);
        }
        Literal tlit = StmtStore[f]->accept(*this);
        for(int i=0;i<keys.size();i++)
            VarStore.erase(keys[i]);
        return tlit;
    }  

    f.dtype = "int";
    it =  StmtStore.find(f);
    it1 = ParamStore.find(f);
    if(it != StmtStore.end() && it1 != ParamStore.end())
    {
        vector<Variable> keys;
        for(int i=0;i<tvals.size();i++)
        {
            Literal l; Variable v;
            l.dtype = ttypes[i];
            l.value = tvals[i];

            v.dtype = ttypes[i];
            v.var = it1->second[i];
            VarStore[v] = l;
            keys.push_back(v);
        }
        Literal tlit = StmtStore[f]->accept(*this);
        for(int i=0;i<keys.size();i++)
            VarStore.erase(keys[i]);
        return tlit;
    }   

    f.dtype = "bool";
    it =  StmtStore.find(f);
    it1 = ParamStore.find(f);
    if(it != StmtStore.end() && it1 != ParamStore.end())
    {
        vector<Variable> keys;
        for(int i=0;i<tvals.size();i++)
        {
            Literal l; Variable v;
            l.dtype = ttypes[i];
            l.value = tvals[i];

            v.dtype = ttypes[i];
            v.var = it1->second[i];
            VarStore[v] = l;
            keys.push_back(v);
        }
        Literal tlit = StmtStore[f]->accept(*this);
        for(int i=0;i<keys.size();i++)
            VarStore.erase(keys[i]);
        return tlit;
    } 

    cout<<"Unable to find function(not declared before\n";
    cout<<"functionName with args "<<functionCall_args->functionName<<endl;
    functionCall_args->param_list->accept(*this);
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;
}

//ifWEStmt
Literal Traverse::visit(AST_ifWEStmt *ifWEStmt)
{
    // cout<<"if stmt"<<endl;
    Literal l = ifWEStmt->expr->accept(*this);
    if(l.dtype == "bool")
    {
        if(l.value ==  "true")
            return ifWEStmt->ifStmts->accept(*this);
    }
    else 
    {
        cout<<"wrong return datatype(not bool)"<<endl;
    }
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

//ifElseStmt
Literal Traverse::visit(AST_ifElseStmt *ifElseStmt)
{   
    // cout<<"if else stmt"<<endl;
    Literal l = ifElseStmt->expr->accept(*this);

    if(l.dtype == "bool")
    {
        if(l.value ==  "true")
            return ifElseStmt->ifStmts->accept(*this);
        else 
            return ifElseStmt->ifEStmts->accept(*this);
    }
    else 
    {
        cout<<"wrong return datatype(not bool)"<<endl;
        Literal ans; ans.dtype = "None"; ans.value = ""; return ans;
    }

}

Literal Traverse::visit(AST_whileStmt *whileStmt)
{
    // cout<<"while stmt"<<endl;
    // cout<<"while condition"<<endl;
    Literal l = whileStmt->expr->accept(*this);
    while(l.dtype == "bool" && l.value == "true")
    {
        Literal t1 = whileStmt->whileStmts->accept(*this);
        if(t1.dtype !="None" || t1.value!="")
            return t1;
        l = whileStmt->expr->accept(*this);
    }
    // cout<<"while stmts"<<endl;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;

}

Literal Traverse::visit(AST_forStmt *forStmt)
{
    Literal ans; ans.dtype = "None"; ans.value = ""; 
    Variable v;
    v.var = forStmt->intialize_var;
    Literal l1 = forStmt->start->accept(*this);
    Literal l2 = forStmt->step->accept(*this);
    Literal l3 = forStmt->end->accept(*this);
    if(l1.dtype == l2.dtype && l2.dtype == l3.dtype)
    {
        v.dtype = l1.dtype;
        if(v.dtype == "int")
        {
            map<Variable,Literal>::iterator it = VarStore.find(v);
            if(it == VarStore.end())
            {
                cout<<"Unable to find the variable of that data type. Contents of variable map\n";
                for(it = VarStore.begin();it!= VarStore.end();it++)
                    cout<<"var : "<<it->first.var->variableName<<endl;
                return ans;
            }
            int a = stoi(l1.value);
            int b = stoi(l2.value);
            int c = stoi(l3.value);
            for(int i=a;i<c;i+=b)
            {
                l1.value = to_string(i);
                VarStore[v]=l1;
                Literal l = forStmt->forStmts->accept(*this);
                if(l.dtype != "None" && l.value != "")
                    return l;
            }
            // cout<<"for stmts"<<endl;
            return ans;
        }
        cout<<"for statement's data type is not int\n";
    }

    cout<<"for statement data type error\n";
    return ans;
    
}

Literal Traverse::visit(AST_returnStmt *returnStmt)
{
    // cout<<"return stmt"<<endl;
    return returnStmt->expr->accept(*this);
}

Literal Traverse::visit(AST_inputStmt *inputStmt)
{
    // cout<<"read input stmt"<<endl;
    return inputStmt->var->accept(*this);
}

Literal Traverse::visit(AST_outputStmt *outputStmt)
{
    // cout<<"write output stmt"<<endl;
    Literal l = outputStmt->var->accept(*this);
    Variable v; v.var = outputStmt->var;

    v.dtype = "void";
    map<Variable, Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())  
        l = VarStore[v];

    v.dtype = "int";
    it =  VarStore.find(v);
    if(it != VarStore.end())  
        l = VarStore[v];    

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())  
        l = VarStore[v]; 

    cout<<"OUTPUT: "<<l.value<<endl;
    Literal ans; ans.dtype = "None"; ans.value = ""; return ans;  
}

Literal Traverse::visit(AST_expr_unary *expr_unary)
{
    // cout<<"unary expression"<<endl;
    // cout<<"operator "<<expr_unary->opType<<endl;
    Literal l =expr_unary->expr->accept(*this);
    Literal ans; ans.dtype = "None"; ans.value = "";
    if(expr_unary->opType == "!")
    {
        if(l.dtype == "bool")
        {
            ans.dtype == "bool";
            if(l.value == "true")
                ans.value = "false";
            else
                ans.value = "true";
            return ans;
        }
        else
        {
            cout<<"datatype not bool for ! operator"<<endl;
        }  
    }
    else
    {
        if(l.dtype == "int")
        {
            ans.dtype = "int";
            if(expr_unary->opType == "-")
            {
                int temp = stoi(l.value);
                temp = (-1)*temp;
                string tmp = to_string(temp);
                ans.value = tmp;
            }
            else 
                ans.value = l.value;
            return ans;
        }
        else 
        {
            cout<<"unary expr: datatype not int for operator: "<<expr_unary->opType<<endl;
        }

    }
    return ans;

}

Literal Traverse::visit(AST_expr_binary *expr_binary)
{
    // cout<<"binary expression"<<endl;
    Literal l1 =expr_binary->expr1->accept(*this);
    // cout<<"operator "<<expr_binary->opType<<endl;
    Literal l2 =expr_binary->expr2->accept(*this);
    Literal ans; ans.dtype="None"; ans.value="";
    if(expr_binary->opType == "+")
    {
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            ans.dtype = l1.dtype;
            ans.value = to_string((int)(stoi(l1.value) + stoi(l2.value)));
            return ans;
        }
    }
    else if(expr_binary->opType == "-")
    {
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            ans.dtype = l1.dtype;
            ans.value = to_string((int)(stoi(l1.value) - stoi(l2.value)));
            return ans;
        }
    }
    else if(expr_binary->opType == "*")
    {
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            ans.dtype = l1.dtype;
            ans.value = to_string((int)(stoi(l1.value) * stoi(l2.value)));
            return ans;
        }
    }
    else if(expr_binary->opType == "/")
    {
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            ans.dtype = l1.dtype;
            ans.value = to_string((int)(stoi(l1.value) / stoi(l2.value)));
            return ans;
        }
    }
    else if(expr_binary->opType == "&&")
    {
        ans.dtype = "bool";

        if( l1.dtype =="bool" && l2.dtype == "bool")
        {
            bool a = boost::lexical_cast<bool>(l1.value);
            bool b = boost::lexical_cast<bool>(l2.value);
            if(a&&b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    }
    else if(expr_binary->opType == "||")
    {
        if(l1.dtype == "bool" && l2.dtype == "bool")
        {
            bool a = boost::lexical_cast<bool>(l1.value);
            bool b = boost::lexical_cast<bool>(l2.value);
            if(a || b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    } 
    else if(expr_binary->opType == ">=")
    {
        ans.dtype = "bool";
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            int a= (int)stoi(l1.value);
            int b= (int)stoi(l2.value);
            if(a >= b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    } 
    else if(expr_binary->opType == ">")
    {
        ans.dtype = "bool";
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            int a= (int)stoi(l1.value);
            int b= (int)stoi(l2.value);
            if(a > b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    } 
    else if(expr_binary->opType == "<=")
    {
        ans.dtype = "bool";
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            int a= (int)stoi(l1.value);
            int b= (int)stoi(l2.value);
            if(a <= b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    }  
    else if(expr_binary->opType == "<")
    {
        // cout<<"compare "<<l1.dtype<<l1.value<<" "<<l2.dtype<<l2.value<<endl;
        ans.dtype = "bool";
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            int a= (int)stoi(l1.value);
            int b= (int)stoi(l2.value);
            if(a < b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    } 
    else if(expr_binary->opType == "==")
    {
        ans.dtype = "bool";
        if(l1.dtype == "int" && l2.dtype=="int")
        {
            int a= (int)stoi(l1.value);
            int b= (int)stoi(l2.value);
            if(a == b)
                ans.value = "true";
            else 
                ans.value = "false";
            return ans;
        }
    } 
    
    cout<<"error in binary expr:\nL1:"<<l1.dtype<<" "<<l1.value<<"\nL2:"<<l2.dtype<<" "<<l2.value<<"\nop:"<<expr_binary->opType<<endl;
    return ans;
    
}

Literal Traverse::visit(AST_expr_ternary *expr_ternary)
{
    Literal l1 = expr_ternary->expr1->accept(*this);
    // cout<<"?"<<endl;
    Literal l2 = expr_ternary->expr2->accept(*this);
    // cout<<":"<<endl;
    Literal l3 = expr_ternary->expr3->accept(*this);

    Literal ans; ans.dtype="None"; ans.value="";
    if(l1.dtype == "bool")
    {
        bool a = boost::lexical_cast<bool>(l1.value);
        if(a)
            return l2;
        else 
            return l3;
    }
    cout<<"error in ternary expression"<<endl;
    return ans;

}

Literal Traverse::visit(AST_paramD_list *paramD_list)
{
    // cout<<"param list of declarations"<<endl;
    Literal ans; 
    for(int i=0;i<(int)paramD_list->paramDs.size();i++)
        ans = paramD_list->paramDs[i]->accept(*this);
    ans.dtype = "None"; ans.value = ""; return ans;  
}

Literal Traverse::visit(AST_param_list *param_list)
{
    // cout<<"param list of variables"<<endl;
    Literal ans;
    for(int i=0;i<(int)param_list->params.size();i++)
        ans = param_list->params[i]->accept(*this);
    ans.dtype = "None"; ans.value = ""; return ans;  
}

Literal Traverse::visit(AST_paramD *paramD)
{
    // cout<<"param with declaration"<<endl;
    // cout<<"dtype "<<paramD->dtype<<endl;
    return paramD->var->accept(*this);
}

Literal Traverse::visit(AST_int *intVal)
{
    // cout<<"int literal "<<intVal->value<<endl;
    Literal l;
    l.dtype = "int";
    l.value = to_string(intVal->value);
    return l;
}

Literal Traverse::visit(AST_float *floatVal)
{
    // cout<<"float literal "<<floatVal->value<<endl; 
    Literal l;
    l.dtype = "float";
    l.value = to_string(floatVal->value);
    return l;
}

Literal Traverse::visit(AST_bool* boolVal)
{
    // cout<<"bool literal "<<boolVal->value<<endl;
    Literal l;
    l.dtype = "bool";
    l.value = to_string(boolVal->value);
    return l;
}

Literal Traverse::visit(AST_variable_0D *variable_0D)
{
    Variable v; v.var = variable_0D;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    Literal ans; ans.dtype="None"; ans.value=""; 
    cout<<"0D variable "<<variable_0D->variableName<<endl;
    return ans;
}

Literal Traverse::visit(AST_variable_1D_v *variable_1D_v)
{

    Literal ans = variable_1D_v->index->accept(*this);
    Variable v; v.var = variable_1D_v;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    ans.dtype="None"; ans.value="";
    cout<<"1D variable "<<variable_1D_v->variableName<<endl;
    cout<<"index"<<endl;
    return ans;
}

Literal Traverse::visit(AST_variable_1D_i *variable_1D_i)
{
    Variable v; v.var = variable_1D_i;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    Literal ans; ans.dtype="None"; ans.value="";
    cout<<"1D variable "<<variable_1D_i->variableName<<" index "<<variable_1D_i->index<<endl;
    return ans;
}

Literal Traverse::visit(AST_variable_2D_ii *variable_2D_ii)
{
    Variable v; v.var = variable_2D_ii;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "float";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "string";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    Literal ans; ans.dtype="None"; ans.value="";
    cout<<"2D variable "<<variable_2D_ii->variableName<<" index1 "<<variable_2D_ii->index1<<" index2 "<<variable_2D_ii->index2<<endl;
    return ans;
}

Literal Traverse::visit(AST_variable_2D_iv *variable_2D_iv)
{
    cout<<"2D variable "<<variable_2D_iv->variableName<<" index1 "<<variable_2D_iv->index1<<endl;
    cout<<"index2"<<endl;
    Literal ans = variable_2D_iv->index2->accept(*this);
    Variable v; v.var = variable_2D_iv;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "float";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "string";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    ans.dtype="None"; ans.value="";

    return ans; 
}

Literal Traverse::visit(AST_variable_2D_vi *variable_2D_vi)
{

    Literal ans = variable_2D_vi->index1->accept(*this);
    Variable v; v.var = variable_2D_vi;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "float";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "string";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    ans.dtype="None"; ans.value="";
    cout<<"2D variable "<<variable_2D_vi->variableName<<endl;
    cout<<"index1"<<endl;
    cout<<"index2 "<<variable_2D_vi->index2<<endl;
    return ans;
}

Literal Traverse::visit(AST_variable_2D_vv *variable_2D_vv)
{

    Literal ans = variable_2D_vv->index1->accept(*this);
    ans = variable_2D_vv->index2->accept(*this);
    Variable v; v.var = variable_2D_vv;

    v.dtype = "int";
    map<Variable,Literal>::iterator it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "bool";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "float";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    v.dtype = "string";
    it = VarStore.find(v);
    if(it != VarStore.end())
        return VarStore[v];

    ans.dtype="None"; ans.value="";
    cout<<"2D variable "<<variable_2D_vv->variableName<<endl;
    cout<<"index1"<<endl;
    cout<<"index2"<<endl;
    return ans;
}
