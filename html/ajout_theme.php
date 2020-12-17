<!-- Bootstrap -->
<link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css"
rel="stylesheet" media="screen">

<h2>Nouveau thème</h2></br>

<?php
if($_POST)
{
  include 'config.php';
  $titre=$_POST['titre'];
  $categorie=$_POST['categorie'];
  $descriptif=$_POST['descriptif'];
  $query="INSERT INTO Theme (titre, categorie, descriptif) VALUES ('$titre', '$categorie', '$descriptif')";
  $result=mysqli_query($conn,$query);
  header('location:themes.php');
}

?>

<form method="POST">
   <p>Titre :
      <input type"text" name="titre"><br/>
   </p>
   <p>Catégorie :
      <input type"text" name="categorie"><br/>
   </p>

   <p>Descriptif :
      <input type"text" name="descriptif"><br/>
   </p>
   <input type="submit" value="Ajouter">
</form>

