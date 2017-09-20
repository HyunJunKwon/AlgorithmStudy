// Generated from C.g4 by ANTLR 4.5.3
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CParser}.
 */
public interface CListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(CParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(CParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#incList}.
	 * @param ctx the parse tree
	 */
	void enterIncList(CParser.IncListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#incList}.
	 * @param ctx the parse tree
	 */
	void exitIncList(CParser.IncListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#directiveDefinition}.
	 * @param ctx the parse tree
	 */
	void enterDirectiveDefinition(CParser.DirectiveDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#directiveDefinition}.
	 * @param ctx the parse tree
	 */
	void exitDirectiveDefinition(CParser.DirectiveDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#declList}.
	 * @param ctx the parse tree
	 */
	void enterDeclList(CParser.DeclListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#declList}.
	 * @param ctx the parse tree
	 */
	void exitDeclList(CParser.DeclListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#funcList}.
	 * @param ctx the parse tree
	 */
	void enterFuncList(CParser.FuncListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#funcList}.
	 * @param ctx the parse tree
	 */
	void exitFuncList(CParser.FuncListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(CParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(CParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#identList}.
	 * @param ctx the parse tree
	 */
	void enterIdentList(CParser.IdentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#identList}.
	 * @param ctx the parse tree
	 */
	void exitIdentList(CParser.IdentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(CParser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(CParser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(CParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(CParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#paramList}.
	 * @param ctx the parse tree
	 */
	void enterParamList(CParser.ParamListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#paramList}.
	 * @param ctx the parse tree
	 */
	void exitParamList(CParser.ParamListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#compoundStmt}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStmt(CParser.CompoundStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#compoundStmt}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStmt(CParser.CompoundStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void enterStmtList(CParser.StmtListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void exitStmtList(CParser.StmtListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(CParser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(CParser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#assignStmt}.
	 * @param ctx the parse tree
	 */
	void enterAssignStmt(CParser.AssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#assignStmt}.
	 * @param ctx the parse tree
	 */
	void exitAssignStmt(CParser.AssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#assign}.
	 * @param ctx the parse tree
	 */
	void enterAssign(CParser.AssignContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#assign}.
	 * @param ctx the parse tree
	 */
	void exitAssign(CParser.AssignContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void enterCallStmt(CParser.CallStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void exitCallStmt(CParser.CallStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#call}.
	 * @param ctx the parse tree
	 */
	void enterCall(CParser.CallContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#call}.
	 * @param ctx the parse tree
	 */
	void exitCall(CParser.CallContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#retStmt}.
	 * @param ctx the parse tree
	 */
	void enterRetStmt(CParser.RetStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#retStmt}.
	 * @param ctx the parse tree
	 */
	void exitRetStmt(CParser.RetStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(CParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(CParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void enterForStmt(CParser.ForStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void exitForStmt(CParser.ForStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(CParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(CParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#switchStmt}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStmt(CParser.SwitchStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#switchStmt}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStmt(CParser.SwitchStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#caseList}.
	 * @param ctx the parse tree
	 */
	void enterCaseList(CParser.CaseListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#caseList}.
	 * @param ctx the parse tree
	 */
	void exitCaseList(CParser.CaseListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(CParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(CParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link CParser#argList}.
	 * @param ctx the parse tree
	 */
	void enterArgList(CParser.ArgListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CParser#argList}.
	 * @param ctx the parse tree
	 */
	void exitArgList(CParser.ArgListContext ctx);
}