/*-----------------------------------------------------------------------------------------------------------------------------------------
2014315382_정상훈
2014315327_권현준

PA#3 AUTO C TO C 

Description:
visitorForAuto 클래스는 위에서 차례대로 분석하면서 auto가 나오면 ';'가 나오기 전 변수명은 auto변수라고 bool값으로 알려주고,
void로 가정합니다. 그리고 추후 '='연산자를 통해 자료형을 알게 되면 auto를 각각의 맞는 자료형으로 변환시키고
bool값을 변경시킵니다. 그리고 이렇게 매칭된 결과를 가지고 두 번 나오는 visitTerminal 클래스에서 indent하여 출력하게됩니다.

-------------------------------------------------------------------------------------------------------------------------------------------*/



// Import ANTLR runtime libraries
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.NotNull;
import org.antlr.v4.runtime.tree.*;

// Import JAVA util
import java.io.*;
import java.util.*;




// Define class
class AUTOC2C  // Define class of class to access input code twice
{

	// Local variabl declare
	HashMap<String, String> vars = new HashMap<String, String>(); // To change character 'auto'
	HashMap<Integer, HashMap<String , String>> varList = new HashMap<Integer, HashMap<String , String>>();

	// Define class
	class VisitorForAuto extends AutoCBaseVisitor<Integer>
   	{
		// Local variables declare
      		Stack<String> CheckParenthesis = new Stack<String>(); // Stack for checking parenthesis
      		Stack<String> CheckFunction = new Stack<String>(); // Stack for cheking function
      		Stack<Integer> CheckFunction2 = new Stack<Integer>();
      		String OperationName = "default";              
      		String curVarName = "none";
      		String curFuncType = "none";
      		String curFuncName = "none"; // Each variable stands for varialble name, function name etc... in example code
      		boolean NEWLINE = false; // To find the need of NEWLINE
      		boolean VOIDFUNC = false; // To find void function 
      		boolean ISAUTOTYPE = false; // To detect  'auto'
      		boolean ISAUTOVAR = false;  // To find 'auto'
      		boolean ISAUTOVARFIX = false; // To finalize 'auto' to some type
      		boolean ISAUTOFUNCFIX = false;  
      		int cntWord = 0; // To count words on one line
      		int cntIndent = 0; // To count indents
      		int type = 0; // To distinguish a word into symbol types, each symbol's informaion is located in AutoCLexer.tokens
      		int cntSemi = 0; // To count semicolon(;) for 'for operation statements'
      		int cntFunc = 0; // To count functions


		// Statements
		VisitorForAuto()
		{
			CheckFunction.push("GROUND");
			CheckFunction2.push(cntIndent);
		}

		//@Override public T visitProgram(AutoCParser.ProgramContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitIncList(AutoCParser.IncListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitDirectiveDefinition(AutoCParser.DirectiveDefinitionContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitDeclList(AutoCParser.DeclListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitFuncList(AutoCParser.FuncListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitDeclaration(AutoCParser.DeclarationContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitIdentList(AutoCParser.IdentListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitIdentifier(AutoCParser.IdentifierContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitInitializer(AutoCParser.InitializerContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitFunction(AutoCParser.FunctionContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitParamList(AutoCParser.ParamListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitCompoundStmt(AutoCParser.CompoundStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitStmtList(AutoCParser.StmtListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitStmt(AutoCParser.StmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitAssignStmt(AutoCParser.AssignStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitAssign(AutoCParser.AssignContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitCallStmt(AutoCParser.CallStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitCall(AutoCParser.CallContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitRetStmt(AutoCParser.RetStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitWhileStmt(AutoCParser.WhileStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitForStmt(AutoCParser.ForStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitIfStmt(AutoCParser.IfStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitSwitchStmt(AutoCParser.SwitchStmtContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitCaseList(AutoCParser.CaseListContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitExpr(AutoCParser.ExprContext ctx) { return visitChildren(ctx); }
		/*
		 * {@inheritDoc}
		 *
		 * <p>The default implementation returns the result of calling
		 * {@link #visitChildren} on {@code ctx}.</p>
		 */
		//@Override public T visitArgList(AutoCParser.ArgListContext ctx) { return visitChildren(ctx); }




		@Override public Integer visitFunction(@NotNull AutoCParser.FunctionContext ctx) 
		{
			// Statements
         		for (int i = 0; i < ctx.getChildCount(); i++)
            			if (ctx.getChild(i) instanceof TerminalNode)
				{
               				String text = ctx.getChild(i).getText();
               				cntFunc++; // Whenever visit function, plus function counter
              				if(cntFunc == 1)
                  				curFuncType = text;
					else if(cntFunc == 2 && !(vars.containsKey(text)))
					{
                  				if(curFuncType.equals("auto"))
						{
                     					ISAUTOTYPE = true; // Notify that 'auto' is detected
                     					curFuncType = "void"; // Assume that type 'auto' is 'void' to finalize later
                  				}
                  				CheckFunction.push(text);
                  				CheckFunction2.push(cntIndent);
						//System.out.println("text " + text + "curFuncType " + curFuncType);
						HashMap vars = varList.get(cntIndent);
						if(vars == null){
							vars = new HashMap<String, String>();
						}
                 				vars.put(text,curFuncType);
					
               				}
					else if(text.equals(")"))
					{
                  				OperationName = CheckFunction.peek();
                  				ISAUTOTYPE = false;
                  				cntFunc = 0;
               				}
            			}
         		return visitChildren(ctx);
      		}	
     



      		@Override public Integer visitTerminal(TerminalNode node) 
		{
			// Statements
         		if(node.getParent().getParent().getParent() instanceof AutoCParser.ProgramContext == false)
			{
            			type = node.getSymbol().getType();
            			String text = node.getText();
                           	cntWord++;
           		       //System.out.println(text + " " + type); 
            			switch(type) // Sorting word according to type and type is defined in AutoCLexer.tokens
				{
            			case 1: // ;
               				ISAUTOVAR = false;
               				ISAUTOVARFIX = false;
               				ISAUTOFUNCFIX = false;
               				if(cntSemi != 0)
                  				cntSemi--;
               				break;
            			case 8: // {
               				ISAUTOVAR = false;
               				ISAUTOVARFIX = false;
               				if(cntWord == 1 && cntIndent == 0)
                  				VOIDFUNC = true;
               				CheckParenthesis.push(OperationName);
                  			cntIndent--;
               				OperationName = "default";
               				break;
            			case 9: // }
               				cntIndent--;
               				if(cntWord == 1 && cntIndent == 0)
                  				VOIDFUNC = true;
               				if(CheckFunction2.peek().equals(cntIndent))
					{
                  				CheckFunction.pop();
                  				CheckFunction2.pop();
               				}
               				if(CheckParenthesis.peek().equals("do"))
					{
                  				CheckParenthesis.pop();
                  				CheckParenthesis.push("do-check");
               				}
					else if(!CheckParenthesis.peek().equals("default"))
                  				CheckParenthesis.pop();
               				break;
            			case 11: // while()
               				if(CheckParenthesis.peek().equals("do-check"))
                  				CheckParenthesis.pop();
					else
						OperationName = "while";
               				break;
            			case 12: // do ... while()
               				OperationName = "do";
               				break;
            			case 13: // for
               				OperationName = "for";
               				cntSemi += 2;
               				break;
            			case 14: // if
               				OperationName = "if";
               				break;
            			case 15: // else
               				OperationName = "else";
              		 		break;
            			case 16: // switch
               				OperationName = "switch";
               				break;
            			case 17: // case
              	 			cntIndent--;
               				break;
            			case 18: // :
               				cntIndent++;
               				break;
            			case 19: // break;
               				break;
            			case 20: // default
               				cntIndent--;
               				break;
            			case 2:   // , add space
               				break;
            			case 10: //return
               				if(vars.containsKey(CheckFunction.peek()) && vars.get(CheckFunction.peek()).equals("void"))
                  				ISAUTOFUNCFIX = true;
               				break;
            			case 22: //type(int, float, etc.)
               				if(text.equals("auto"))
                  				ISAUTOVAR = true;
               				break;
            			case 5: // =
               				ISAUTOVARFIX = true;
               				break;
            			case 25: // +, -
            			case 26: // *, /
            			case 27: // >, <, >=, <=
            			case 28: // ==, !=
               				break;
				case 29: // variables
					if(ISAUTOVAR && (!ISAUTOVARFIX) && (!vars.containsKey(text)))
					{
						//System.out.println("text " + text +  " 29"); //hoony
						vars.put(text, "none");
						curVarName = text;
					}
					else if(vars.containsKey(text) && vars.get(text).equals("none"))
					{
						ISAUTOVAR = true;
						curVarName = text;
					}
					else if(ISAUTOFUNCFIX){
						//System.out.println( "CheckFunction.peek() " + CheckFunction.peek() +  " 29"); //hoony
						vars.put(CheckFunction.peek(), vars.get(text));
					}
					break;
				case 23: // string
					if(ISAUTOVAR && ISAUTOVARFIX){
						//System.out.println("curVarName " + curVarName +  " 23"); //hoony
						vars.put(curVarName, "char");
					}
					else if(ISAUTOFUNCFIX){
						//System.out.println("CheckFunction.peek() " + CheckFunction.peek() +  " 23"); //hoony
						vars.put(CheckFunction.peek(), "String");
					}
					break;
				case 30: // integer
					if(ISAUTOVAR && ISAUTOVARFIX){
						//System.out.println("curVarName " + curVarName +  " 30"); //hoony
						vars.put(curVarName, "int");
					}
					else if(ISAUTOFUNCFIX){
						//System.out.println("CheckFunction.peek() "  + CheckFunction.peek() +  " 30"); //hoony
						vars.put(CheckFunction.peek(), "int");
					}
					break;
				case 31: // float
					if(ISAUTOVAR && ISAUTOVARFIX){
						//System.out.println("curVarName " + curVarName +  " 31"); //hoony
						vars.put(curVarName, "float");
					}
					else if(ISAUTOFUNCFIX){
						//System.out.println("CheckFunction.peek() " + CheckFunction.peek() +  " 31"); //hoony
						vars.put(CheckFunction.peek(), "float");
					}
					break;
				}


            			// After sorting, if a word is first on its line, then print '\t' characters to the front of the word
            			if(type == 8)
				{
              	 			cntIndent++;
               				if(cntWord == 1 && CheckParenthesis.peek().equals("default"))
                  			cntIndent++;
            			}
           
            			// By conditions, print out a word and '\n' or space appropriately
            			if(NEWLINE)
               				cntWord = 0;
            		}
         		return null;
      		}
     
   	}
  
	class C2CVisitor extends AutoCBaseVisitor<Integer> // To print out
   	{
		// Statements
      		Stack<StringBuilder> out = new Stack<StringBuilder>();
      		Stack<String> CheckParenthesis = new Stack<String>();   
      		Stack<String> CheckFunction = new Stack<String>();
      		String OperationName = "default";               
      		boolean NEWLINE = false; 
      		boolean ISBINARY = false; // To check whether it is binary operator
      		boolean ISONESPACE = false; // TO find the need of space after one word
      		boolean VOIDFUNC = false;
      		boolean ISAUTOCHECK = false;
     		int cntWord = 0;   
      		int cntIndent = 0;      
      		int type = 0;      
      		int cntSemi = 0;     
      		int cntFunc = 0; 

     
     
        
      		C2CVisitor()
		{
         		System.out.println("C2CVisitor \n");
			System.out.println("AUTOC2C PROGRAM IS EXECUTED... \n\n");
         		out.push(new StringBuilder(""));
         		CheckFunction.push("GROUND");
      		}


      


		@Override public Integer visitDirectiveDefinition(@NotNull AutoCParser.DirectiveDefinitionContext ctx) 
		{
         		if(ctx.getParent() instanceof AutoCParser.IncListContext)
            			for (int i = 0; i < ctx.getChildCount(); i++)
					out.peek().append(ctx.getChild(i).getText()+"\n");   // Print IncList
            		return visitChildren(ctx);
      		}
      



		@Override public Integer visitFunction(@NotNull AutoCParser.FunctionContext ctx) 
		{
         		for (int i = 0; i < ctx.getChildCount(); i++)
            			if (ctx.getChild(i) instanceof TerminalNode)
				{
               				String text = ctx.getChild(i).getText();
               				cntFunc++;
              
               				if(cntFunc == 2)
					{
                  				CheckFunction.push(text);
                  				if(!vars.containsKey(text))
                    	 			cntIndent--;
               				}	
					else if(text.equals(")"))
					{
                  				OperationName = CheckFunction.peek();
                  				cntFunc = 0;
               				}
               				if(!VOIDFUNC)
                  				out.peek().append(text + " ");   // Print Function without CompoundStmt
            			}		
         		return visitChildren(ctx);
      		}
      


		@Override public Integer visitTerminal(TerminalNode node) 
		{
         		if(node.getParent().getParent().getParent() instanceof AutoCParser.ProgramContext == false)
			{
            			type = node.getSymbol().getType();
            			String text = node.getText();
                       
            			cntWord++;
           
            			
            			switch(type) 
				{
            			case 1: // ;
               				if(cntSemi == 0)
						NEWLINE = true;
               				else
					{
                  				cntSemi--;
                  				ISONESPACE = true;
               				}
               				break;
            			case 8: // {
               				if(cntWord == 1 && cntIndent == 0)
						VOIDFUNC = true;
               				CheckParenthesis.push(OperationName);
               				OperationName = "default";
               				if(cntIndent > 0 && cntWord > 0 && !(CheckParenthesis.peek().equals("else")))
						out.peek().append(' ');
               				NEWLINE = true;
               				break;
            			case 9: // }
               				cntIndent--;
               				if(cntWord == 1 && cntIndent == 0)
						VOIDFUNC = false;
               				if(CheckParenthesis.peek().equals("do"))
					{
                  				CheckParenthesis.pop();
                  				CheckParenthesis.push("do-check");
                  				ISONESPACE = true;
               				}
					else if(!CheckParenthesis.peek().equals("default"))
					{
                  				CheckParenthesis.pop();
                  				NEWLINE = true;
               				}
					else
						NEWLINE = true;
               				break;
            			case 11: // while()
               				ISONESPACE = true;
               				if(CheckParenthesis.peek().equals("do-check"))
						CheckParenthesis.pop();
               				else
						OperationName = "while";
               				break;
            			case 12: // do ... while()
               				OperationName = "do";
               				break;
            			case 13: // for
               				ISONESPACE = true;
               				OperationName = "for";
               				cntSemi += 2;
               				break;
            			case 14: // if
               				ISONESPACE = true;
               				OperationName = "if";
               				break;
            			case 15: // else
               				ISONESPACE = true;
               				OperationName = "else";
               				break;
            			case 16: // switch
               				ISONESPACE = true;
               				OperationName = "switch";
               				break;
            			case 17: // case
               				ISONESPACE = true;
               				cntIndent--;
               				break;
           	 		case 18: // :
               				NEWLINE = true;
               				cntIndent++;
               				break;
           	 		case 19: // break;
               				NEWLINE = true;
               				break;
            			case 20: // default
               				cntIndent--;
               				break;
            			case 2:   // , add space
            			case 10: //return
            			case 22: //type(int, float, etc.)
               				if(text.equals("auto"))
                  				ISAUTOCHECK = true;
               				ISONESPACE = true;
               				break;
            			case 5: // =
            			case 25: // +, -
            			case 26: // *, /
            			case 27: // >, <, >=, <=
            			case 28: // ==, !=
               				ISBINARY = true;
               				break;
            			case 29: // variables
               				if(ISAUTOCHECK)
					{
                  				int index = out.peek().lastIndexOf("auto");
                  				out.peek().replace(index, index+4, vars.get(text));
                  				ISAUTOCHECK = false;
               				}
              	 			break;
				default:
					break;
            			}
           

            			// After sorting, if a word is first on its line, then print 'indent' characters to the front of the word
            			if(cntWord == 1)
				{
               				for(int i = 0; i < cntIndent; i++)
                  			out.peek().append('\t');
               			}
            			if(type == 8)
					cntIndent++;
            			
           
           
            			// According to  conditions, print out a word and 'NEWLINE' or space appropriately
            			if(NEWLINE)
				{


               				NEWLINE = false;
               				cntWord = 0;
               				out.peek().append(text + '\n');
            			}
				else if(ISBINARY)
				{


               				ISBINARY = false;
               				out.peek().append(' ' + text + ' ');
            			}
				else if(ISONESPACE)
				{
               				ISONESPACE = false;
               				out.peek().append(text + ' ');
            			}
				else
					out.peek().append(text);
            	         
         		}
         		return null;
      		}
     
	}
  

}


public class AutoC2CApp 
{
	// Statements
  	public static void main(String[] args) throws IOException 
	{
      		// Input file     
      		if (args.length != 1)
		{
         		System.err.println("Input C file");
         		System.exit(1);
      		}
      		String filename = args[0];
      		System.setIn(new FileInputStream(filename));
      		InputStream input = System.in;

      		// Get lexer
      		AutoCLexer lexer = new AutoCLexer(new ANTLRInputStream(input));
     
      		// Get a list of matched tokens
      		CommonTokenStream tokens = new CommonTokenStream(lexer);
     
      		// Pass tokens to parser
      		AutoCParser parser = new AutoCParser(tokens);
     
      		// ParseTree
      		ParseTree tree = parser.program();
     
		// our visitor
		AUTOC2C cta = new AUTOC2C();

		AUTOC2C.VisitorForAuto visitorForAuto = cta.new VisitorForAuto(); // Mapping auto to each data type

		AUTOC2C.C2CVisitor visitor = cta.new C2CVisitor(); // Print result 



		// visit AutoCParser
      		visitorForAuto.visit(tree);
      		visitor.visit(tree);
      	  
      		// Output file
      		FileOutputStream output = new FileOutputStream(new File("output_"+args[0]));
      		System.out.println("Output file name:  output_"+args[0]);
      		output.write(visitor.out.peek().toString().getBytes());
      		output.flush();
      		output.close();
   	}	
} 
