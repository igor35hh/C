<?php

$book = array();

$book["apple"] = 0.67;
$book["milk"] = 1.49;
$book["avocado"] = 1.49;

foreach ($book as $key => $value)
	echo "$key $value\n";

	echo "\n";

	print_r($book);
	
$voted = array(); 

// function check_voted($name) {
// 	global $voted;
// 	if(isset($voted[$name])) {
// 		echo "Kick them out \n";
// 	} else {
// 		$voted[$name] = True;
// 		echo "Let them vote \n";
// 	}
// };

// check_voted("tom");
// check_voted("mike");
// check_voted("mike");

$check_voted = function ($name) use(&$voted) {
	global $voted;
	if(isset($voted[$name])) {
		echo "Kick them out \n";
	} else {
		$voted[$name] = True;
		echo "Let them vote \n";
	}
};

$check_voted("tom");
$check_voted("mike");
$check_voted("mike");

