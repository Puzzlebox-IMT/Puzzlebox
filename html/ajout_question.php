<!-- Bootstrap -->
<link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.css"
rel="stylesheet" media="screen">
<body class="bg-light">
    <main>
      <div class="py-5 text-center">
        <h1>Nouvelle question</h1>
      </div>
      <div class="container justify-content-center">


<?php
if($_POST)
{
  session_start();
  include 'config.php';
  $id_theme = $_SESSION['id_theme'];
  $enonce=$_POST['enonce'];
  $proposition1=$_POST['proposition1'];
  $proposition2=$_POST['proposition2'];
  $proposition3=$_POST['proposition3'];
  $proposition4=$_POST['proposition4'];
  $reponse=$_POST['reponse'];
  $sEnonce = addslashes($enonce);
  $sProposition1 = addslashes($proposition1);
  $sProposition2 = addslashes($proposition2);
  $sProposition3 = addslashes($proposition3);
  $sProposition4 = addslashes($proposition4);
  $sReponse = addslashes($reponse);
  $query="INSERT INTO Question (enonce, proposition1, proposition2, proposition3, proposition4, reponse) VALUES ('$sEnonce', '$sProposition1', '$sProposition2', '$sProposition3', '$sProposition4', '$sReponse')";
  if($result=mysqli_query($conn,$query))
  {
    $query2="SELECT ID_QUESTION FROM Question WHERE enonce='$enonce' AND proposition1='$proposition1' AND proposition2='$proposition2' AND proposition3='$proposition3' AND proposition4='$proposition4' AND reponse='$reponse'";
    if ($result2 = mysqli_query($conn,$query2))
    {
       while ($ligne = mysqli_fetch_assoc($result2))
       {
         $id_question = $ligne['ID_QUESTION'];
       }
       echo "L'id de la question est : ";
       echo $id_question;
       echo "L'id du theme est : ";
       echo $id_theme;
       $query3="INSERT INTO themes_questions (ID_THEME, ID_QUESTION) VALUES ('$id_theme', '$id_question')";
       if ($result3 = mysqli_query($conn,$query3))
       {
          header("location:consulter_theme.php?id_theme=$id_theme");
       }
       else
       {
         echo "Une erreur est survenue lors de la requête 2";
       }

    //$query3="INSERT INTO Question (ID_THEME, ID_QUESTION) VALUES ('$sEnonce')";
    }
    else
    {
      echo "Une erreur est survenue lors de la requête";
    }

  }
  session_unset();
  session_destroy();
}

?>

<form class="needs-validation" novalidate="" method="POST">
   <div class ="col-md-6">
     <label class="form-label" for="Enonce">Enonce</label>
       <input type="text" class="form-control" name="enonce" placeholder="Quelle est la couleur de mon caleçon?"><br/>
   </div>
   <div class ="col-md-6">
    <label class="form-label" for="Proposition1">Proposition 1</label>
      <input type="text" class="form-control" name="proposition1" placeholder="Bleu"><br/>
   </div>
   
   <div class ="col-md-6">
    <label class="form-label" for="Proposition2">Proposition 2</label>
      <input type="text" class="form-control" name="proposition2" placeholder="Jaune"><br/>
   </div>

   <div class ="col-md-6">
    <label class="form-label" for="Proposition3">Proposition 3</label>
      <input type="text" class="form-control" name="proposition3" placeholder="Rouge"><br/>
   </div>

   <div class ="col-md-6">
    <label class="form-label" for="Proposition4">Proposition 4</label>
      <input type="text" class="form-control" name="proposition4" placeholder="Orange"><br/>
   </div>

   <div class ="col-md-6">
    <label class="form-label" for="Reponse">Réponse</label>
      <input type="text" class="form-control" name="reponse" placeholder="Bleu"><br/>
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



