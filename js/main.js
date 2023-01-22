function validatePassword()
{
	var password = document.getElementById("password").value;
	var cpassword = document.getElementById("conPassword").value;
	
	if((password != cpassword))
	{
			alert("Incorrect Password", "The password length should be more than five and you should enter the same for confirm password");
			
			return false;
            location.href = 'signup.php';
            
            
	}
	
}