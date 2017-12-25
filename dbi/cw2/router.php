<?php

class Router {
  // Value of 'true' indicates that no more handlers should be run
  protected $done = false;

  // Compiles the given path into a regular expression with parameters
  // e.g. /foo/:bar/:baz matched against /foo/123/abc returns bar = "123", baz = "abc"
  protected function compilePath( $path ) {
    $path = preg_replace( '~:(?\'param\'[^:]+)~',
      "(?'$1'[^:]+)", $path );

    return '~'. $path .'[\/]?$~';
  }

  // Filter handlers depending on request method/path
  protected function runHandler( $args, $method = null ) {
    global $params;

    // Don't run handler if routing finished, or request method / path doesn't match
    if ( $this->done
      || isset( $method ) && $_SERVER['REQUEST_METHOD'] != $method
      || count( $args ) > 1 && !preg_match( self::compilePath( $args[0] ), REQUEST_URI, $params )
    ) return;

    // Run handler function, save results into $done
    $this->done = ( count( $args ) > 1? $args[1]() : $args[0]() ) === true;
  }

  // Add handler to be checked regardless of request method
  public function use() {
    $this->runHandler( func_get_args() );
  }

  // Add a GET handler
  public function get() {
    $this->runHandler( func_get_args(), 'GET' );
  }

  // Add a POST handler
  public function post() {
    $this->runHandler( func_get_args(), 'POST' );
  }

  // Encode response as JSON
  public function respondJSON() {
    global $params;
    $params = isset( $params )? $params : [];

    $html = ob_get_clean();

    echo json_encode( [
      'html'  => $html,
      'title' => defined( 'PAGE_TITLE' )? PAGE_TITLE : 'Songbase'] );
  }

  // Should be run after all handlers have been checked
  public function respond() {
    // JSON response for AJAX requests
    if ( AJAX )
      return self::respondJSON();
  }

  function __construct() {
    // Render error page if something goes wrong
    register_shutdown_function( function() {
      if ( error_get_last()['type'] !== E_ERROR ) return;
      ob_clean();

      define( 'PAGE_TITLE' , 'Error | SongBase' );
      http_response_code( 500 );

      require 'views/500.php';
      if ( AJAX ) self::respondJSON();
    } );

  }

}
