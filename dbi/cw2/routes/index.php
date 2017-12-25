<?php
global $router;

$router->get( '/', function() {
  global $database, $res;

  $res = $database->exec( "SELECT
    ( SELECT COUNT(*) FROM Artist ) as Artists,
    ( SELECT COUNT(*) FROM CD ) as Albums,
    ( SELECT COUNT(*) FROM Track ) as Tracks;",
  null, false );

  require 'views/index.php';
  return true;
} );
