import java.io.File;

public class Sheet
{
	private String filename;
	private char[] source;
	private long   length;
	private int    columns;
	private int    rows;
	private int    cells;
	
	public Sheet (final String filename)
	{
		this.filename = filename;
		this.source = Help.readFile(filename);
		
		System.out.println(this.source);
		System.out.println("~~~~~~~~~~~~~");
	}
}

