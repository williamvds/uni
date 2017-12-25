<?php
// Don't include header if request is AJAX
if ( AJAX ) return false;
global $params;
?>
<!doctype html>
<title><?php echo defined( 'PAGE_TITLE' )? PAGE_TITLE .' | ' : '', 'Songbase'; ?></title>
<link rel="stylesheet" href="/static/global.css">
<script type="text/javascript" src="/static/global.js"></script>

<header>
  <div class="sizeWrap">
    <span id="logo">
      <h1>Songbase</h1>
    </span>

    <span class="links">
<?php
  $links = [
    "Home"    => "/",
    "Artists" => "/artists",
    "Albums"  => "/albums",
    "Tracks"   => "/tracks"
  ];
  // Add 'current' class if link points to current page
  foreach ( $links as $text => $link ) {
    $class = $link == REQUEST_URI? ' class="current"' : '';
    echo "\t<a href=\"$link\"$class>$text</a>", PHP_EOL;
  }
?>
    </span>
  </div>
</header>

<content class="sizeWrap">
  <center>
