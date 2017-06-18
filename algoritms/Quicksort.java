package algoritms;

import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Quicksort {

	public static void main(String[] args) {
		List<Integer> arr = Arrays.asList(10, 5, 2, 3);
		System.out.println(quicksort(arr));
	}
	
	private static List<Integer> quicksort(List<Integer> list) {
		if(list.size() < 2) {
			return list;
		} else {
			Integer pivot = list.get(0);
			List<Integer> less = 
					list.stream().skip(1).filter(el -> el <= pivot).collect(Collectors.toList());
			List<Integer> greater = 
					list.stream().skip(1).filter(el -> el > pivot).collect(Collectors.toList());
			
			return Stream.of(
					quicksort(less).stream(), 
					Stream.of(pivot), 
					quicksort(greater).stream())
					.flatMap(Function.identity()).collect(Collectors.toList());
			
		}
	}

}
