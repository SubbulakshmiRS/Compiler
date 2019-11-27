
class Traverse;

class Traverse : public Visitor
{
public:
     Literal visit(AST_stmts * stmts) ;

     Literal visit(AST_function_decl *function_decl) ;
     Literal visit(AST_variable_decl *variable_decl) ;
     Literal visit(AST_semicolon* semicolon);
     Literal visit(AST_keyword* keyword);
     Literal visit(AST_assignStmt_old *assignStmt_old) ;
     Literal visit(AST_assignStmt_new *assignStmt_new) ;
     Literal visit(AST_functionCall_noargs *functionCall_noargs) ;
     Literal visit(AST_functionCall_args *functionCall_args) ;

     Literal visit(AST_ifWEStmt *ifWEStmt) ;
     Literal visit(AST_ifElseStmt *ifElseStmt) ;
     Literal visit(AST_whileStmt *whileStmt) ;
     Literal visit(AST_forStmt *forStmt) ;

     Literal visit(AST_returnStmt *returnStmt) ;
     Literal visit(AST_inputStmt *inputStmt) ;
     Literal visit(AST_outputStmt *outputStmt) ;
     Literal visit(AST_expr_unary *expr_unary) ;
     Literal visit(AST_expr_binary *expr_binary) ;
     Literal visit(AST_expr_ternary *expr_ternary) ;    


     Literal visit(AST_paramD_list *paramD_list ) ;
     Literal visit(AST_param_list *param_list) ;
     Literal visit(AST_paramD *paramD ) ;

     Literal visit(AST_int *intVal) ;
     Literal visit(AST_float *floatVal) ;
     Literal visit(AST_bool* boolVal) ;
     Literal visit(AST_variable_0D *variable_0D) ;
     Literal visit(AST_variable_1D_v *variable_1D_v) ;
     Literal visit(AST_variable_1D_i *variable_1D_i) ;
     Literal visit(AST_variable_2D_ii *variable_2D_ii) ;
     Literal visit(AST_variable_2D_iv *variable_2D_iv) ;
     Literal visit(AST_variable_2D_vi *variable_2D_vi) ;
     Literal visit(AST_variable_2D_vv *variable_2D_vv) ;
};