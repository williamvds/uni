<?php require 'views/header.php'; ?>
    <h1>A database of songs</h1>
    <h2>Currently storing</h2>
<?php
global $res;
foreach ( $res as $index => $count ) {
  $url = strtolower( $index );
  echo "
    <a href=\"/$url\" class=\"card\">
        <h1>$count</h1>
        <h2>$index</h2>
    </a>
  ";
}

?>
<?php require 'views/footer.php'; ?>
