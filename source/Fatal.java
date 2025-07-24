public class Fatal
{
	
	private static final String RED    = "\u001B[31m";
	private static final String RESET  = "\u001B[0m";
	private static final String BOLD   = "\u001B[1m";	
	
	private static void _prelude (final String why)	
	{
		final String message = BOLD + "tsp:" + RESET + RED + "error: " + RESET + why;
		System.err.println(message);
	}
	
	public static void cannotRead (final String filename)
	{	
		_prelude("cannot access file");
		System.err.println(" make sure '" + filename + "' file exists and it has read permissions.");
		System.exit(1);
	}
	
	public static void IO (final String filename)
	{
		_prelude("input/output ops interrupted");
		System.err.println(" cannot continue operations over '" + filename + "' file.");
		System.exit(1);
	}
	
	public static void uncompleteRead (final String filename, final int read, final long outta)
	{
		_prelude("incomplete read");
		System.err.println(" expecting " + outta + "B but only read " + read + "B instead.");	
		System.exit(1);
	}
}
