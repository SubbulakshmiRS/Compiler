
class CodeGen;
Value *ErrorV(const char *str);

class CodeGen : public Visitor
{
private:
    Value * ret;
    Function * main_function;
    int load_variable;
    string str_;
    
public:
    CodeGen();
    void dump();
     Value* visit(AST_stmts * stmts) ;

     Value* visit(AST_function_decl *function_decl) ;
     Value* visit(AST_variable_decl *variable_decl) ;
     Value* visit(AST_semicolon* semicolon);
     Value* visit(AST_keyword* keyword);
     Value* visit(AST_assignStmt_old *assignStmt_old) ;
     Value* visit(AST_assignStmt_new *assignStmt_new) ;
     Value* visit(AST_functionCall_noargs *functionCall_noargs) ;
     Value* visit(AST_functionCall_args *functionCall_args) ;

     Value* visit(AST_ifWEStmt *ifWEStmt) ;
     Value* visit(AST_ifElseStmt *ifElseStmt) ;
     Value* visit(AST_whileStmt *whileStmt) ;
     Value* visit(AST_forStmt *forStmt) ;

     Value* visit(AST_returnStmt *returnStmt) ;
     Value* visit(AST_inputStmt *inputStmt) ;
     Value* visit(AST_outputStmt *outputStmt) ;
     Value* visit(AST_expr_unary *expr_unary) ;
     Value* visit(AST_expr_binary *expr_binary) ;
     Value* visit(AST_expr_ternary *expr_ternary) ;    


     Value* visit(AST_paramD_list *paramD_list ) ;
     Value* visit(AST_param_list *param_list) ;
     Value* visit(AST_paramD *paramD ) ;

     Value* visit(AST_int *intVal) ;
     Value* visit(AST_float *floatVal) ;
     Value* visit(AST_bool* boolVal) ;
     Value* visit(AST_variable_0D *variable_0D) ;
     Value* visit(AST_variable_1D_v *variable_1D_v) ;
     Value* visit(AST_variable_1D_i *variable_1D_i) ;
     Value* visit(AST_variable_2D_ii *variable_2D_ii) ;
     Value* visit(AST_variable_2D_iv *variable_2D_iv) ;
     Value* visit(AST_variable_2D_vi *variable_2D_vi) ;
     Value* visit(AST_variable_2D_vv *variable_2D_vv) ;
};