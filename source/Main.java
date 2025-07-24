import jxa.*;

class Arguments
{
	public static JxaFlag<String> sheet = new JxaFlag<>("sheet", "main sheet", 's', JxaFlag.arg.yes, "", "");
		
	private static JxaFlag<?>[] flags =
	{
		sheet,
	};	

	public static void solve (final String[] args) { Jxa.parse(flags, args); }
	public static void usage () { JxaDoc.printUsage(flags); }
}

public class Main
{
	public static void main (String[] args)
	{
		Arguments.solve(args);
		final String filename = Arguments.sheet.getArgument();
		
		if (filename.isEmpty())
		{
			Arguments.usage();
		}
		
		Sheet[] sheets = new Sheet[1 + Jxa._posArguments.size()];
		sheets[0] = new Sheet(filename);
		
		for (int i = 0; i < Jxa._posArguments.size(); i++)
		{
			sheets[i + 1] = new Sheet(Jxa._posArguments.get(i));
		}	
	}	
}
