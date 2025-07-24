import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Help
{
	public static char[] readFile (final String filename)
	{
		File file = new File(filename);
		if (!file.exists() || !file.canRead())
		{
			Fatal.cannotRead(filename);
		}
		
		try
		{
			FileReader reader = new FileReader(file);			
			final long length = file.length();	
			char[] buffer     = new char[(int) length];
			final int read    = reader.read(buffer, 0, (int) length);
				
			if (read != (int) length)
			{
				Fatal.uncompleteRead(filename, read, length);
			}	
			reader.close();
			return buffer;
		}
		catch (IOException e) { Fatal.IO(filename); }	
		return null;
	}

}
