<?php
// A wrapper around PDO to make queries easier

class Database {
  protected $db;

  // Table fields that can be modified, i.e. can be used in UPDATE, INSERT
  static private $fields = [
    'Artist' => ['ArtName'],
    'CD'     => ['Title', 'Genre', 'Artist', 'Price', 'Tracks'],
    'Track'  => ['Title', 'CD', 'Length'],
  ];

  // Prepare, bind, and execute SQL with an array of named variables
  function exec( $sql, $binds=[], $all=true ) {
    $q = $this->db->prepare( $sql );
    $q->execute( $binds );

    if ( $q->columnCount() < 1 ) return;

    // Return all rows if requested, only use field names as keys
    return $all? $q->fetchAll( PDO::FETCH_ASSOC ) : $q->fetch( PDO::FETCH_ASSOC );
  }

  // Convenience method for INSERT queries
  function insert( $tab, $binds ) {

    // Ensure that $binds' keys are existing field names, avoid injection
    $allowedFields = array_fill_keys( self::$fields[ $tab ], true );
    foreach ( $binds as $key => &$val ) {
      // If OK, HTML escape value
      if ( $allowedFields[ $key ] ) {
        $val = htmlspecialchars( $val );
        continue;
      }

      // Otherwise remove from array
      unset( $binds, $key );
    }

    // Form the SQL query using $binds' keys, which indicate the fields
    $fields = array_keys( $binds );
    $sql = "INSERT INTO $tab( ". implode( ', ', $fields ) .') VALUES ( :'.
      implode( ', :', $fields ) . ' );';

    $this->exec( $sql, $binds );
  }

  // Convenience method for UPDATE queries
  function update( $tab, $binds, $cond, $params=[] ) {
    // Suggestions taken from stackoverflow.com/questions/15304656 while searching for an
    // existing method
    $sql = "UPDATE $tab SET";

    // Ensure that $binds' keys are existing field names, avoid injection
    $allowedFields = array_fill_keys( self::$fields[ $tab ], true );
    foreach ( $binds as $field => &$val ) {
      // If OK, HTML escape value, form SQL using keys
      if ( $allowedFields[ $field ] ) {
        $val = htmlspecialchars( $val );
        $sql .= " $field = :$field,";
        continue;
      }

      // Otherwise remove from array
      unset( $binds, $key );
    }

    $sql = substr( $sql, 0, -1 ) ." WHERE $cond;";
    return $this->exec( $sql, array_merge( $binds, $params ) );
  }

  // Create all tables if necessary
  function setupTables() {
    $this->db->beginTransaction();

    $this->db->exec( 'CREATE TABLE IF NOT EXISTS Artist(
      `ID` int NOT NULL PRIMARY KEY AUTO_INCREMENT,
      `ArtName` varchar(100) NOT NULL
    );' );

    $this->db->exec( 'CREATE TABLE IF NOT EXISTS CD(
      `ID` int NOT NULL PRIMARY KEY AUTO_INCREMENT,
      `Title` varchar(100) NOT NULL,
      `Genre` varchar(50),
      `Artist` int NOT NULL,
      `Price` real DEFAULT 0,
      `Tracks` int DEFAULT 1,
      CONSTRAINT FOREIGN KEY ( Artist ) REFERENCES Artist( ID )
        ON DELETE CASCADE
    );' );

    $this->db->exec( 'CREATE TABLE IF NOT EXISTS Track(
      `ID` int NOT NULL PRIMARY KEY AUTO_INCREMENT,
      `Title` varchar(100) NOT NULL,
      `CD` int NOT NULL,
      `Length` int DEFAULT 1,
      CONSTRAINT FOREIGN KEY ( CD ) REFERENCES CD( ID )
        ON DELETE CASCADE
    );' );

    $this->db->commit();
  }

  // Uses config( dbms, host, dbname, charset, user, pass )
  function __construct( $config ) {
    extract( $config );
    $this->db = new PDO( "$dbms:host=$host;port=$port;dbname=$dbname;charset=utf8", $user, $pass );
    $this->db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING );

    if ( DEVEL ) $this->setupTables();
  }
}
