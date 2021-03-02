<!-- Bootstrap -->
<link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.css"
rel="stylesheet" media="screen">
<body class="bg-light">
    <main>
      <div class="py-5 text-center">
        <h1>Nouvelle face</h1>
      </div>
      <div class="container justify-content-center">


<?php
if($_POST)
{
  //session_start();
  include 'config.php';
  $intitule = $_POST['intitule'];
  $descriptif = $_POST['descriptif'];
  $sIntitule = addslashes($intitule);
  $sDescriptif = addslashes($descriptif);
  $query="INSERT INTO Face (intitule, descriptif, etat) VALUES ('$sIntitule', '$sDescriptif', 'Désactivée')";
  if($result=mysqli_query($conn,$query))
  {
    $filename = escapeshellarg($intitule);
    // escape the others
    $val = shell_exec("/usr/bin/sudo mkdir /home/pi/git_workspace/Puzzlebox/'$filename'"); 
    $val2 = shell_exec("/usr/bin/sudo cp /home/pi/git_workspace/Puzzlebox/Common/MQTT/mainWifiEnigma_version_test_mqtt.py /home/pi/git_workspace/Puzzlebox/'$filename'/main_'$filename'.py");
    header('location:faces.php');
  }
  else
  {
    echo "Une erreur est survenue lors de la requête";
  }
  //session_unset();
  //session_destroy();
}

?>

<form class="needs-validation" novalidate="" method="POST">
   <div class ="col-md-6">
     <label class="form-label" for="intitule">Intitule</label>
       <input type="text" class="form-control" name="intitule" placeholder="Bluetooth_enigma"><br/>
   </div>
   <div class ="col-md-6">
    <label class="form-label" for="descriptif">Descriptif</label>
      <input type="text" class="form-control" name="descriptif" placeholder="Cette face comprend des énigmes concernant la technologie bluetooth"><br/>
   </div>


   <div class="text-center">
     <input type="submit" class="btn btn-success" value="Ajouter">
     <a class="btn btn-danger" href="faces.php">Annuler</a>
   </div>
</form>
     </div>
    </main>
  </div>
</body>





