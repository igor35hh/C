<?php 

	function binarySearch($array, $item) {
		$low = 0;
		$high = count($array) - 1;

		while($low <= $high) {
			$middle = floor(($low+$high)/2);
			if($array[$middle] == $item) {
				return $middle;
			}
			if($array[$middle] > $item) {
				$high = $middle - 1;
			} else {
				$low = $middle + 1;
			}
		}
		return null;
	}

	$array = [1,3,5,7,9];
	echo binarySearch($array, 5) . "<br>";
	echo binarySearch($array, 1) . "<br>";

 ?>