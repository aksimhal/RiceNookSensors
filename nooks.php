<?php
$con=mysqli_connect("aa1ii6iox65zmyh.crckwrljxw6q.us-east-1.rds.amazonaws.com:3306","ricenooksensors","ricenook","ebdb");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$result = mysqli_query($con,"SELECT * FROM NOOK");

echo "<table border='1'>
<tr>
<th>Nook #</th>
<th>Last Updated</th>
<th>Occupied</th>
</tr>";

while($row = mysqli_fetch_array($result))
  {
  echo "<tr>";
  echo "<td>" . $row['nook_id'] . "</td>";
  echo "<td>" . $row['last_updated'] . "</td>";
  echo "<td>" . $row['occupied'] . "</td>";
  echo "</tr>";
  }
echo "</table>";

mysqli_close($con);
?>
