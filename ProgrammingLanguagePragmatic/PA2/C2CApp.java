/*---------------------------------------------------------------------------------------------------------------------------------------------------

2014315382_정상훈
2014315327_권현준
PA#2 SOURCE TO SOURCE COMPILER
-----------------------------------------------------------------------------------------------------------------------------------------------------*/
// Import ANTLR runtime libraries
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.NotNull;
import org.antlr.v4.runtime.tree.*;

// Import JAVA util
import java.io.*;
import java.util.*;

// Class definition
class C2CListener extends CBaseListener 
{
	// Local variables decalre
	Stack<StringBuilder> out = new Stack<StringBuilder>();
	int nIndentCnt = 0; // Variable to count indent
	boolean isIndent = false; // Variable to check indent
	boolean isParenthesis = false;
	CParser parser;
	
	// Statements
	C2CListener(CParser parser)
	{
		out.push(new StringBuilder(""));
		this.parser = parser;
	}
	
	@Override	
	public void enterDirectiveDefinition(@NotNull CParser.DirectiveDefinitionContext ctx) 
	{
		if(ctx.getParent() instanceof CParser.IncListContext)
		{
			for (int i=0; i< ctx.getChildCount(); i++)
			{
				out.peek().append(
					ctx.getChild(i).getText()+"\n");
				System.out.println(
					"enterDirectiveDefinition : " + ctx.getChild(i).getText());
			}
		}
	}
	
	@Override	
	public void enterFunction(@NotNull CParser.FunctionContext ctx) 
	{ 
		for (int i=0; i < ctx.getChildCount(); i++)
		{
			System.out.println("enterFunction : " + ctx.getChild(i).getText());
			if (!(ctx.getChild(i) instanceof TerminalNode))
				continue;
			out.peek().append(ctx.getChild(i).getText());			
			if(!ctx.getChild(i).getText().equals("main") && !ctx.getChild(i).getText().equals("("))
			{
				out.peek().append(" ");
			}
			
			System.out.println("enterFunction if: " + ctx.getChild(i).getText());
		}
	}
	
	@Override	
	public void visitTerminal(TerminalNode node) 
	{
		if(node.getParent().getParent().getParent() instanceof CParser.ProgramContext==false)
		{
			
			String str = node.getText();

			isParenthesis = str.equals("(") ? true : isParenthesis;
			isParenthesis = str.equals(")") ? false : isParenthesis;


			if(checkPreNewLine(str))
				addNewLine();

			if(checkPreSpace(str))
				out.peek().append(" ");

			nIndentCnt -= str.equals("}") ? 1 : 0;

			addIndent();
			out.peek().append(node.getText());

			nIndentCnt += str.equals("{") ? 1 : 0;

			if(checkPostSpace(str))
				out.peek().append(" ");
			
			if(checkPostNewLine(str))
				addNewLine();
			
			System.out.println("visitTerminal if: " + str);
		}
	}

	private void addNewLine() // Add new line and change the value of 'isIndent'
	{
		out.peek().append("\n");
		isIndent = true;
	}

	private void addIndent() // Add indent according to 'isIndent' value
	{

		if(!isIndent)
			return ;

		isIndent = false;

		for(int i=0; i < nIndentCnt; i++)
		{
			out.peek().append("\t");	
		}
	}

	private boolean checkPreNewLine(String str) // If the '{' is come, we know there should be new line.
	{
		return str.equals("{");
	}
	
	private boolean checkPreSpace(String str) // Check pre space
	{
		return checkOperator(str);
	}

	private boolean checkPostSpace(String str) // Check post space
	{
		return str.equals("int")
			|| str.equals("char")
			|| str.equals("double")
			|| str.equals("float")
			|| str.equals("boolean")
			|| str.equals("short")
			|| str.equals("long")
			|| str.equals("unsigned")
			|| str.equals("return")
			|| str.equals("default")
			|| str.equals("case")
			|| str.equals("else")
			|| (isParenthesis && str.equals(";"))
			|| str.equals(",")
			|| checkOperator(str); 
	}

	private boolean checkPostNewLine(String str) // Check post new line
	{
		return str.equals("{")
			|| str.equals("}")
			|| str.equals("break;")
			|| (!isParenthesis && str.equals(";"))
			|| (!isParenthesis && str.equals(":"));
	}
	
	private boolean checkOperator(String str) // Check operator
	{
		return  str.equals("<=")
			|| str.equals(">=")
			|| str.equals("==")
			|| str.equals("!=")
			|| str.equals("+")
			|| str.equals("-")
			|| str.equals("*")
			|| str.equals("/")
			|| str.equals(">")
			|| str.equals("<")
			|| str.equals("=");
	}
	

}

public class C2CApp {
	public static void main(String[] args) throws IOException {
		// Input file		
		if (args.length != 1){
			System.err.println("Input C file");
			System.exit(1);
		}
		String filename = args[0];
		System.setIn(new FileInputStream(filename)); 
		InputStream input = System.in;

		// Get lexer
		CLexer lexer = new CLexer(new ANTLRInputStream(input));
		// Get a list of matched tokens
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		// Pass tokens to parser
		CParser parser = new CParser(tokens);
		// Walk parse-tree and attach our listener
		ParseTreeWalker walker = new ParseTreeWalker();
		C2CListener listener = new C2CListener(parser);
		// walk from the root of parse tree
		walker.walk(listener, parser.program());
	
		// Output file
		FileOutputStream output = new FileOutputStream(new File("output_"+args[0]));
		System.out.println("Output file name:  output_"+args[0]);
		output.write(listener.out.peek().toString().getBytes());
		output.flush();
		output.close();
	}
} 
