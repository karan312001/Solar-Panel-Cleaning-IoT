  
<?php
class Solardata{
 public $link='';
 function __construct($temperature, $flowrate, $pressure, $water_level){
  $this->connect();
  $this->storeInDB($temperature, $flowrate, $pressure, $water_level);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'solarcleaning') or die('Cannot select the DB');
 }
 
 function storeInDB($temperature, $flowrate, $pressure, $water_level){
  $query = "insert into sensor_data set flowrate='".$flowrate."', temperature='".$temperature."', pressure='".$pressure."', water_level='".$water_level."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['temperature'] != '' and  $_GET['flowrate'] != '' and  $_GET['pressure'] != '' and  $_GET['water_level'] != ''){
 $Solardata=new Solardata($_GET['temperature'], $_GET['flowrate'], $_GET['pressure'], $_GET['water_level']);
}


?>