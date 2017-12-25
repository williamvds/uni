package pgp;

public class MyFile extends PGPFile {
    public PGPText readEntireFile( String path ) {
        PGPText text = new PGPText();
        openReadFile( path );
        
        String ln;        
        while ( ( ln = readNextLine() ) != null ) {
          text.addLine( ln );
        }
        
        closeReadFile();
        return text;
    }

    public boolean writeEntireFile( String path, PGPText text ) {
      openWriteFile( path );
     
      boolean res = true;
      for ( int i = 0; i < text.getLineCount(); i++ ) {
        res = writeLine( text.getLine(i) );

        if ( !res ) { break; }
      }
      
      closeWriteFile();
      return res;
    }

    public static void main( String[] args ) {
      MyFile file = new MyFile();
      PGPText text = file.readEntireFile( "test.txt" );

      for ( int i = 0; i < 5; i++ ) {
        text.setLine( i, "" );
      }
      
      file.writeEntireFile( "test.txt", text );
    }
}
