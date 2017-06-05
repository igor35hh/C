<?php 

	$arr = array(5,3,6,2,10);

	$TotalCount = count($arr);

	print_r($arr);

	print_r("<br>");

	function reduce(&$arr, $key, &$TotalCount) {
    	for($k=$key; $k<$TotalCount-1; $k++) {
    		$arr[$k] = $arr[$k+1];
    	}
    	--$TotalCount;
    }

	function findSmallest(&$arr, &$TotalCount) {
		$smallest = $arr[0];
        $smallestIndex = 0;
		for ($i=0; $i < $TotalCount; $i++) { 
			$a = $arr[$i];
			if ($a < $smallest) {
                $smallest = $arr[$i];
                $smallestIndex = $i;
            }

		}
		return $smallestIndex;
	}

	function selectionSort(&$arr, &$TotalCount) {
		$newArr = array();
		$count = count($arr);
		for ($i=0; $i < $count; $i++) { 
			$smallest = findSmallest($arr, $TotalCount);
			$newArr[$i] = $arr[$smallest];
			reduce($arr, $smallest, $TotalCount);
		}
		return $newArr;
	}

	print_r(selectionSort($arr, $TotalCount));

?>