<?php
// Manages all requests to /artists
global $router;

// Determines whether the given values in $_POST pass validation
function artistValid( $edit=false ) {
  extract( $_POST );
  return isset( $ArtName )         // Require ArtName
    && !ctype_space( $ArtName )    // ArtName not just whitespace
    && strlen( $ArtName ) < 101    // ArtName at most 100 chars
    && $edit? isset( $ID ) : true; // ID set if editing
}

// Default page, shows list of artists
$router->get( '/artists', function() {
  define( 'PAGE_TITLE', 'Artists' ); // Defines the page title that is replaced in the page
  global $database, $res;
  $res = $database->exec( 'SELECT * FROM Artist;' ); // Perform query to use in page

  require 'views/artist.php'; // Require page that contains and modifies the HTML
  return true; // Return true to stop any more router functions being run
} );

// Add artist form
$router->get( '/artists/add', function() {
  // EDIT constant modifies the generated page accordingly
  define( 'PAGE_TITLE', 'Add artist' );
  define( 'EDIT', false );

  require 'views/artistForm.php';
  return true;
} );

// Handles add POST request, adds new artist
$router->post( '/artists/add', function() {

  if ( artistValid() ) {
    global $database;
    $database->insert( 'Artist', $_POST );
  }

  header( 'Location: /artists' );
  return true;
} );

// Edit artist form
$router->get( '/artists/edit/:id', function() {
  // $params gives the 'parameters' gathered from the dynamic URL, in this case, 'id'
  global $params, $database;
  $res = $database->exec( 'SELECT * FROM Artist WHERE ID = :id;', [ 'id' => $params['id'] ],
    null, false );
  $params = array_merge( $params, $res );

  define( 'EDIT', true );
  define( 'PAGE_TITLE', 'Edit artist \''. $res['ArtName'] .'\'' );
  require 'views/artistForm.php';
  return true;
} );

// Handles edit POST request, alters artist
$router->post( '/artists/edit', function() {
  if ( artistValid( true ) ) {
    global $database;

    // Remove ID from $_POST
    $id = $_POST['ID'];
    unset( $_POST['ID'] );

    $database->update( 'Artist', $_POST, 'ID = :id', ['id' => $id] );
  }

  header( 'Location: /artists' );
  return true;
} );

// Searching artists
$router->post( '/artists/search', function() {
  define( 'PAGE_TITLE', 'Artists matching \''. $_POST['ArtName'] .'\'' );
  global $database, $res;

  $res = $database->exec( 'SELECT * FROM Artist WHERE ArtName LIKE :name;',
    [ 'name' => '%'. $_POST['ArtName'] .'%' ] );

  require 'views/artist.php';
  return true;
} );

// Delete artists
$router->get( '/artists/delete/:id', function() {
  global $database, $params;
  $database->exec( 'DELETE FROM Artist WHERE ID = :id', [ 'id' => $params['id'] ] );

  header( 'Location: /artists' );
  return true;
} );

// Only shows albums by specific artist
$router->get( '/artists/:id', function() {
  global $params, $database, $res;
  $res = $database->exec( 'SELECT ArtName FROM Artist WHERE ID = :id;', [ 'id' => $params['id'] ],
    false );
  define( 'PAGE_TITLE', 'Albums by '. $res['ArtName'] );

  // Select CD info, as well as the artist's name
  $res = $database->exec( 'SELECT CD.*, Artist.ArtName AS ArtistName
    FROM CD JOIN Artist ON Artist.ID = CD.Artist
    WHERE Artist = :id;', [ 'id' => $params['id'] ] );

  require 'views/cd.php';
  return true;
} );

