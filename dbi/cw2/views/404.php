<?php require 'views/header.php'; global $params; ?>
    <h1>404</h1>
    <p>The requested page <em><?php echo $params['url']; ?></em> was not found</p>
    <a href="/">Return to the home page</a>
<?php require 'views/footer.php'; ?>
