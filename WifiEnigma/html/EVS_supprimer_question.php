<head>
  <!-- Bootstrap -->
  <link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css"
  rel="stylesheet" media="screen">
</head>

<?php

session_start();
$_SESSION['id_question'] = $_GET['id_question'];
$id_theme =  $_SESSION['id_theme'];

?>

<section class="py-5 text-center container">
  <h2>Etes-vous sûr de vouloir supprimer cette question?<h2></br>
  <a class="btn btn-success"  href="supprimer_question.php">Continuer</a>
  <a class="btn btn-danger"  href="consulter_theme.php?id_theme=<?php echo $id_theme?>">Annuler</a>
</section>
