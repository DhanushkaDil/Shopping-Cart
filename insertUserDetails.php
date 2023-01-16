<?php 

    // check connection 
    @include 'connection.php';

    if(isset($_POST['submit']))
	{
		$Name=$_POST['name'];
		$Email=$_POST['email'];
		$Password=md5($_POST['password']);
        $conPassword=$_POST['conPassword'];


	}

    if($Password==md5($conPassword))
    {
        $sql = "INSERT INTO `userdetails`(`name`, `email`, `password`) VALUES ('$Name','$Email','$Password')";



    if(!mysqli_query($con,$sql))
		{
     		echo "not insert";
		}
        else
        {
            header("location:login.php");
        }
    }
    else
    {
        header("location:signup.php");
    }


    
       


?>