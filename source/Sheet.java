public class Sheet
{
	private String filename;
	private String source;
	private long   length;
	private int    columns;
	private int    rows;
	private int    cells;
	
	public Sheet (final String filename)
	{
		this.filename = filename;
		this.readSource();
	}
		
	private void readSource ()
	{
		System.out.println(this.filename);
	}	
}
