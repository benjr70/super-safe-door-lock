<?php include_once("home.html");
$username = "Datatest";
$password = "THANh123";
$host = "datatest.cmuftxtjbxoj.us-east-1.rds.amazonaws.com";


try{
	$db =  new mysqi($host,$username,$password);// "datatest",3306);
	echo "connected to database<br>";
}
catch(PDOException $e){
	
	echo "Connection failed: " . $e->getMessage();
}

mysql_close($db);

?>