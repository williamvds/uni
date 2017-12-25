class OOcw1 {
  public static String encrypt( String message, String password ) {
    int m, p;
    m = p = 0;

    StringBuffer encrypted = new StringBuffer( message );

    while ( m < message.length() ) {
      encrypted.setCharAt( m, (char) (
        32 +( 126 +message.charAt( m ) +password.charAt( p ) -(m %95) ) %95
      ) );

      m++; p++;

      if ( p >= password.length() ) {
        p = 0;
      }
    }

    return encrypted.toString();
  }

  public static String decrypt( String message, String password ) {
    int m, p;
    m = p = 0;

    StringBuffer decrypted = new StringBuffer( message );

    while ( m < message.length() ) {
      decrypted.setCharAt( m, (char) (
        32 +( 95 +message.charAt( m ) -password.charAt( p ) +m ) %95
      ) );

      m++; p++;

      if ( p >= password.length() ) {
        p = 0;
      }
    }

    return decrypted.toString();
  }

  public static void encryptDecrypt( String word, String password ) {
    System.out.printf( "Encrypt word : '%s' using password '%s'\n", word, password );

    String encrypted = encrypt( word, password );
    System.out.printf("Encrypted word is '%s'\n", encrypted );

    String decrypted = decrypt( encrypted, password );
    System.out.printf( "Decrypted word is '%s'\n\n", decrypted );
  }

  public static void main( String[] args ) {
    encryptDecrypt("Hello world", "password!");
    encryptDecrypt("Hello world", "pass");
    encryptDecrypt("Hello world", "word");
    encryptDecrypt("This is a longer message", "password!");
    encryptDecrypt("This is a longer message", "pass");
    encryptDecrypt("This is a longer message", "word");
    encryptDecrypt("aaaaaaaaaaaaaaaaaaaa", "password!");
    encryptDecrypt("abcdefghijklmnopqrstuvwxyz", "password!");
    encryptDecrypt("AbCdEfGhIjKlMnOpQrStUvWxYz", "password!");
  }
}
