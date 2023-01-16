

<header class="header">

   <div class="flex">

      <a href="#" class="logo">foodies</a>

      <nav class="navbar">
         <?php 
            if(isset($_SESSION['user']))
            {
               if($_SESSION['user']=='admin')
               {
                  echo "<a href='admin.php'>add products</a>";
               }
               
            }

         ?>
         
         <a href="products.php">view products</a>
         
      </nav>

      <?php

      if(isset($_SESSION['user']))
      {
         if($_SESSION['user']!='admin')
         {
            $select_rows = mysqli_query($conn, "SELECT * FROM `cart`") or die('query failed');
            $row_count = mysqli_num_rows($select_rows);
            echo "<a href='cart.php' class='cart'>cart <span>$row_count</span> </a>";
         }
         
      }
      
      
      ?>

      
      <nav class="navbar">
         <?php 
                if(!isset($_SESSION['user']))
               { 
                     echo "<a href='signup.php'>Sign Up</a>";
               }
               
                           
         ?>
         
         <?php 
                if(!isset($_SESSION['user']))
               { 
                  echo "<a href='login.php'>Sign In</a>";
               }
               else
               {
                  echo "<a href='logout.php'>Sign Out</a>";
               }
                                     
         ?> 
         
      </nav>

      <div id="menu-btn" class="fas fa-bars"></div>

   </div>

</header>