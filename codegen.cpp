Value * ErrorV(const char *str) { printf("Error:\n%s\n",str); return 0; }
Value * ErrorV(string str) { cout << "Error:\n" << str << "\n"; return 0; }


static LLVMContext Context;
static Module * module;
static map<string, Value *> NamedValues;
static IRBuilder<> Builder(Context);

Constant *CalleeF;

CodeGen::CodeGen()
{
    module = new Module("MyCompiler", getGlobalContext());
    CalleeF = module->getOrInsertFunction("printf",FunctionType::get(IntegerType::getInt32Ty(getGlobalContext()), PointerType::get(Type::getInt8Ty(getGlobalContext()), 0), true ));
    
}

void CodeGen::dump()
{
    printf("sgdy \n ");
    module->dump();
}

AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(Context), 0, VarName);
    } else if (type == "boolean") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(Context), 0, VarName);
    }
    return alloca_instruction;
}

Value* CodeGen::visit(AST_stmts * stmts)
{
    Value* v;
    for(int i=0;i<(int)stmts->stmt_list.size();i++)
    {
        v = stmts->stmt_list[i]->accept(*this);
        if(v == nullptr)
            return v;
    }
    return v;
}

Value* CodeGen::visit(AST_function_decl * function_decl) 
{
    vector<string> argNames;
    vector<string> argTypes;

    vector<Type *> arguments;

    auto arg_size = (int)function_decl->paramD_list->paramDs.size();

    for (int i=0;i<(int)function_decl->paramD_list->paramDs.size();i++) {
        string arg_type = function_decl->paramD_list->paramDs[i]->dtype;
        string arg_name = function_decl->paramD_list->paramDs[i]->var->variableName;
        if (arg_type == "int") {
            arguments.push_back(Type::getInt32Ty(Context));
        } else if (arg_type == "bool") {
            arguments.push_back(Type::getInt1Ty(Context));
        } else {
            return ErrorV("ERROR: Arguments can only be int or bool");
        }
        argTypes.emplace_back(arg_type);
        argNames.emplace_back(arg_name);
    }

    Type *returnType;
    if (function_decl->dtype == "int") {
        returnType = Type::getInt32Ty(Context);
    } else if (function_decl->dtype == "bool") {
        returnType = Type::getInt1Ty(Context);
    } else if (function_decl->dtype == "void") {
        returnType = Type::getVoidTy(Context);
    } else {
        return ErrorV("ERROR: Invalid Return Type for " + function_decl->functionName + ". Return Type can only be int or bool or bool");
    } 

    FunctionType *FT = FunctionType::get(returnType, arguments, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, function_decl->functionName , module);


    unsigned Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != arg_size; ++AI, ++Idx) {
        AI->setName(argNames[Idx]);
    }

    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);
    Builder.SetInsertPoint(BB);
    Idx = 0;      

    for (auto &Arg : F->args()) {
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(F, argNames[Idx], argTypes[Idx]);
        Builder.CreateStore(&Arg, Alloca);
        NamedValues[argNames[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal = function_decl->stmts->accept(*this);

    if(RetVal==nullptr)
    {
        if(function_decl->dtype=="void")
            Builder.CreateRetVoid();

        if(function_decl->dtype == "bool" or function_decl->dtype == "int")
        {
            return ErrorV("ERROR: Invalid Return Type for " + function_decl->functionName + ". Return Type can only be " + function_decl->dtype + " as defined");
        }    

        verifyFunction(*F);
        return F;
    }

    if (RetVal) {
        if (function_decl->dtype == "void")
        {
            Builder.CreateRetVoid();
        }
        else
        {
            if(!RetVal->getType()->isIntegerTy(32) and function_decl->dtype == "int")
            {
                return ErrorV("ERROR: Invalid Return Type for " + function_decl->functionName + ". Return Type can only be int as defined");
            }

            if(!RetVal->getType()->isIntegerTy(1) and function_decl->dtype == "bool")
            {              
                return ErrorV("ERROR: Invalid Return Type for " + function_decl->functionName + ". Return Type can only be int as defined");
            }       

        }

        verifyFunction(*F);
        return F;
    }    

    F->eraseFromParent();
    return nullptr;
}

Value* CodeGen::visit(AST_variable_decl *variable_decl)
{
    variable_decl->variable->accept(*this);
    
    return 0;
}

Value* CodeGen::visit(AST_semicolon* semicolon)
{
    
    return 0;
}

Value* CodeGen::visit(AST_keyword* keyword)
{
    
    return 0;
}

Value* CodeGen::visit(AST_assignStmt_old *assignStmt_old)
{
    Value * expr_value = assignStmt_old->expr->accept(*this);
    if(load_variable)
    {
        expr_value = Builder.CreateLoad(expr_value);       
    }

    Value * variable_value = assignStmt_old->varName->accept(*this);
    return Builder.CreateStore(expr_value, variable_value);
}

Value* CodeGen::visit(AST_assignStmt_new *assignStmt_new)
{
    if(assignStmt_new->dtype == "int" )
    {
        module->getOrInsertGlobal(assignStmt_new->varName->variableName,Builder.getInt32Ty());
        GlobalVariable* gv = module->getNamedGlobal(assignStmt_new->varName->variableName);
        gv->setLinkage(GlobalValue::CommonLinkage);
        gv->setInitializer(ConstantInt::get(getGlobalContext(), APInt(32,(int)stoi(assignStmt_new->varName->variableName))));
    }

    Value * expr_value = assignStmt_new->expr->accept(*this);
    if(load_variable)
    {
        expr_value = Builder.CreateLoad(expr_value);   
    }

    Value * variable_value = assignStmt_new->varName->accept(*this);
    if(load_variable)
    {
        variable_value = Builder.CreateLoad(variable_value);
                
    }
    return Builder.CreateStore(expr_value, variable_value);

}

Value* CodeGen::visit(AST_functionCall_noargs *functionCall_noargs)
{
    Function *calle = module->getFunction(functionCall_noargs->functionName);
    if (calle == nullptr) {
        return ErrorV("ERROR: Unknown Function Name" + functionCall_noargs->functionName);
    }
    
    if (calle->arg_size() != 0) {
        return ErrorV("ERROR: Incorrect Number of Parameters Passed");
    }
    
    vector<Value *> Args;

    Value *v = Builder.CreateCall(calle, Args);
    return v;
}

Value* CodeGen::visit(AST_functionCall_args *functionCall_args)
{

    Function *calle = module->getFunction(functionCall_args->functionName);
    if (calle == nullptr) {
        return ErrorV("ERROR: Unknown Function Name" + functionCall_args->functionName);
    }

    vector<AST_param* > args_list = functionCall_args->param_list->params;
    if (calle->arg_size() != args_list.size()) {
        return ErrorV("ERROR: Incorrect Number of Parameters Passed");
    }
    
    FunctionType *FTy = calle->getFunctionType();

    for(int i=0; i<(int)args_list.size(); i++)
    {
        Value *argVal = functionCall_args->param_list->params[i]->accept(*this);
        if (load_variable) {
            argVal = Builder.CreateLoad(argVal);
        }
        if (argVal == nullptr) {
            return ErrorV("ERROR: Argument is not valid");
        }

        if(argVal->getType() != FTy->getParamType(i))
        {
            return ErrorV("ERROR: Incorrect type found in passing " + functionCall_args->functionName + " function parameters");
        }

    }

    vector<Value *> Args;
    for(int i=0; i<(int)args_list.size(); i++)
    {
        Value *argVal = functionCall_args->param_list->params[i]->accept(*this);
        if (load_variable) {
            argVal = Builder.CreateLoad(argVal);
        }
        if (argVal == nullptr) {
            return ErrorV("ERROR: Argument is not valid");
        }
        Args.push_back(argVal);
    }

    Value *v = Builder.CreateCall(calle, Args);
    return v;
}

Value* CodeGen::visit(AST_ifWEStmt *ifWEStmt)
{
    Value *cond = ifWEStmt->expr->accept(*this);
    if (cond == nullptr) {
        return ErrorV("ERROR: Invalid Expression in the IF");
    }

    if(!cond->getType()->isIntegerTy(1))
    {
        return ErrorV("ERROR: Condition in IF must be of boolean type");        
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    Builder.SetInsertPoint(ifBlock);

    Value *if_val = ifWEStmt->ifStmts->accept(*this);
    if (if_val == nullptr) {
        return nullptr;
    }

    ifBlock = Builder.GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(nextBlock);
    Builder.SetInsertPoint(nextBlock);
    Value *V = ConstantInt::get(Context, APInt(32, 0));
    return V;  
}

Value* CodeGen::visit(AST_ifElseStmt *ifElseStmt)
{
    Value *cond = ifElseStmt->expr->accept(*this);
    if (cond == nullptr) {
        return ErrorV("ERROR: Invalid Expression in the IF");
    }

    if(!cond->getType()->isIntegerTy(1))
    {
        return ErrorV("ERROR: Condition in IF must be of boolean type");        
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *elseBlock = BasicBlock::Create(Context, "else");
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    BasicBlock *otherBlock = elseBlock;
    Builder.CreateBr(nextBlock);

    Builder.CreateCondBr(cond, ifBlock, otherBlock);
    Builder.SetInsertPoint(ifBlock);

    Value *if_val = ifElseStmt->ifStmts->accept(*this);
    if (if_val == nullptr) {
        return nullptr;
    }

    ifBlock = Builder.GetInsertBlock();

    Value *else_val = nullptr;

    TheFunction->getBasicBlockList().push_back(elseBlock);
    Builder.SetInsertPoint(elseBlock);
    else_val = ifElseStmt->ifEStmts->accept(*this);
    if (else_val == nullptr) {
        return nullptr;
    }

    Builder.CreateBr(nextBlock);

    TheFunction->getBasicBlockList().push_back(nextBlock);
    Builder.SetInsertPoint(nextBlock);
    Value *V = ConstantInt::get(Context, APInt(32, 0));
    return V;  
}

Value* CodeGen::visit(AST_whileStmt *whileStmt)
{
    Function *funct = Builder.GetInsertBlock()->getParent();

    Builder.GetInsertBlock();
    BasicBlock * cond_body = BasicBlock::Create(getGlobalContext(), "while_condition", funct);
    BasicBlock * loop_body = BasicBlock::Create(getGlobalContext(), "loop", funct);
    BasicBlock * afterBB = BasicBlock::Create(getGlobalContext(), "afterloop", funct);

    Builder.CreateBr(cond_body);
    Builder.SetInsertPoint(cond_body);
    Value * condition_value = whileStmt->expr->accept(*this);;
    if(load_variable){ condition_value = Builder.CreateLoad(condition_value); }
    //condition_value = Builder.CreateICmpEQ(condition_value, ConstantInt::get(Type::getInt1Ty(getGlobalContext()), true, true),"ifcond");
    Builder.CreateCondBr(condition_value, loop_body, afterBB);

    Builder.SetInsertPoint(loop_body);
    Value * body = whileStmt->whileStmts->accept(*this);
    if(load_variable){ body = Builder.CreateLoad(body); }

    Builder.CreateBr(cond_body);
    Builder.GetInsertBlock();
    Builder.SetInsertPoint(afterBB);

    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    return V;
}

Value* CodeGen::visit(AST_forStmt *forStmt)
{
    string var = forStmt->initialize->varName->variableName;
    Value *start = forStmt->initialize->accept(*this);
    if (start == nullptr) {
        return nullptr;
    }
    if (load_variable) {
        start = Builder.CreateLoad(start);
    }

    if(!(start->getType()->isIntegerTy(32)))
    {
        return ErrorV("ERROR:  For loop initial expr must have type integer");
    }    

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, var, string("int"));
    Builder.CreateStore(start, Alloca);

    Value *step_val = ConstantInt::get(Context, APInt(32, (int)forStmt->increment));
    BasicBlock *pre_header_basic_block = Builder.GetInsertBlock();
    BasicBlock *loop_body = BasicBlock::Create(Context, "loop", TheFunction);
    BasicBlock *afterBB = BasicBlock::Create(Context, "afterloop", TheFunction);
    Builder.CreateBr(loop_body);
    Builder.SetInsertPoint(loop_body);

    PHINode *Variable = Builder.CreatePHI(Type::getInt32Ty(Context), 2, var);
    Variable->addIncoming(start, pre_header_basic_block);
    Value *cond = ConstantInt::get(Context, APInt(32, (int)forStmt->end));
    if (cond == nullptr) {
        return ErrorV("ERROR: Invalid Condition");
    }    

    if (load_variable) {
        cond = Builder.CreateLoad(cond);
    }

    if(!(cond->getType()->isIntegerTy(32)))
    {
        return ErrorV("ERROR:  For loop ending expr must have type integer");
    }   

    Value *OldVal = NamedValues[var];
    NamedValues[var] = Alloca;

    if (forStmt->forStmts->accept(*this) == nullptr) {
        return nullptr;
    }

    Value *cur = Builder.CreateLoad(Alloca, var);
    Value *next_val = Builder.CreateAdd(cur, step_val, "NextVal");
    Builder.CreateStore(next_val, Alloca);
    cond = Builder.CreateICmpSLT(next_val, cond, "loopcondition");
    BasicBlock *loopEndBlock = Builder.GetInsertBlock();
    Builder.CreateCondBr(cond, loop_body, afterBB);
    Builder.SetInsertPoint(afterBB);
    Variable->addIncoming(next_val, loopEndBlock);

    if (OldVal) {
        NamedValues[var] = OldVal;
    } else {
        NamedValues.erase(var);
    }
    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    return V;
}

Value* CodeGen::visit(AST_returnStmt *returnStmt)
{
    Value* V = returnStmt->expr->accept(*this);
    if (V) {
        V = Builder.CreateLoad(V);
    }
    Builder.CreateRet(V);
    return V;
}

Value* CodeGen::visit(AST_inputStmt *inputStmt)
{
    // no clue
    return 0;
}

Value* CodeGen::visit(AST_outputStmt *outputStmt)
{
    vector<Value *> args;

    
    Value * v = outputStmt->var->accept(*this);
    if(v){v = Builder.CreateLoad(v); }

    str_ = "\n";
    Value* val = Builder.CreateGlobalStringPtr("%s");
    args.push_back(val);
    args.push_back(v);

    return Builder.CreateCall(CalleeF, args, "printfCall");

}

Value* CodeGen::visit(AST_expr_unary *expr_unary)
{
    Value * R = expr_unary->expr->accept(*this);
    if(R) {R = Builder.CreateLoad(R); }


    if(expr_unary->opType == "-" && R->getType()->isIntegerTy(32)) return Builder.CreateNeg(R, "negtmp");
    else if(expr_unary->opType == "-" && R->getType()->isIntegerTy(1)) return Builder.CreateNot(R, "notop");
    else return ErrorV("wrong operand - operator combination for unary expr");

}

Value* CodeGen::visit(AST_expr_binary *expr_binary)
{
    Value * L = expr_binary->expr1->accept(*this);
    if(L){L = Builder.CreateLoad(L); }
    if(L == 0) return ErrorV("Left expression error");


    Value * R = expr_binary->expr2->accept(*this);
    if(R){R = Builder.CreateLoad(R); }
    if(R == 0) return ErrorV("Right expression error");

    string op = expr_binary->opType;
    if(!((op  == "+" || op == "-" || op == "*" || op == "/") && L->getType()->isIntegerTy(32) && R->getType()->isIntegerTy(32)))
        return ErrorV("Both left and right operands are not int ");
    if(!((op  == ">" || op == "<" || op == ">=" || op == "<=" || op == "==") && L->getType()->isIntegerTy(1) && R->getType()->isIntegerTy(1)))
        return ErrorV("Both left and right operands are not bool ");  
        
    if(expr_binary->opType == "+")  return Builder.CreateAdd(L, R, "addtmp");
    else if(expr_binary->opType == "-") return Builder.CreateSub(L, R, "subtmp");
    else if(expr_binary->opType == "*") return Builder.CreateMul(L, R, "multmp");
    else if(expr_binary->opType == "/") return Builder.CreateSDiv(L, R, "divtmp");
    else if(expr_binary->opType == "<") return Builder.CreateICmpSLT(L, R, "lttmp");
    else if(expr_binary->opType == ">") return Builder.CreateICmpSGT(L, R, "gttmp");
    else if(expr_binary->opType == "<=") return Builder.CreateICmpSLE(L, R, "letmp");
    else if(expr_binary->opType == ">=") return Builder.CreateICmpSGE(L, R, "getmp");
    else if(expr_binary->opType == "==") return Builder.CreateICmpEQ(L, R, "eqtmp");
    else return ErrorV("Not a binary operator");

}

Value* CodeGen::visit(AST_expr_ternary *expr_ternary)
{
    //no clue
    expr_ternary->expr1->accept(*this);
    expr_ternary->expr2->accept(*this);
    expr_ternary->expr3->accept(*this);
    
    return 0;
}

Value* CodeGen::visit(AST_paramD_list *paramD_list)
{
    Value * v;
    for(int i=0;i<(int)paramD_list->paramDs.size();i++)
    {
        v = paramD_list->paramDs[i]->accept(*this);
        if(v == nullptr)
            return v;
    }
    
    return v;
}

Value* CodeGen::visit(AST_param_list *param_list)
{
    Value * v;
    for(int i=0;i<(int)param_list->params.size();i++)
    {
        v = param_list->params[i]->accept(*this);
        if(v == nullptr)
            return v;
    }
    
    return v;
}

Value* CodeGen::visit(AST_paramD *paramD)
{
    return paramD->var->accept(*this);
}

Value* CodeGen::visit(AST_int *intVal)
{
    Value *v = ConstantInt::get(Context, APInt(32, static_cast<uint64_t>(intVal->value)));
    return v;
}

Value* CodeGen::visit(AST_bool* boolVal)
{
    return ConstantInt::get(Context, llvm::APInt(1, (bool)boolVal->value));
}

Value* CodeGen::visit(AST_float *floatVal)
{
    
    return 0;
}

Value* CodeGen::visit(AST_variable_0D *variable_0D)
{
    ret = NamedValues[variable_0D->variableName];
    if(ret == NULL)
        ret = module->getGlobalVariable(variable_0D->variableName);
    if(ret == NULL)
        ret = ErrorV("Unknown Variable name " + variable_0D->variableName);
    return ret;
}

Value* CodeGen::visit(AST_variable_1D_v *variable_1D_v)
{
    
    Value * index = variable_1D_v->index->accept(*this);
    if(load_variable){index = Builder.CreateLoad(index); }

    //index = ConstantInt::get(getGlobalContext(), APInt(32, 2));

    if(index == NULL)
        ret = ErrorV("Invalid Array Index in " + variable_1D_v->variableName);

    vector<Value*> array_index;
    array_index.push_back(Builder.getInt32(0));
    array_index.push_back(index);
    return Builder.CreateGEP(module->getNamedGlobal(variable_1D_v->variableName), array_index, variable_1D_v->variableName+"_IDX");

}

Value* CodeGen::visit(AST_variable_1D_i *variable_1D_i)
{
    Value * index = ConstantInt::get(getGlobalContext(), llvm::APInt(32, (int)variable_1D_i->index));

    if(load_variable){index = Builder.CreateLoad(index); }

    //index = ConstantInt::get(getGlobalContext(), APInt(32, 2));

    if(index == NULL)
        ret = ErrorV("Invalid Array Index in " + variable_1D_i->variableName);

    vector<Value*> array_index;
    array_index.push_back(Builder.getInt32(0));
    array_index.push_back(index);
    return Builder.CreateGEP(module->getNamedGlobal(variable_1D_i->variableName), array_index, variable_1D_i->variableName+"_IDX");
}

Value* CodeGen::visit(AST_variable_2D_ii *variable_2D_ii)
{
    
    return 0;
}

Value* CodeGen::visit(AST_variable_2D_iv *variable_2D_iv)
{
    
    return 0;
}

Value* CodeGen::visit(AST_variable_2D_vi *variable_2D_vi)
{
    
    return 0;
}

Value* CodeGen::visit(AST_variable_2D_vv *variable_2D_vv)
{
    
    return 0;
}
