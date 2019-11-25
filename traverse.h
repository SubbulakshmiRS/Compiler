
class Traverse;

class Traverse : public Visitor
{
public:
     void visit(AST_stmts * stmts) ;

     void visit(AST_function_decl *function_decl) ;
     void visit(AST_variable_decl *variable_decl) ;
     void visit(AST_semicolon* semicolon);
     void visit(AST_keyword* keyword);
     void visit(AST_assignStmt_old *assignStmt_old) ;
     void visit(AST_assignStmt_new *assignStmt_new) ;
     void visit(AST_functionCall_noargs *functionCall_noargs) ;
     void visit(AST_functionCall_args *functionCall_args) ;

     void visit(AST_ifWEStmt *ifWEStmt) ;
     void visit(AST_ifElseStmt *ifElseStmt) ;
     void visit(AST_whileStmt *whileStmt) ;
     void visit(AST_forStmt *forStmt) ;

     void visit(AST_returnStmt *returnStmt) ;
     void visit(AST_inputStmt *inputStmt) ;
     void visit(AST_outputStmt *outputStmt) ;
     void visit(AST_expr_unary *expr_unary) ;
     void visit(AST_expr_binary *expr_binary) ;
     void visit(AST_expr_ternary *expr_ternary) ;    


     void visit(AST_paramD_list *paramD_list ) ;
     void visit(AST_param_list *param_list) ;
     void visit(AST_paramD *paramD ) ;

     void visit(AST_int *intVal) ;
     void visit(AST_float *floatVal) ;
     void visit(AST_bool* boolVal) ;
     void visit(AST_variable_0D *variable_0D) ;
     void visit(AST_variable_1D_v *variable_1D_v) ;
     void visit(AST_variable_1D_i *variable_1D_i) ;
     void visit(AST_variable_2D_ii *variable_2D_ii) ;
     void visit(AST_variable_2D_iv *variable_2D_iv) ;
     void visit(AST_variable_2D_vi *variable_2D_vi) ;
     void visit(AST_variable_2D_vv *variable_2D_vv) ;
};