<?php



	$con = mysqli_connect('localhost','root','');


	if(!$con)
	{
		echo 'Online<br>';
	}
	if(!mysqli_select_db($con,'shop_db'))
	{
		echo 'Database Not selected<br>';		
	}

	
// $servername="localhost";
// $username="root";
// $password="";
// $dbname="contact";
// $conn=mysql($servername,$username,$password,$dbname);
// if($conn->connect-error)
// {
// 	echo "error";
// }
// {die("connection faild:".$conn->connect-error);}
?>
