<head>
  <!-- Bootstrap -->
  <link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css"
  rel="stylesheet" media="screen">
</head>

<?php

session_start();
$_SESSION['id_face'] = $_GET['id_face'];

?>

<section class="py-5 text-center container">
  <h2>Etes-vous sûr de vouloir supprimer ce thème?<h2></br>
  <a class="btn btn-success"  href="supprimer_face.php">Continuer</a>
  <a class="btn btn-danger"  href="faces.php">Annuler</a>
</section>

