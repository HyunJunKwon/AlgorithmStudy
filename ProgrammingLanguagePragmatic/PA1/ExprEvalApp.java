/*---------------------------------------------------------------------------------------------------------------------------------
PA#1
2014315327_권현준
2014315382_정상훈
antlr 계산기
----------------------------------------------------------------------------------------------------------------------------------*/

// import ANTLR runtime libraries
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

// import Java Map Libs
import java.util.HashMap;
import java.util.Map;

// import Java List Libs
import java.util.ArrayList;
import java.util.LinkedList;

// import Java Queue Libs
import java.util.Queue;

// import Java Stack Libs
import java.util.Stack;

// import Java console IO
import java.io.Console;
import java.io.IOException;

// import Java File I/O
import java.io.FileReader;
import java.io.FileNotFoundException;


class EvalListener extends ExprBaseListener 
{

	private boolean isAssn = false;
	private boolean isError = false;
	private String strErrorMsg;
	
	// Hash-map for variables' integer value for assignment
	Map<String, Double> vars = new HashMap<String, Double>(); 

   	// Stack for expression tree evaluation
   	Stack<Double> evalStack = new Stack<Double>();
   	
	// Stack for operators (+-*/) in shunting-yard algorithm 
   	Stack<String> opStack = new Stack<String>();

   	// Queue to save all the calculation
   	Queue<String> Q = new LinkedList<String>();

   	// ArrayList to save resutl data
   	ArrayList<String> res = new ArrayList<String> ();

   	// To get priority of the operator
   	public int getPriority (String input) 
	{
		if (input.equals("+") || input.equals("-"))
			return 1;
		else if (input.equals("*") || input.equals("/"))
			return 2;
		else
			return 3;
	}

	// To check operator whether it is operator or not
   	public boolean opChecker (String t) 
	{
		switch (t) 
		{
	   	case "+" :
	   	case "-" :
	   	case "*" :
	  	case "/" :
			return true;

	   	default:
			return false;
		}
   	}

	// To calculate the result
   	public double calculator (double a, double b, String c) 
	{
		
		if (c.equals("+"))
			return (a+b);
		if (c.equals("-"))
			return (a-b);
		if (c.equals("*"))
			return (a*b);
		else 
		{
			return (a/b);		
		}
	}

   	@Override
   	public void exitProg(ExprParser.ProgContext ctx) 
	{
	      	System.out.println("exitProg: ");
		moveOp();
		calculate(); // When exit program, just move operators and calculate the result
	}
   
  	@Override
   	public void exitExpr(ExprParser.ExprContext ctx) 
	{
	      	System.out.println("exitExpr: ");
	}

   	@Override
   	public void enterAssn(ExprParser.AssnContext ctx)  
	{
		String strId = ctx.ID().getText();
		String strValue = ctx.INT().getText();
		Double value = 0.0d;
	
		try // To catch exception case
		{
			value = (vars.get(strValue) == null) ? new Double(strValue) : vars.get(strValue);
		}
		catch(NumberFormatException e)
		{
			isError = true;
			strErrorMsg = "NumberFormatException" + e.getMessage();
		}		

		vars.put(strId, value);
		System.out.println("enterAssn: " + strId + " " + value);
		isAssn = true;
	}
   
   	@Override
   	public void exitAssn(ExprParser.AssnContext ctx) 
	{
		System.out.println("exitAssn");
	   	isAssn = false;
	}

    
   	@Override 
   	public void visitTerminal(TerminalNode node) 
	{
	      	String s = node.getText();
	      	String temp;

		System.out.println("Get character : " + s);
		switch(s) 
		{
		case "+": 
		case "-":
		case "*": 
		case "/":
			checkOperation(s);
			break;
		case "(":
			opStack.push(s);
			break;
		case ")":
			checkRightparenthesis(s); // Checking the right parenthesis, we can know about the end of expresions
			break;
		case ";":
			break;
		default:
			if(isAssn)
				break;

		if (s.matches("[0-9]+")) 
		{ 
             		Q.add(s);
	     		System.out.println(s + " is go into the Queue");
	     	} 
		else 
		{ 
			Double value = vars.get(s);
			if(value == null) 
				return;
			Q.add(value.toString());
		}
	}
   }

	private void checkOperation(String s)
	{
		String temp;
		while(!opStack.isEmpty()) // According to order of priority, check operator
		{
			temp = opStack.peek();
			if (getPriority(s) <= getPriority(temp)) 
			{
				if(temp.equals("("))
					break;
				Q.add(opStack.pop());	
			}
			else
				break;
		}
		System.out.println("push = " + s);
		opStack.push(s);
	}

	private void checkRightparenthesis(String s)
	{
		// Checking right parenthesis
		String temp;
		while(!opStack.isEmpty())
		{
			temp = opStack.peek();
			if(temp.equals("("))
			{
				opStack.pop();
				break;
			}
			else
				Q.add(opStack.pop());		
		}
	}
	
	private void calculate()
	{
		if(isError)
		{
			System.err.println(strErrorMsg);
			return ;		
		}
		
		System.out.println("calculate");
		
		String temp;
		while (!Q.isEmpty()) 
		{
			temp = Q.poll();
			if (!opChecker(temp)) 
			{
				Double value;
				try
				{
					value = Double.parseDouble(temp);
				}
				catch(NumberFormatException e)
				{
					System.err.println("NumberFormatException : " + e.getMessage());
					return;	
				}
		    		evalStack.push(value);
			} 
			else 
			{
		     		double a = evalStack.pop();
		     		double b = evalStack.pop();
				double result = 0.0d;
				try
				{
		     			result = calculator(b, a, temp);
				}
				catch(ArithmeticException e)
				{
					System.err.println("ArithmeticException : " + e.getMessage());
					return;				
				}
				catch(Exception e)
				{
					System.err.println("Exception : " + e.getMessage());
					return;				
				}
		     		evalStack.push(result);
			}
	  	}
		System.out.println("The result is: " + evalStack.pop());
	  	
	}

	private void moveOp()
	{
		while(!opStack.isEmpty())
		{
			Q.add(opStack.pop());
		}
	}
}

public class ExprEvalApp 
{
   public static void main(String[] args) throws IOException 
	{
	      System.out.println("** Expression Eval w/ antlr-listener **");
		String input = "";
		if(args.length > 0)
		{
			byte[] b = new byte[1024];
			FileReader in = null;
			try
			{
				in = new FileReader(args[0]);
				StringBuffer buffer = new StringBuffer();
				int c;
				while((c = in.read()) != -1)
				{
					buffer.append((char)c);			
				}
				input = buffer.toString();
				in.close();
	
			}
			catch(FileNotFoundException e)
			{
				System.err.println("FileNotFoundException" + e.getMessage());
			}
		} 
		else 
		{
			Console c = System.console();
	      		if (c == null) 
			{
	         		System.err.println("No Console");
	         		System.exit(1);
	      		}
	      		input = c.readLine("Input: ");
		}

	      // Get lexer
	      ExprLexer lexer = new ExprLexer(new ANTLRInputStream(input));
	      // Get a list of matched tokens
	      CommonTokenStream tokens = new CommonTokenStream(lexer);
	      // Pass tokens to parser
	      ExprParser parser = new ExprParser(tokens);
	      // Walk parse-tree and attach our listener
	      ParseTreeWalker walker = new ParseTreeWalker();
	      EvalListener listener = new EvalListener();
	      walker.walk(listener, parser.prog());// walk from the root of parse tree
	}
} 
