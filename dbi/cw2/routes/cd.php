<?php
// Manages all requests to /albums
// Follows very similar format to /routes/artist.php, so most commenting has not been repeated
global $router;

function cdValid( $edit=false ) {
  extract( $_POST );
  return isset( $Artist, $Title )  // Require Artist, Title
    && !ctype_space( $Title )      // Title not just whitespace
    && strlen( $Title ) < 101      // Title at most 100 chars
    && $edit? isset( $ID ) : true; // Require ID if editing
}

$router->get( '/albums', function() {
  define( 'PAGE_TITLE', 'Albums' );
  global $database, $res;
  $res = $database->exec( 'SELECT CD.*, Artist.ArtName AS ArtistName
    FROM CD JOIN Artist ON Artist.ID = CD.Artist;' );

  require 'views/cd.php';
  return true;
} );

$router->get( '/albums/add', function() {
  define( 'PAGE_TITLE', 'Add album' );
  global $res, $params, $database;
  $res = $database->exec( 'SELECT ID, ArtName FROM Artist;' );

  define( 'EDIT', false );
  require 'views/cdForm.php';
  return true;
} );

$router->post( '/albums/add', function() {

  if ( cdValid() ) {
    global $database;
    $database->insert( 'CD', $_POST );
  }

  header( 'Location: /albums' );
  return true;
} );

$router->get( '/albums/edit/:id', function() {
  global $res, $params, $database;
  $res = $database->exec( 'SELECT * FROM CD WHERE ID = :id;', [ 'id' => $params['id'] ],
    null, false );
  $params = array_merge( $params, $res );
  define( 'PAGE_TITLE', 'Edit album \''. $res['Title'] .'\'' );

  $res = $database->exec( 'SELECT ID, ArtName FROM Artist;' );
  define( 'EDIT', true );

  require 'views/cdForm.php';
  return true;
} );

$router->post( '/albums/edit', function() {
  if ( cdValid( true ) ) {
    global $database;

    // Remove ID from $_POST
    $id = $_POST['ID'];
    unset( $_POST['ID'] );

    $database->update( 'CD', $_POST, 'ID = :id', ['id' => $id] );
  }

  header( 'Location: /albums' );
  return true;
} );

$router->post( '/albums/search', function() {
  define( 'PAGE_TITLE', 'Albums matching \''. $_POST['Title'] .'\'' );
  global $database, $res;

  $res = $database->exec( 'SELECT CD.*, Artist.ArtName AS ArtistName
    FROM CD JOIN Artist ON Artist.ID = CD.Artist
    WHERE CD.Title LIKE :name;',
    [ 'name' => '%'. $_POST['Title'] .'%' ] );

  require 'views/cd.php';
  return true;
} );

$router->get( '/albums/delete/:id', function() {
  global $database, $params;
  $database->exec( 'DELETE FROM CD WHERE ID = :id', [ 'id' => $params['id'] ] );

  header( 'Location: /albums' );
  return true;
} );

$router->get( '/albums/:id', function() {
  global $params, $database, $res;
  $res = $database->exec( 'SELECT Title FROM CD WHERE ID = :id;', [ 'id' => $params['id'] ],
    false );
  define( 'PAGE_TITLE', 'Tracks in '. $res['Title'] );

  $res = $database->exec( 'SELECT Track.*, CD.Title AS CDTitle, Artist.ArtName as ArtistName
    FROM Track JOIN CD ON CD.ID = Track.CD
    JOIN Artist ON Artist.ID = CD.Artist WHERE Track.CD = :id;',
    [ 'id' => $params['id'] ] );

  require 'views/track.php';
  return true;
} );

