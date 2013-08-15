<?php
$con=mysqli_connect("aa1ii6iox65zmyh.crckwrljxw6q.us-east-1.rds.amazonaws.com:3306","ricenooksensors","ricenook","ebdb");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$now = date("Y-m-d H:i:s");
$sql="UPDATE `ebdb`.`NOOK` SET `last_updated`='$now', `occupied`='1' WHERE `nook_id`='2'";
if (mysqli_query($con,$sql))
  {
  echo "Database updated successfully!";
  }
else
  {
  echo "Error with database: " . mysqli_error($con);
  }
mysqli_close($con);
?>
