// Generated from AutoC.g4 by ANTLR 4.5.3
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link AutoCParser}.
 */
public interface AutoCListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link AutoCParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(AutoCParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(AutoCParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#incList}.
	 * @param ctx the parse tree
	 */
	void enterIncList(AutoCParser.IncListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#incList}.
	 * @param ctx the parse tree
	 */
	void exitIncList(AutoCParser.IncListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#directiveDefinition}.
	 * @param ctx the parse tree
	 */
	void enterDirectiveDefinition(AutoCParser.DirectiveDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#directiveDefinition}.
	 * @param ctx the parse tree
	 */
	void exitDirectiveDefinition(AutoCParser.DirectiveDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#declList}.
	 * @param ctx the parse tree
	 */
	void enterDeclList(AutoCParser.DeclListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#declList}.
	 * @param ctx the parse tree
	 */
	void exitDeclList(AutoCParser.DeclListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#funcList}.
	 * @param ctx the parse tree
	 */
	void enterFuncList(AutoCParser.FuncListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#funcList}.
	 * @param ctx the parse tree
	 */
	void exitFuncList(AutoCParser.FuncListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(AutoCParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(AutoCParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#identList}.
	 * @param ctx the parse tree
	 */
	void enterIdentList(AutoCParser.IdentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#identList}.
	 * @param ctx the parse tree
	 */
	void exitIdentList(AutoCParser.IdentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(AutoCParser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(AutoCParser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(AutoCParser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(AutoCParser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(AutoCParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(AutoCParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#paramList}.
	 * @param ctx the parse tree
	 */
	void enterParamList(AutoCParser.ParamListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#paramList}.
	 * @param ctx the parse tree
	 */
	void exitParamList(AutoCParser.ParamListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#compoundStmt}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStmt(AutoCParser.CompoundStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#compoundStmt}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStmt(AutoCParser.CompoundStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void enterStmtList(AutoCParser.StmtListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void exitStmtList(AutoCParser.StmtListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(AutoCParser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(AutoCParser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#assignStmt}.
	 * @param ctx the parse tree
	 */
	void enterAssignStmt(AutoCParser.AssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#assignStmt}.
	 * @param ctx the parse tree
	 */
	void exitAssignStmt(AutoCParser.AssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#assign}.
	 * @param ctx the parse tree
	 */
	void enterAssign(AutoCParser.AssignContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#assign}.
	 * @param ctx the parse tree
	 */
	void exitAssign(AutoCParser.AssignContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void enterCallStmt(AutoCParser.CallStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void exitCallStmt(AutoCParser.CallStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#call}.
	 * @param ctx the parse tree
	 */
	void enterCall(AutoCParser.CallContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#call}.
	 * @param ctx the parse tree
	 */
	void exitCall(AutoCParser.CallContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#retStmt}.
	 * @param ctx the parse tree
	 */
	void enterRetStmt(AutoCParser.RetStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#retStmt}.
	 * @param ctx the parse tree
	 */
	void exitRetStmt(AutoCParser.RetStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(AutoCParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(AutoCParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void enterForStmt(AutoCParser.ForStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#forStmt}.
	 * @param ctx the parse tree
	 */
	void exitForStmt(AutoCParser.ForStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(AutoCParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(AutoCParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#switchStmt}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStmt(AutoCParser.SwitchStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#switchStmt}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStmt(AutoCParser.SwitchStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#caseList}.
	 * @param ctx the parse tree
	 */
	void enterCaseList(AutoCParser.CaseListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#caseList}.
	 * @param ctx the parse tree
	 */
	void exitCaseList(AutoCParser.CaseListContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(AutoCParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(AutoCParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link AutoCParser#argList}.
	 * @param ctx the parse tree
	 */
	void enterArgList(AutoCParser.ArgListContext ctx);
	/**
	 * Exit a parse tree produced by {@link AutoCParser#argList}.
	 * @param ctx the parse tree
	 */
	void exitArgList(AutoCParser.ArgListContext ctx);
}