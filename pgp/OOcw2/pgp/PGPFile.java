package pgp;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Wrapper class created for use in G51PGP to simplify initial file I/O
 * @author jaa
 */
public class PGPFile
{
	public boolean openReadFile( String strFileName )
	{
		// Close any existing file before opening new one
		if ( br != null )
			closeReadFile();
		try 
		{
			br = new BufferedReader(
					new FileReader(strFileName));
	    }
		catch(Exception e )
		{
			return false;
		}
		return true;
	}

	public String readNextLine()
	{
		// If not open then we can't do this
		if ( br == null )
			return null;

		try
		{
			return br.readLine();
		} 
		catch (IOException e)
		{
			return null;
		}
	}
	
	public boolean closeReadFile()
	{
		// If not open then we can't do this
		if ( br == null )
			return false;
		
		try
		{
			br.close();
			br = null;
		} 
		catch (IOException e)
		{
			return false;
		}
		return true;
	}
	
	public boolean openWriteFile( String strFileName )
	{
		// Close any existing file before opening new one
		if ( bw != null )
			closeWriteFile();

		try
		{
	        bw = new BufferedWriter(new FileWriter(strFileName));
			return true;
	    } 
		catch (IOException e)
		{
			return false;
		}
	}

	public boolean writeLine( String strLine )
	{
		// If not open then we can't do this
		if ( bw == null )
			return false;

		try
		{
			bw.write( strLine + "\r\n" );
			return true;
		} 
		catch (IOException e)
		{
			return false;
		}
	}
	
	public boolean closeWriteFile()
	{
		// If not open then we can't do this
		if ( bw == null )
			return false;

		try
		{
			bw.close();
			bw = null;
			return true;
		} 
		catch (IOException e)
		{
			return false;
		}
	}
	
	// Internal object - the reader for the input file
	protected BufferedReader br;
	// Internal object - the writer for the output file
	protected BufferedWriter bw;
}
