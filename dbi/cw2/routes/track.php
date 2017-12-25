<?php
// Manages all requests to /tracks
// Follows very similar format to /routes/artist.php, so most commenting has not been repeated
global $router;

function trackValid( $edit=false ) {
  extract( $_POST );
  return isset( $CD, $Title )      // Require CD, Title
    && !ctype_space( $Title )      // Title not just whitespace
    && strlen( $Title ) < 101      // Title at most 100 chars
    && $edit? isset( $ID ) : true; // Require ID if editing
}

$router->get( '/tracks', function() {
  define( 'PAGE_TITLE', 'Tracks' );
  global $database, $res;
  $res = $database->exec( 'SELECT Track.*, CD.Title AS CDTitle, Artist.ArtName AS ArtistName
    FROM Track JOIN CD ON CD.ID = Track.CD
    JOIN Artist ON Artist.ID = CD.Artist;' );

  require 'views/track.php';
  return true;
} );

$router->get( '/tracks/add', function() {
  define( 'PAGE_TITLE', 'Add track' );
  global $res, $params, $database;
  $res = $database->exec( 'SELECT CD.ID, CD.Title, Artist.ArtName
    FROM CD JOIN Artist ON Artist.ID = CD.Artist;' );

  define( 'EDIT', false );
  require 'views/trackForm.php';
  return true;
} );

$router->post( '/tracks/add', function() {

  if ( trackValid() ) {
    global $database;
    $database->insert( 'Track', $_POST );
  }

  header( 'Location: /tracks' );
  return true;
} );

$router->get( '/tracks/edit/:id', function() {
  global $res, $params, $database;
  $res = $database->exec( 'SELECT * FROM Track WHERE ID = :id;', [ 'id' => $params['id'] ],
    null, false );
  $params = array_merge( $params, $res );
  define( 'PAGE_TITLE', 'Edit track \''. $res['Title'] .'\'' );

  $res = $database->exec( 'SELECT CD.ID, CD.Title, Artist.ArtName
    FROM CD JOIN Artist ON Artist.ID = CD.Artist;' );
  define( 'EDIT', true );

  require 'views/trackForm.php';
  return true;
} );

$router->post( '/tracks/edit', function() {
  if ( trackValid( true ) ) {
    global $database;

    // Remove ID from $_POST
    $id = $_POST['ID'];
    unset( $_POST['ID'] );

    $database->update( 'Track', $_POST, 'ID = :id', ['id' => $id] );
  }

  header( 'Location: /tracks' );
  return true;
} );

$router->post( '/tracks/search', function() {
  define( 'PAGE_TITLE', 'Tracks matching \''. $_POST['Title'] .'\'' );
  global $database, $res;

  $res = $database->exec( 'SELECT Track.*, CD.Title AS CDTitle, Artist.ArtName as ArtistName
    FROM Track JOIN CD ON CD.ID = Track.CD
    JOIN Artist ON Artist.ID = CD.Artist WHERE Track.Title LIKE :name;',
    [ 'name' => '%'. $_POST['Title'] .'%' ] );

  require 'views/track.php';
  return true;
} );

$router->get( '/tracks/delete/:id', function() {
  global $database, $params;
  $database->exec( 'DELETE FROM Track WHERE ID = :id', [ 'id' => $params['id'] ] );

  header( 'Location: /tracks' );
  return true;
} );
