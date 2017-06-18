<?php

	//but this option doesn't work:)

	function quicksort($arr) {
		if(count($arr) < 2) {
			return $arr;
		} else {
			$pivot = reset($arr);

			$less = array_filter($arr, function ($var) use($pivot) { return $var <= $pivot; });
			$greater = array_filter($arr, function ($var) use($pivot) { return $var > $pivot; });

			return array_merge(quicksort($less) , [$pivot] , quicksort($greater));
		}
	}

	$arr = array(1,5,3,4);
	print_r($arr);

	echo '<br>';

	$all = quicksort($arr);
	print_r($all);

?>