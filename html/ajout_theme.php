<!-- Bootstrap -->
<link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.css"
rel="stylesheet" media="screen">
<body class="bg-light">
    <main>
      <div class="py-5 text-center"> 
        <h1>Nouveau thème</h1>
      </div>
      <div class="container justify-content-center">
 

<?php
if($_POST)
{
  include 'config.php';
  $titre=$_POST['titre'];
  $categorie=$_POST['categorie'];
  $descriptif=$_POST['descriptif'];
  $sTitre = addslashes($titre);
  $sCategorie = addslashes($categorie);
  $sDescriptif = addslashes($descriptif);
  $query="INSERT INTO Theme (titre, categorie, descriptif) VALUES ('$sTitre', '$sCategorie', '$sDescriptif')";
  $result=mysqli_query($conn,$query);
  header('location:themes.php');
}

?>

<form class="needs-validation" novalidate="" method="POST">
   <div class ="col-xl-6">
     <label class="form-label" for="Titre">Titre</label>
       <input type="text" class="form-control" name="titre" placeholder="Dragonball Z"><br/>
   </div>
   <div class ="col-md-6">
    <label class="form-label" for="Categorie">Catégorie</label>
      <input type="text" class="form-control" name="categorie" placeholder="Aventure"><br/>
   </div>

   <div class ="col-md-6">
      <label class="form-label" for="Descriptif">Descriptif</label>
      <input type"text" class="form-control" name="descriptif" placeholder="C'est l'histoire de ..."><br/>
   </div>
   <div class="text-center">
     <input type="submit" class="btn btn-success" value="Ajouter">
     <a class="btn btn-danger" href="themes.php">Annuler</a>
   </div>
</form>
     </div>         
    </main>
  </div>
</body>
