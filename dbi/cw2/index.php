<?php
ob_start();

$config = parse_ini_file( 'config.ini', true );
define( 'DEVEL', $config['development'] || $_ENV['development'] );
ini_set( 'display_errors', DEVEL );

define( 'REQUEST_URI', parse_url( $_SERVER['REQUEST_URI'] )['path'] );
define( 'BASEDIR', __DIR__ );
define( 'AJAX', isset( $_GET['ajax'] ) );

require 'router.php';
$router = new Router;

require 'database.php';
$database = new Database( $config['database'] );

// Require all route files
foreach ( scandir( 'routes/' ) as $f ) {
  $path = 'routes/'. $f;
  if ( !is_file( $path ) ) continue;

  require $path;
}

// Catch all requests, handle 404
$router->use( function() {
  http_response_code( 404 );

  global $params;
  $params['url'] = REQUEST_URI;
  define( 'PAGE_TITLE' , 'Page not found | Songbase' );

  require 'views/404.php';
} );

$router->respond();
ob_end_flush();
